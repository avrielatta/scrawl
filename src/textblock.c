#include <stdlib.h>

#include "textblock.h"
#include "types.h"
#include "linebuffer.h"

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
