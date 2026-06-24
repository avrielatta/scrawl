#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "types.h"

typedef struct Font {
    TTF_Font *font;
    float size;
} Font;

typedef struct Text {
    Font* font;
    char* str;
    size_t len;
    int vw, vh;
    SDL_Color color;
} Text;

Font* txt_FontInit(void);
Text txt_CreateText(const char* str, SDL_Color color);
SDL_Texture* txt_RenderTextToTexture(SDL_Renderer *render, Font* font, Text *text);
