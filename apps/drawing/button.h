#ifndef UI_BUTTON
#define UI_BUTTON

#include "raylib.h"

typedef struct {
    int top_left_x;
    int top_left_y;
    int width;
    int height;
    char *text;
} Button;

Button *Button_Calloc(int top_left_x, int top_left_y, int width, int height, const char *x);

void Button_Free(Button *Button);

void Button_Draw(const Button *btn, Color btn_color, Color text_color);

int Button_IsInside(const Button *btn, int x, int y);

#endif