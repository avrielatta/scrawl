#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "gapbuffer.h"

GapBuffer* gb_CreateGapBuffer(void) {
    GapBuffer *buf = malloc(sizeof(GapBuffer));
    buf->pos = 0;
    buf->capacity = BUFFER_GAP;
    buf->gapEnd = buf->capacity - 2;
    buf->buf = malloc(BUFFER_CAP);

    for (int i = 0; i < buf->capacity - 1; i++) {
        buf->buf[i] = EMPTY;
    }

    buf->buf[buf->capacity - 1] = '\0';
    return buf;
}

void gb_Grow(GapBuffer *buffer, const char *input) {
    // store old trailing data in a temporary string
    char temp[256];
    u16 j = 0;
    for (int i = buffer->pos + 1; i < buffer->capacity - 1; i++) {
        temp[j] = buffer->buf[i];
        j++;
    }
    // save value for later
    u16 trailingCount = j;
    j--;
    // update to new capacity
    buffer->capacity += BUFFER_GAP;
    // new allocation
    buffer->buf = realloc(buffer->buf, (size_t)buffer->capacity);
    // init new space 
    for (int i = buffer->pos; i < buffer->capacity - 2; i++) {
        buffer->buf[i] = EMPTY;
    }
    // null terminate
    buffer->buf[buffer->capacity - 1] = '\0';
    // insert old trailing data at the end
    for (int i = 0; i < trailingCount; i++) {
        buffer->buf[(buffer->capacity - 2) - i] = temp[j];
        j--;
    }
    // place new input
    buffer->buf[buffer->pos++] = *input;
    // move gap end
    buffer->gapEnd += BUFFER_GAP;
}

void gb_Left(GapBuffer *buffer) {
    buffer->buf[buffer->gapEnd--] = buffer->buf[buffer->pos - 1];
    buffer->buf[buffer->pos--] = EMPTY;
    buffer->buf[buffer->pos] = CURSOR;
}

void gb_Right(GapBuffer *buffer) {
    if (buffer->gapEnd < buffer->capacity - 2) {
        if (buffer->buf[buffer->gapEnd + 1] != EMPTY) {
            buffer->buf[buffer->pos++] = buffer->buf[buffer->gapEnd + 1];
            buffer->buf[++buffer->gapEnd] = EMPTY;
            buffer->buf[buffer->pos] = CURSOR;
        }
    }
}

void gb_Delete(GapBuffer *buffer) {
    buffer->buf[++buffer->gapEnd] = EMPTY;
}
