#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "txt.h"
#include "edit.h"
#include "types.h"
#include "linebuffer.h"
#include "textblock.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

Font *font;
Text text;
SDL_Texture *tex;
TextBlock *block;

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

    font = txt_FontInit();
    if (font == NULL) {
        return SDL_APP_FAILURE;
    }

    SDL_StartTextInput(window);

    text = txt_CreateText("placeholder", (SDL_Color){ 255, 255, 255, 255 });
    tex = txt_RenderTextToTexture(renderer, font, &text);

    if (tex == NULL) {
        SDL_Log("Error generating texture from surface: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    block = tb_CreateBlock();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_TEXT_INPUT) {
        input_HandleTextInput(event->text.text, block->lines[block->lineCount - 1]);
    } else if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_ESCAPE) {
            return SDL_APP_SUCCESS;
        } else {
            input_HandleKeyDown(event->key, block->lines[block->lineCount - 1]);
        }
    }

    SDL_DestroyTexture(tex);
    text = txt_CreateText(block->lines[block->lineCount - 1]->buf, (SDL_Color){ 255, 255, 255, 255 });
    tex = txt_RenderTextToTexture(renderer, font, &text);

    if (tex == NULL) {
        SDL_Log("Error generating texture from surface: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    system("clear");
    SDL_Log("%s", block->lines[block->lineCount - 1]->buf);
    SDL_Log("pos: %d, gapEnd: %d, cap: %d", block->lines[block->lineCount - 1]->pos, block->lines[block->lineCount - 1]->gapEnd, block->lines[block->lineCount - 1]->capacity);
 
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    const double now = ((double)SDL_GetTicks()) / 1000.0f; // converts millliseconds to seconds
    const float red = (float)(0.5f + 0.5f * SDL_sin(now));
    const float green = (float)(0.5f + 0.5f * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5f + 0.5f * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    if (tex) {
        SDL_FRect dstrct = (SDL_FRect){ 0, 0, (f32)text.vw, (f32)text.vh };
        SDL_RenderTexture(renderer, tex, NULL, &dstrct);
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    TTF_CloseFont(font->font);
    free(font);
    SDL_DestroyTexture(tex);
    TTF_Quit();
    if (result) {}
}
