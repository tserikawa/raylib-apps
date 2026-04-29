#ifndef UI_EDIT_MODE
#define UI_EDIT_MODE

typedef enum{
    waiting,
    add_point,
    delete_point,
    add_line,
    delete_line
}edit_mode;

void mode_draw_label(const edit_mode *mode, int canvas_left);
#endif