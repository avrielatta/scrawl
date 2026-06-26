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
        if (buf->gapIndex < buf->gapEnd - 1) {
            lb_AddChar(buf, input);
            return true;
        } else {
            // create a new line
            tb_NewLine(block);
            lb_AddChar(block->lines[block->lineCount - 1], input);
            return false;
        }
    } else {
        tb_NewLine(block);
        lb_AddChar(block->lines[block->lineCount - 1], input);
        return true;
    }
}

void input_HandleKeyDown(SDL_KeyboardEvent event, TextBlock* block) {
    LineBuffer* buffer = block->lines[block->lineCount - 1];

    if (event.key == SDLK_BACKSPACE) {
        lb_Backspace(buffer);
    } else if (event.key == SDLK_LEFT) {
        lb_Left(buffer);
    } else if (event.key == SDLK_RIGHT) {
        lb_Right(buffer);
    } else if (event.key == SDLK_DELETE) {
        lb_Delete(buffer);
    } else if (event.key == SDLK_RETURN) {
        tb_NewLine(block);
    }
}
