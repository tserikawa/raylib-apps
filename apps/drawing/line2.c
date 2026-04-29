#include "line2.h"
#include <stdlib.h>

line2 *line2_calloc(const Vector2 start, const Vector2 end)
{
    line2 *line = malloc(sizeof(line2));
    if (line == NULL)
    {
        return NULL;
    }

    line->start = start;
    line->end = end;
    return line;
}

void line2_free(line2 *line)
{
    free(line);
}