#include <SDL3/SDL.h>

#include "edit.h"
#include "txt.h"
#include "linebuffer.h"
#include "textblock.h"

bool input_HandleTextInput(const char *input, TextBlock* block) {
    if (block->lineCount > 0) {
        // store reference for shorthand
        LineBuffer* buf = block->lines[block->lineCount - 1];

        // if we are under capacity
        if (buf->gapIndex < buf->gapEnd) {
            lb_AddChar(buf, input);
            return true;
        }
    } else {
        tb_NewLine(block, input);
        return false;
    }
}

void input_HandleKeyDown(SDL_KeyboardEvent event, LineBuffer *buffer) {
    if (event.key == SDLK_BACKSPACE && !(buffer->gapIndex == 0)) {
        lb_Backspace(buffer);
    } else if (event.key == SDLK_LEFT && buffer->gapIndex != 0) {
        lb_Left(buffer);
    } else if (event.key == SDLK_RIGHT && buffer->gapIndex <= buffer->gapEnd) {
        lb_Right(buffer);
    } else if (event.key == SDLK_DELETE && buffer->gapEnd < buffer->capacity - 2) {
        lb_Delete(buffer);
    }
}
