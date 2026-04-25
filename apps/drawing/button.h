#ifndef UI_BUTTON
#define UI_BUTTON

#include "raylib.h"

typedef struct {
    int top_left_x;
    int top_left_y;
    int width;
    int height;
    char *text;
} button;

button *button_calloc(int top_left_x, int top_left_y, int width, int height, const char *x);

void button_free(button *button);

void button_draw(const button *btn, Color btn_color, Color text_color);

int button_is_inside(const button *btn, int x, int y);

#endif