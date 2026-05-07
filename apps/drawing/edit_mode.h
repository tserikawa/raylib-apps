#ifndef UI_EDIT_MODE
#define UI_EDIT_MODE

typedef enum{
    waiting,
    addPoint,
    deletePoint,
    selectPoint,
    addLine,
    deleteLine,
    selectLine,
}EditMode;

void EditMode_Draw(const EditMode *mode, int canvas_left);
#endif