#include <stdlib.h>

#include "textblock.h"
#include "types.h"
#include "linebuffer.h"
#include "txt.h"

TextBlock* tb_CreateBlock(void) {
    TextBlock *newBlock = malloc(sizeof(TextBlock));
    newBlock->pos = (Vec2){ 0, 0 };
    newBlock->lineCount = 0;
    return newBlock;
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
        if (block->lines[i]->preGapWidth > 0) {
            TTF_DestroyText(preGapTexts[i]);
            preGapTexts[i] = TTF_CreateText(
                    engine,
                    font,
                    block->lines[i]->buf,
                    block->lines[i]->preGapWidth
            );
        }

        // create post-gap text object
        if (block->lines[i]->postGapWidth > 0) {
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

void tb_RenderBlock(TextBlock* block, TTF_Text* preGapTexts[], TTF_Text* postGapTexts[]) {
    int currentTextWidth;

    for (int i = 0; i < block->lineCount; i++) {
        if (block->lines[i]->preGapWidth > 0) {
            // calculate width of the first section of text
            TTF_GetTextSize(preGapTexts[i], &currentTextWidth, NULL);
            // draw pre-gap text
            TTF_DrawRendererText(preGapTexts[i], 0, i * FONT_SIZE);
            // draw post-gap text
            TTF_DrawRendererText(postGapTexts[i], currentTextWidth, i * FONT_SIZE);
        }
    }
}
