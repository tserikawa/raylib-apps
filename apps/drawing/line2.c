#include "raylib.h"
#include "raymath.h"
#include "line2.h"
#include <float.h>
#include <assert.h>

int FindClosestLineIndex(const Vector2 *cursor, const Line2 *lines, int lineCount, int tolerance)
{
    assert(tolerance > 0);

    int lineIndex = -1;
    float minimumDistance = FLT_MAX;
    for (int i = 0; i < lineCount; i++)
    {
        Vector2 a = lines[i].start;
        Vector2 b = lines[i].end;
        Vector2 c = *cursor;

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