#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "animation.h"
#include "txt.h"
#include "edit.h"
#include "types.h"
#include "linebuffer.h"
#include "textblock.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

Timer* timer;

TTF_Font *font;
TTF_Text* preGapTexts[MAX_BLOCK_LINES];
TTF_Text* postGapTexts[MAX_BLOCK_LINES];
TTF_TextEngine *textEngine;
TextBlock *block;
Cursor* cursor;

bool isNewlineNeeded;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *arg[]) {
    SDL_SetAppMetadata("Scrawl", "0.1.0", "com.avrielatta.scrawl");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("src/renderer", 1920, 1080, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    timer = anim_CreateTimer(60);

    font = txt_FontInit();
    if (font == NULL) {
        return SDL_APP_FAILURE;
    }

    textEngine = TTF_CreateRendererTextEngine(renderer);

    SDL_StartTextInput(window);

    block = tb_CreateBlock();
    cursor = tb_CreateCursor(1, 18);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_TEXT_INPUT) {
        isNewlineNeeded = !(input_HandleTextInput(event->text.text, block));
    } else if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_ESCAPE) {
            return SDL_APP_SUCCESS;
        } else {
            input_HandleKeyDown(event->key, block);
        }
    }

    tb_UpdateTexts(textEngine, block, preGapTexts, postGapTexts, font);

#ifdef DEBUG_MODE
    system("clear");
    SDL_Log("%s", block->lines[block->lineCount - 1]->buf);
    SDL_Log(
            "pos: %d, gapEnd: %d, cap: %d",
            block->lines[block->lineCount - 1]->pos,
            block->lines[block->lineCount - 1]->gapEnd,
            block->lines[block->lineCount - 1]->capacity
    );
#endif

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    anim_UpdateTimer(timer);

    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    tb_RenderBlock(renderer, block, cursor, textEngine, font, preGapTexts, postGapTexts);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    for (int i = 0; i < block->lineCount; i++) {
        TTF_DestroyText(preGapTexts[i]);
        TTF_DestroyText(postGapTexts[i]);
    }

    for (int i = 0; i < block->lineCount; i++) {
        lb_DestroyBuffer(block->lines[i]);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    if (result) {}
}
