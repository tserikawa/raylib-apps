#ifndef GEO_POINT
#define GEO_POINT

#include "raylib.h"

typedef struct {
    float x;
    float y;
    bool isSelected;
} Point2;

Vector2 Point2_AsVector2(const Point2 *point);

Point2 Point2_FromVector2(const Vector2 *vector, bool isSelected);
#endif