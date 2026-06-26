#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include "linebuffer.h"
#include "types.h"

#define MAX_BLOCK_LINES 8

typedef struct TextBlock {
    LineBuffer *lines[MAX_BLOCK_LINES];
    u8 lineCount;
    Vec2 pos;
} TextBlock;

TextBlock* tb_CreateBlock(void);
void tb_NewLine(TextBlock *block);
void tb_UpdateTexts(TTF_TextEngine* engine, TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[], TTF_Font* font);
void tb_RenderBlock(TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]);
