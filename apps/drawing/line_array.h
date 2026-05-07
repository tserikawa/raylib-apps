#ifndef ARRAY_LINE
#define ARRAY_LINE

#include "raylib.h"
#include "line2.h"
#include "point2.h"

typedef struct {
    Line2 *values;
    int size;
    int capacity;
} LineArray;

LineArray *LineArray_Calloc(int capacity);

void LineArray_Add(LineArray *array, const Line2 value);

void LineArray_RemoveAt(LineArray *array, int index);

void LineArray_UnselectAll(LineArray *array);

void LineArray_Clear(LineArray *array);

Line2 LineArray_Get(const LineArray *array, int index);

void LineArray_Free(LineArray *array);

int LineArray_FindClosestLineIndex(const LineArray *lines, const Point2 *position, int tolerance);
#endif