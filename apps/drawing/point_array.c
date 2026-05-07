#include "point_array.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

PointArray *PointArray_Calloc(int capacity)
{
    PointArray *array = malloc(sizeof(PointArray));
    if (array == NULL)
    {
        return NULL;
    }

    array->values = calloc(capacity, sizeof(Vector2));
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void PointArray_Add(PointArray *array, const Point2 value)
{
    int index = array->size;
    array->values[index] = value;
    array->size++;
}

void PointArray_RemoveAt(PointArray *array, int index)
{
    bool isFirst = index == 0;
    bool isLast = index == array->capacity - 1;
    if (isFirst || isLast)
    {
        array->size--;
    }
    else
    {
        for (int i = index; i < array->capacity - 1; i++)
        {
            array->values[i] = array->values[i + 1];
        }
        array->size--;
    }
}


void PointArray_UnselectAll(PointArray *array)
{
    for(int i = 0; i < array->size; i++)
    {
        array->values[i].isSelected = false;
    }
}

void PointArray_Clear(PointArray *array)
{
    array->size = 0;
}

void PointArray_Free(PointArray *array)
{
    free(array->values);
    array->values = NULL;

    free(array);
    array = NULL;
}

int PointArray_FindClosestPointIndex(const PointArray *points, const Point2 *target, int tolerance)
{

    assert(tolerance > 0);

    for (int i = 0; i < points->size; i++)
    {
        int dx = target->x - points->values[i].x;
        int dy = target->y - points->values[i].y;
        int dxy = dx * dx + dy * dy;
        if (dxy <= tolerance * tolerance)
        {
            return i;
        }
    }

    return -1;
}