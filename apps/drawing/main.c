#include "button.h"
#include "edit_mode.h"
#include "line2.h"
#include "line_array.h"
#include "point_array.h"
#include "raylib.h"
#include "raymath.h"
#include "window.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void UpdatePointCategory(Button *addButton, Button *deleteButton, Button *clearButton, PointArray *points,
                         EditMode *currentMode, const Vector2 mouse)
{
    // ラベル
    DrawText("POINT", 20, 20, 20, BLACK);
    // ADDボタン
    if (Button_IsInside(addButton, mouse.x, mouse.y))
    {
        Button_Hovered(addButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            *currentMode = add_point;
        }
    }
    else
    {
        Button_UnHovered(addButton);
    }
    Button_Draw(addButton);

    // DELETEボタン
    if (Button_IsInside(deleteButton, mouse.x, mouse.y))
    {
        Button_Hovered(deleteButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            *currentMode = delete_point;
        }
    }
    else
    {
        Button_UnHovered(deleteButton);
    }
    Button_Draw(deleteButton);

    // CLEARボタン
    if (Button_IsInside(clearButton, mouse.x, mouse.y))
    {
        Button_Hovered(clearButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PointArray_Clear(points);
            *currentMode = waiting;
        }
    }
    else
    {
        Button_UnHovered(clearButton);
    }
    Button_Draw(clearButton);
}

void UpdateLineCategory(Button *addButton, Button *deleteButton, Button *clearButton, LineArray *lines,
                        EditMode *currentMode, const Vector2 mouse)
{
    // ラベル
    DrawText("LINE", 20, 100, 20, BLACK);
    // ADDボタン
    if (Button_IsInside(addButton, mouse.x, mouse.y))
    {
        Button_Hovered(addButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            *currentMode = add_line;
        }
    }
    else
    {
        Button_UnHovered(addButton);
    }
    Button_Draw(addButton);

    // DELETEボタン
    if (Button_IsInside(deleteButton, mouse.x, mouse.y))
    {
        Button_Hovered(deleteButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            *currentMode = delete_line;
        }
    }
    else
    {
        Button_UnHovered(deleteButton);
    }
    Button_Draw(deleteButton);

    // CLEARボタン
    if (Button_IsInside(clearButton, mouse.x, mouse.y))
    {
        Button_Hovered(clearButton);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            LineArray_Clear(lines);
            *currentMode = waiting;
        }
    }
    else
    {
        Button_UnHovered(clearButton);
    }
    Button_Draw(clearButton);
}

void UpdatePointCanvasEvent(const EditMode *currentMode, const Vector2 *cursor, PointArray *points)
{
    const int tolerance = 5;

    if (*currentMode == delete_point)
    {
        DrawCircleLines(cursor->x, cursor->y, tolerance, RED);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (*currentMode == add_point)
        {
            PointArray_Add(points, *cursor);
        }
        else if (*currentMode == delete_point)
        {
            int index = PointArray_FindClosestPointIndex(points, cursor, tolerance);
            if (index != -1)
            {
                PointArray_RemoveAt(points, index);
            }
        }
    }
}

void UpdateLineCanvasEvent(const EditMode *currentMode, const Vector2 *cursor, LineArray *lines, Vector2 *lineStartPoint)
{
    const int tolerance = 5;

    if (*currentMode == delete_line)
    {
        DrawCircleLines(cursor->x, cursor->y, tolerance, RED);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (*currentMode == add_line)
        {
            if (isnan(lineStartPoint->x) || isnan(lineStartPoint->y))
            {
                *lineStartPoint = *cursor;
            }
            else
            {
                Line2 ln = (Line2){*lineStartPoint, *cursor};
                LineArray_Add(lines, ln);
                *lineStartPoint = (Vector2){NAN, NAN};
            }
        }
        else if (*currentMode == delete_line)
        {
            int idx = LineArray_FindClosestLineIndex(lines, cursor, tolerance);
            if (idx != -1)
            {
                LineArray_RemoveAt(lines, idx);
            }
        }
    }
}

void UpdateCanvas()
{
    
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const Window window = {1200, 800, 240};
    InitWindow(window.width, window.height, "GEOMETRY EDITOR");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // 点のリスト
    PointArray *points = PointArray_Calloc(10);
    if (points == NULL)
    {
        TraceLog(LOG_FATAL, "Fail to allocate PointArray...");
        return -1;
    }

    // 線分のリスト
    LineArray *lines = LineArray_Calloc(10);
    if (lines == NULL)
    {
        TraceLog(LOG_FATAL, "Fail to allocate LineArray...");
        return -1;
    }
    // 未設定を表すためにNANを使う。
    Vector2 lineStartPoint = {NAN, NAN};

    // UI
    EditMode currentMode = waiting;
    Button *pointAddButton = Button_Calloc(20, 40, 50, 20, "ADD");
    Button *pointDeleteButton = Button_Calloc(80, 40, 70, 20, "DELETE");
    Button *pointClearButton = Button_Calloc(160, 40, 60, 20, "CLEAR");
    Button *lineAddButton = Button_Calloc(20, 120, 50, 20, "ADD");
    Button *lineDeleteButton = Button_Calloc(80, 120, 70, 20, "DELETE");
    Button *lineClearButton = Button_Calloc(160, 120, 60, 20, "CLEAR");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close Button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Vector2 cursor = GetMousePosition();
        bool isInsideCanvas = Window_IsInsideCanvas(&window, &cursor);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // 仕切り線
        DrawLine(window.canvasLeftX, 0, window.canvasLeftX, window.height, GRAY);

        // ボタン
        UpdatePointCategory(pointAddButton, pointDeleteButton, pointClearButton, points, &currentMode, cursor);
        UpdateLineCategory(lineAddButton, lineDeleteButton, lineClearButton, lines, &currentMode, cursor);

        // イベント
        if(isInsideCanvas)
        {
            UpdatePointCanvasEvent(&currentMode, &cursor, points);
            UpdateLineCanvasEvent(&currentMode, &cursor, lines, &lineStartPoint);
        }

#pragma region 全体に関わる処理

        // モード表示
        EditMode_Draw(&currentMode, window.canvasLeftX);
        // 節点数表示
        char pointCountText[256];
        sprintf(pointCountText, "  POINT COUNT: %d", points->size);
        DrawText(pointCountText, window.canvasLeftX + 20, 40, 16, BLACK);
        // 線分数表示
        char lineCountText[256];
        sprintf(lineCountText, "  LINE COUNT: %d", lines->size);
        DrawText(lineCountText, window.canvasLeftX + 20, 60, 16, BLACK);

        // 作成済みの点を描画
        for (int i = 0; i < points->size; i++)
        {
            Vector2 point = PointArray_Get(points, i);
            DrawCircle(point.x, point.y, 5.0f, BLACK);
        }

        // 作成済みの線を描画
        for (int i = 0; i < lines->size; i++)
        {
            DrawLineEx(lines->values[i].start, lines->values[i].end, 2.0, BLACK);
        }

        // 線分追加時の線分を描画
        if (!isnan(lineStartPoint.x) && !isnan(lineStartPoint.y))
        {
            DrawLineEx(lineStartPoint, cursor, 1.0, BLUE);
        }
#pragma endregion

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Button_Free(lineClearButton);
    Button_Free(lineDeleteButton);
    Button_Free(lineAddButton);
    Button_Free(pointClearButton);
    Button_Free(pointDeleteButton);
    Button_Free(pointAddButton);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}