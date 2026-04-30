#ifndef UI_EDIT_MODE
#define UI_EDIT_MODE

typedef enum{
    waiting,
    add_point,
    delete_point,
    add_line,
    delete_line
}EditMode;

void EditMode_Draw(const EditMode *mode, int canvas_left);
#endif