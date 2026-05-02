#ifndef UI_BUTTON
#define UI_BUTTON

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    int top_left_x;
    int top_left_y;
    int width;
    int height;
    char *text;
    bool isHovered;
} Button;

Button *Button_Calloc(int top_left_x, int top_left_y, int width, int height, const char *x);

void Button_Free(Button *Button);

void Button_Hovered(Button *button);

void Button_UnHovered(Button *button);

void Button_Draw(const Button *button);

int Button_IsInside(const Button *btn, int x, int y);

#endif