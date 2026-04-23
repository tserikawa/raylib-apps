#include "button.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

button *button_calloc(int top_left_x, int top_left_y, int width, int height, const char *x){
    button *btn = malloc(sizeof(button));
    if(btn == NULL){
        return NULL;
    }

    btn->top_left_x = top_left_x;
    btn->top_left_y = top_left_y;
    btn->width = width;
    btn->height = height;

    btn->text = strdup(x);
    if(btn->text == NULL){
        free(btn);
        return NULL;
    }

    return btn;
}

void button_free(button *btn){
    free(btn->text);
    free(btn);
}

void button_draw(const button *btn, Color btn_color, Color text_color){
    DrawRectangle(
        btn->top_left_x,
        btn->top_left_y,
        btn->width,
        btn->height,
        btn_color
    );

    DrawText(
        btn->text,
        btn->top_left_x + 10,
        btn->top_left_y + btn->height / 6,
        btn->height * 2 / 3,
        text_color
    );
}

int button_is_inside(const button *btn, int x, int y){
    int top = btn->top_left_y;
    int bottom = top + btn->height;
    int left = btn->top_left_x;
    int right = left + btn->width;
    
    if(x < left || right < x) return 0;
    if(y < top || bottom < y) return 0;
    return 1;
}