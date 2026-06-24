#include <SDL3/SDL.h>

#include "edit.h"
#include "txt.h"
#include "gapbuffer.h"

void input_HandleTextInput(const char *input, GapBuffer *buf) {
    if (buf->pos < buf->gapEnd - 1) {
        buf->buf[buf->pos++] = *input;
        buf->buf[buf->pos] = CURSOR;
    } else {
        gb_Grow(buf, input);
    }
}

void input_HandleKeyDown(SDL_KeyboardEvent event, GapBuffer *buffer) {
    if (event.key == SDLK_BACKSPACE && !(buffer->pos == 0)) {
        buffer->buf[buffer->pos--] = EMPTY;
        buffer->buf[buffer->pos] = CURSOR;
    } else if (event.key == SDLK_LEFT && buffer->pos != 0) {
        gb_Left(buffer);
    } else if (event.key == SDLK_RIGHT && buffer->pos <= buffer->gapEnd) {
        gb_Right(buffer);
    } else if (event.key == SDLK_DELETE && buffer->gapEnd < buffer->capacity - 2) {
        gb_Delete(buffer);
    }
}
