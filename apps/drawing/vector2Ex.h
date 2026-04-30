#ifndef GEO_VECTOR2EX
#define GEO_VECTOR2EX

#include "raylib.h"

int FindClosestPointIndex(const Vector2 *cursor, const Vector2 *points, int pointCount, int tolerance);

#endif