#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_rect.h>

#include "linebuffer.h"
#include "types.h"

#define MAX_BLOCK_LINES 8

typedef struct TextBlock {
    LineBuffer *lines[MAX_BLOCK_LINES];
    u8 lineCount;
    Vec2 pos;
} TextBlock;

typedef struct Cursor {
    SDL_FRect rect;
} Cursor;

TextBlock* tb_CreateBlock(void);
void tb_NewLine(TextBlock *block);
void tb_UpdateTexts(TTF_TextEngine* engine, TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[], TTF_Font* font);
int tb_RenderBlockText(TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]);
void tb_RenderBlock(SDL_Renderer* renderer, TextBlock* block, Cursor* cursor, TTF_TextEngine* engine, TTF_Font* font, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]);

/* CURSOR FUNCTIONS */
Cursor* tb_CreateCursor(float w, float h);
void tb_DestroyCursor(Cursor* cursor);
void tb_RenderCursor(SDL_Renderer* renderer, Cursor* cursor, int xPos, TextBlock* block);
