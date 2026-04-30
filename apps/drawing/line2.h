#ifndef GEO_LINE2
#define GEO_LINE2

#include "raylib.h"

typedef struct {
    Vector2 start;
    Vector2 end;
} Line2;

int FindClosestLineIndex(const Vector2 *cursor, const Line2 *lines, int lineCount, int tolerance);

#endif