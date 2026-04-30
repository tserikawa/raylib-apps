#include "raylib.h"
#include "vector2Ex.h"
#include <assert.h>

int FindClosestPointIndex(const Vector2 *cursor, const Vector2 *points, int pointCount, int tolerance)
{
    assert(tolerance > 0);

    for (int i = 0; i < pointCount; i++)
    {
        int dx = cursor->x - points[i].x;
        int dy = cursor->y - points[i].y;
        int dxy = dx * dx + dy * dy;
        if (dxy <= tolerance * tolerance)
        {
            return i;
        }
    }

    return -1;
}