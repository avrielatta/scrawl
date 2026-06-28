#include <stdlib.h>

#include "textblock.h"
#include "types.h"
#include "linebuffer.h"
#include "txt.h"

/* CURSOR DECLARATIONS */
Cursor* CreateCursor(float w, float h);
void DestroyCursor(Cursor* cursor);
void RenderCursor(SDL_Renderer* renderer, Cursor* cursor, int xPos, TextBlock* block);

/* TEXT BLOCK DEFINITIONS */

TextBlock* tb_CreateBlock(void) {
    TextBlock *newBlock = malloc(sizeof(TextBlock));
    newBlock->pos = (Vec2){ 0, 0 };
    newBlock->lineCount = 0;
    newBlock->cursor = CreateCursor(1, 18);
    return newBlock;
}

void tb_DestroyBlock(TextBlock* block) {
    DestroyCursor(block->cursor);
    free(block);
}

void tb_NewLine(TextBlock *block) {
    if (block->lineCount < 8) {
        block->lines[block->lineCount++] = lb_CreateBuffer();
    }
}

void tb_UpdateTexts(
        TTF_TextEngine* engine,
        TextBlock* block,
        TTF_Text* preGapTexts[],
        TTF_Text* postGapTexts[],
        TTF_Font* font
) {
    for (int i = 0; i < block->lineCount; i++) {
        // create pregap text object
        if (block->lines[i]->preGapWidth >= 0) {
            TTF_DestroyText(preGapTexts[i]);
            preGapTexts[i] = TTF_CreateText(
                    engine,
                    font,
                    block->lines[i]->buf,
                    block->lines[i]->preGapWidth
            );
        }

        // create post-gap text object
        if (block->lines[i]->postGapWidth >= 0) {
            TTF_DestroyText(postGapTexts[i]);
            postGapTexts[i] = TTF_CreateText(
                    engine,
                    font,
                    &block->lines[i]->buf[block->lines[i]->gapEnd + 1],
                    block->lines[i]->postGapWidth
            );
        }
    }
}

int tb_RenderBlockText(TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]) {
    int currentTextWidth;

    for (int i = 0; i < block->lineCount; i++) {
        if (block->lines[i]->preGapWidth > 0) {
            // calculate width of the first section of text
            TTF_GetTextSize(preGapTexts[i], &currentTextWidth, NULL);
            // draw pre-gap text
            TTF_DrawRendererText(preGapTexts[i], 0, i * FONT_SIZE);
            // draw post-gap text
            TTF_DrawRendererText(postGapTexts[i], currentTextWidth, i * FONT_SIZE);
        } else {
            /* this is necessary bc, without it, currentTextWidth
             * will maintain the value of lineCount-1's width,
             * thus drawing the cursor at the correct y-level
             * but at the x-pos of the end of the previous line
             */
            currentTextWidth = 0;
        }
    }

    return currentTextWidth;
}

void tb_RenderBlock(
        SDL_Renderer* renderer,
        TextBlock* block,
        TTF_TextEngine* engine,
        TTF_Font* font,
        TTF_Text* preGapTexts[],
        TTF_Text* postGapTexts[]
) {
    int cursorX = tb_RenderBlockText(block, preGapTexts, postGapTexts);
    RenderCursor(renderer, block->cursor, cursorX, block);
}

/* CURSOR DEFINITIONS */

Cursor* CreateCursor(float w, float h) {
    Cursor* newCursor = malloc(sizeof(Cursor));
    newCursor->rect.x = 0.0f;
    newCursor->rect.y = 0.0f;
    newCursor->rect.w = w;
    newCursor->rect.h = h;

    return newCursor;
}

void DestroyCursor(Cursor* cursor) {
    free(cursor);
}

void RenderCursor(SDL_Renderer* renderer, Cursor* cursor, int xPos, TextBlock* block) {
    cursor->rect.x = xPos;
    cursor->rect.y = (block->lineCount - 1) * (cursor->rect.h - 2);
    SDL_RenderRect(renderer, &cursor->rect);
}
