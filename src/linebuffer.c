#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "linebuffer.h"

LineBuffer* lb_CreateBuffer(void) {
    LineBuffer *buf = malloc(sizeof(LineBuffer));
    buf->capacity = BUFFER_CAP;
    buf->gapIndex = 0;
    buf->preGapWidth = 0;
    buf->postGapWidth = 0;
    buf->gapEnd = buf->capacity - 1;
    buf->gapWidth = buf->capacity;
    buf->buf = malloc(BUFFER_CAP + 1);
    buf->buf[BUFFER_CAP] = '\0';

    return buf;
}

void lb_DestroyBuffer(LineBuffer* buffer) {
    free(buffer->buf);
    free(buffer);
}

void lb_AddChar(LineBuffer* buffer, const char* input) {
    // set the char at current gap start to input
    buffer->buf[buffer->gapIndex++] = *input;
    // update the gap width variable
    buffer->gapWidth = buffer->gapEnd - buffer->gapIndex;
    // only draw cursor if not at line's end
    if (buffer->gapIndex != buffer->gapEnd) {
        buffer->buf[buffer->gapIndex] = CURSOR;
    }
    // update gapwidth
    buffer->gapWidth--;
    // update pre gap width
    buffer->preGapWidth++;
}

void lb_Left(LineBuffer *buffer) {
    // move previous char to end of gap
    buffer->buf[buffer->gapEnd--] = buffer->buf[buffer->gapIndex - 1];
    // set gapindex to empty and decrement
    buffer->buf[buffer->gapIndex--] = EMPTY;
    // set new gapindex to cursor
    buffer->buf[buffer->gapIndex] = CURSOR;
    // update pregap width
    buffer->preGapWidth--;
    // update post gap width
    buffer->postGapWidth++;
}

void lb_Right(LineBuffer *buffer) {
    // safety check for line end
    if (buffer->gapEnd < buffer->capacity - 1) {
        // move first char after gap to current gapindex and inc
        buffer->buf[buffer->gapIndex++] = buffer->buf[buffer->gapEnd + 1];
        // inc gap end pos and set to empty
        buffer->buf[++buffer->gapEnd] = EMPTY;
        // set new index to cursor
        buffer->buf[buffer->gapIndex] = CURSOR;
        // update pregap width
        buffer->preGapWidth++;
        // update post gap width
        buffer->postGapWidth--;
    }
}

void lb_Backspace(LineBuffer* buffer) {
    // set current index to empty and decrement
    buffer->buf[buffer->gapIndex--] = EMPTY;
    // set new index to cursor
    buffer->buf[buffer->gapIndex] = CURSOR;
    // update gap width
    buffer->gapWidth++;
    // update pre gap width
    buffer->preGapWidth--;
}

void lb_Delete(LineBuffer *buffer) {
    // overwrite first char after gap
    buffer->buf[++buffer->gapEnd] = EMPTY;
    // update gapwidth
    buffer->gapWidth++;
    // update post gap width
    buffer->postGapWidth--;
}
