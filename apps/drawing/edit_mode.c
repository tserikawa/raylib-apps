#include "edit_mode.h"
#include "raylib.h"

void EditMode_Draw(const EditMode *mode, int canvas_left)
{
    if (*mode == add_point)
    {
        DrawText("MODE: ADD POINT", canvas_left + 20, 20, 20, BLACK);
    }
    else if (*mode == delete_point)
    {
        DrawText("MODE: DELETE POINT", canvas_left + 20, 20, 20, BLACK);
    }
    else if (*mode == add_line)
    {
        DrawText("MODE: ADD LINE", canvas_left + 20, 20, 20, BLACK);
    }
    else if (*mode == delete_line)
    {
        DrawText("MODE: DELETE LINE", canvas_left + 20, 20, 20, BLACK);
    }
    else
    {
        DrawText("COMMAND WAITING...", canvas_left + 20, 20, 20, BLACK);
    }
}