#include "edit_mode.h"
#include "raylib.h"

static const char *text_add_point = "MODE: ADD POINT";
static const char *text_delete_point = "MODE: DELETE POINT";
static const char *text_waiting = "COMMAND WAITING...";

void mode_draw_label(const edit_mode *mode, int canvas_left)
{
    if (*mode == add_point)
    {
        DrawText(text_add_point, canvas_left + 20, 20, 20, BLACK);
    }
    else if (*mode == delete_point)
    {
        DrawText(text_delete_point, canvas_left + 20, 20, 20, BLACK);
    }
    else
    {
        DrawText(text_waiting, canvas_left + 20, 20, 20, BLACK);
    }
}