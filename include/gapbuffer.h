#pragma once
#include "types.h"

#define BUFFER_CAP 1024
#define BUFFER_GAP 16
#define EMPTY '_'
#define CURSOR '#'

typedef struct GapBuffer {
    char *buf;
    u16 pos, gapEnd;
    u16 capacity;
} GapBuffer;

GapBuffer* gb_CreateGapBuffer(void);
void gb_Grow(GapBuffer *buffer, const char *input);
void gb_Left(GapBuffer *buffer);
void gb_Right(GapBuffer *buffer);
void gb_Delete(GapBuffer *buffer);
