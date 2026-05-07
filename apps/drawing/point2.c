#include "point2.h"
#include "raylib.h"

Vector2 Point2_AsVector2(const Point2 *point)
{
    return (Vector2){point->x, point->y};
}

Point2 Point2_FromVector2(const Vector2 *vector, bool isSelected)
{
    return (Point2){vector->x, vector->y, isSelected};
}