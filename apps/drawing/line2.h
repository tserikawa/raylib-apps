#ifndef GEO_LINE2
#define GEO_LINE2

#include "raylib.h"

typedef struct {
    Vector2 start;
    Vector2 end;
} line2;

line2 *line2_calloc(const Vector2 start, const Vector2 end);

void line2_free(line2 *line);

#endif