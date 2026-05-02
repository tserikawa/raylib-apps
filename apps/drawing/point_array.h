#ifndef ARRAY_POINT
#define ARRAY_POINT

#include "raylib.h"

typedef struct {
    Vector2 *values;
    int size;
    int capacity;
} PointArray;

PointArray *PointArray_Calloc(int capacity);

void PointArray_Add(PointArray *array, const Vector2 value);

void PointArray_RemoveAt(PointArray *array, int index);

void PointArray_Clear(PointArray *array);

Vector2 PointArray_Get(const PointArray *array, int index);

void PointArray_Free(PointArray *array);

int PointArray_FindClosestPointIndex(const PointArray *points, const Vector2 *target, int tolerance);
#endif