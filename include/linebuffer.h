#pragma once
#include "types.h"

#define BUFFER_CAP 64
#define EMPTY '_'

typedef struct LineBuffer {
    int gapIndex, gapEnd, capacity;
    int preGapWidth, gapWidth, postGapWidth;
    char *buf;
} LineBuffer;

LineBuffer* lb_CreateBuffer(void);
void lb_DestroyBuffer(LineBuffer* buffer);
void lb_AddChar(LineBuffer* buffer, const char* input);
void lb_Left(LineBuffer *buffer);
void lb_Right(LineBuffer *buffer);
void lb_Backspace(LineBuffer* buffer);
void lb_Delete(LineBuffer *buffer);
