#ifndef UI_SCREEN
#define UI_SCREEN

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int canvasLeftX;
} Window;

bool Window_IsInsideCanvas(const Window *window, const Vector2 *position);

#endif