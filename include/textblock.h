#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_rect.h>

#include "linebuffer.h"
#include "types.h"

#define MAX_BLOCK_LINES 8

typedef struct Cursor {
    SDL_FRect rect;
} Cursor;

typedef struct TextBlock {
    LineBuffer *lines[MAX_BLOCK_LINES];
    u8 lineCount;
    Vec2 pos;
    Cursor* cursor;
} TextBlock;

// instantiates a new TextBlock object
TextBlock* tb_CreateBlock(void);
// safely unloads TextBlock data from memory
void tb_DestroyBlock(TextBlock* block);

// appends a new line to the end of a TextBlock, safely
void tb_NewLine(TextBlock *block);
// updates pointer arrays of SDL_Text data to be used for rendering
void tb_UpdateTexts(
        TTF_TextEngine* engine,
        TextBlock* block,
        TTF_Text* preGapTexts[],
        TTF_Text* postGapTexts[],
        TTF_Font* font
);

/* does     - renders TextBlock text data to SDL Renderer
 * returns  - the width of the current line of text (to be used
 *            by the cursor for positioning)
 */
int tb_RenderBlockText(TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]);
// renders TextBlock and Cursor to SDL renderer
void tb_RenderBlock(
        SDL_Renderer* renderer,
        TextBlock* block,
        TTF_TextEngine* engine,
        TTF_Font* font,
        TTF_Text* preGapTexts[],
        TTF_Text* postGapTexts[]
);
