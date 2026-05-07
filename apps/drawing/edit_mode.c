#include "edit_mode.h"
#include "raylib.h"
#include <string.h>

void EditMode_Draw(const EditMode *mode, int canvas_left)
{
    char text[255];

    if (*mode == addPoint)
    {
        strncpy(text, "MODE: ADD POINT", sizeof(text) - 1);
    }
    else if (*mode == deletePoint)
    {
        strncpy(text, "MODE: DELETE POINT", sizeof(text) - 1);
    }
    else if (*mode == selectPoint)
    {
        strncpy(text, "MODE: SELECT POINT", sizeof(text) - 1);
    }
    else if (*mode == addLine)
    {
        strncpy(text, "MODE: ADD LINE", sizeof(text) - 1);
    }
    else if (*mode == deleteLine)
    {
        strncpy(text, "MODE: DELETE LINE", sizeof(text) - 1);
    }
    else if (*mode == selectLine)
    {
        strncpy(text, "MODE: SELECT LINE", sizeof(text) - 1);
    }
    else
    {
        strncpy(text, "COMMAND WAITING...", sizeof(text) - 1);
    }
    text[254] = '\0';

    DrawText(text, canvas_left + 20, 20, 20, BLACK);
}