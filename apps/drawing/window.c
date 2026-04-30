#include "window.h"

bool Window_IsInsideCanvas(const Window *window, const Vector2 *position)
{
    return window->canvasLeftX <= position->x 
            && position->x <= window->width 
            && 0 <= position->y 
            && position->y <= window->height;
}