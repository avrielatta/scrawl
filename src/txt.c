#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "txt.h"

TTF_Font* txt_FontInit(void) {
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf library: %s", SDL_GetError());
        return NULL;
    }

    TTF_Font* font = TTF_OpenFont(
            "resources/fonts/Roboto/static/Roboto-Medium.ttf",
            16.0f
    );

    return font;
}
