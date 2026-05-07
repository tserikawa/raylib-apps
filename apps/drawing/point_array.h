#ifndef ARRAY_POINT
#define ARRAY_POINT

#include "raylib.h"
#include "point2.h"

typedef struct {
    Point2 *values;
    int size;
    int capacity;
} PointArray;

PointArray *PointArray_Calloc(int capacity);

void PointArray_Add(PointArray *array, const Point2 value);

void PointArray_RemoveAt(PointArray *array, int index);

void PointArray_UnselectAll(PointArray *array);

void PointArray_Clear(PointArray *array);

void PointArray_Free(PointArray *array);

int PointArray_FindClosestPointIndex(const PointArray *points, const Point2 *target, int tolerance);
#endif