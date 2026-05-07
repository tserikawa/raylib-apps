#include "line_array.h"
#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

LineArray *LineArray_Calloc(int capacity)
{
    LineArray *array = malloc(sizeof(LineArray));
    if (array == NULL)
    {
        return NULL;
    }

    array->values = calloc(capacity, sizeof(Line2));
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void LineArray_Add(LineArray *array, const Line2 value)
{
    int index = array->size;
    array->values[index] = value;
    array->size++;
}

void LineArray_RemoveAt(LineArray *array, int index)
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

void LineArray_UnselectAll(LineArray *array)
{
    for(int i = 0; i < array->size; i++)
    {
        array->values[i].isSelected = false;
    }
}

void LineArray_Clear(LineArray *array)
{
    array->size = 0;
}

Line2 LineArray_Get(const LineArray *array, int index)
{
    assert(0 <= index && index < array->size);
    return array->values[index];
}

void LineArray_Free(LineArray *array)
{
    free(array->values);
    array->values = NULL;

    free(array);
    array = NULL;
}

int LineArray_FindClosestLineIndex(const LineArray *lines, const Point2 *position, int tolerance)
{
    assert(tolerance > 0);

    int lineIndex = -1;
    float minimumDistance = FLT_MAX;
    for (int i = 0; i < lines->size; i++)
    {
        Vector2 a = lines->values[i].start;
        Vector2 b = lines->values[i].end;
        Vector2 c = Point2_AsVector2(position);

        Vector2 ab = Vector2Subtract(b, a);
        Vector2 ac = Vector2Subtract(c, a);

        float t = Vector2DotProduct(ac, ab) / Vector2DotProduct(ab, ab);
        Clamp(t, 0.0, 1.0);
        
        Vector2 tAB = Vector2Scale(ab, t);
        Vector2 closestPoint = Vector2Add(a, tAB);

        Vector2 distanceVector = Vector2Subtract(c, closestPoint);
        float distance = Vector2Length(distanceVector);
        
        if (distance < minimumDistance && distance <= (float)tolerance) {
            minimumDistance = distance;
            lineIndex = i;
        }
    }
    return lineIndex;
}