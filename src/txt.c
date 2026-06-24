#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "txt.h"

Font* txt_FontInit(void) {
    Font* font = malloc(sizeof(Font));

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf library: %s", SDL_GetError());
        return NULL;
    }

    font->font = TTF_OpenFont("resources/fonts/Roboto/static/Roboto-Medium.ttf", 32.0f);

    return font;
}

Text txt_CreateText(const char* str, SDL_Color color) {
    Text newText = {0};
    newText.str = str;
    newText.len = strlen(newText.str);
    newText.color = color;
    return newText;
}

SDL_Texture* txt_RenderTextToTexture(SDL_Renderer *render, Font* font, Text *text) {
    if (TTF_GetStringSize(font->font, text->str, text->len, &text->vw, &text->vh)) {
        SDL_Surface *surf = TTF_RenderText_Blended(font->font, text->str, text->len, text->color);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surf);
        SDL_DestroySurface(surf);
        return tex;
    }

    return NULL;
}
