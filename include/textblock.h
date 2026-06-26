#pragma once
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
