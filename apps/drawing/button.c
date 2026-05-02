#include "button.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Button *Button_Calloc(int top_left_x, int top_left_y, int width, int height, const char *x){
    Button *btn = malloc(sizeof(Button));
    if(btn == NULL){
        return NULL;
    }

    btn->top_left_x = top_left_x;
    btn->top_left_y = top_left_y;
    btn->width = width;
    btn->height = height;
    btn->isHovered = false;

    btn->text = strdup(x);
    if(btn->text == NULL){
        free(btn);
        return NULL;
    }

    return btn;
}

void Button_Free(Button *btn){
    free(btn->text);
    free(btn);
}

void Button_Hovered(Button *button)
{
    button->isHovered = true;
}

void Button_UnHovered(Button *button)
{
    button->isHovered = false;
}

void Button_Draw(const Button *button)
{
    DrawRectangle(
        button->top_left_x,
        button->top_left_y,
        button->width,
        button->height,
        button->isHovered ? DARKGRAY : LIGHTGRAY
    );

    DrawText(
        button->text,
        button->top_left_x + 10,
        button->top_left_y + button->height / 6,
        button->height * 2 / 3,
        button->isHovered ? WHITE : BLACK
    );
}

int Button_IsInside(const Button *btn, int x, int y){
    int top = btn->top_left_y;
    int bottom = top + btn->height;
    int left = btn->top_left_x;
    int right = left + btn->width;
    
    if(x < left || right < x) return 0;
    if(y < top || bottom < y) return 0;
    return 1;
}