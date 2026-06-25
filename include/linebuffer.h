#pragma once
#include "types.h"

#define BUFFER_CAP 64
#define BUFFER_GAP 16
#define EMPTY '_'
#define CURSOR '#'

typedef struct LineBuffer {
    char *buf;
    u16 pos, gapEnd;
    u16 capacity;
} LineBuffer;

LineBuffer* lb_CreateBuffer(void);
void lb_Grow(LineBuffer *buffer, const char *input);
void lb_Left(LineBuffer *buffer);
void lb_Right(LineBuffer *buffer);
void lb_Delete(LineBuffer *buffer);
