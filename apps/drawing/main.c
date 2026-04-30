#include "window.h"
#include "button.h"
#include "edit_mode.h"
#include "line2.h"
#include "vector2Ex.h"
#include "raylib.h"
#include "raymath.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const Window window = { 1200, 800, 240 };
    InitWindow(window.width, window.height, "GEOMETRY EDITOR");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // 点のリスト
    const int pointCapacity = 10;
    Vector2 *pts;
    int pointCount = 0;
    if ((pts = calloc(pointCapacity, sizeof(Vector2))) == NULL)
    {
        printf("Fail..");
        return -1;
    }

    // 線分のリスト
    const int lineCapacity = 10;
    Line2 *lines;
    int lineCount = 0;
    if ((lines = calloc(lineCapacity, sizeof(Line2))) == NULL)
    {
        printf("Faile...");
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

        #pragma region Pointカテゴリー
        // ラベル
        DrawText("POINT", 20, 20, 20, BLACK);
        // ADDボタン
        if (Button_IsInside(pointAddButton, cursor.x, cursor.y))
        {
            Button_Draw(pointAddButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentMode = add_point;
            }
        }
        else
        {
            Button_Draw(pointAddButton, LIGHTGRAY, BLACK);
        }

        // DELETEボタン
        if (Button_IsInside(pointDeleteButton, cursor.x, cursor.y))
        {
            Button_Draw(pointDeleteButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentMode = delete_point;
            }
        }
        else
        {
            Button_Draw(pointDeleteButton, LIGHTGRAY, BLACK);
        }

        // CLEARボタン
        if (Button_IsInside(pointClearButton, cursor.x, cursor.y))
        {
            Button_Draw(pointClearButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                pointCount = 0;
                currentMode = waiting;
            }
        }
        else
        {
            Button_Draw(pointClearButton, LIGHTGRAY, BLACK);
        }
        #pragma endregion

        #pragma region Lineカテゴリー
        // ラベル
        DrawText("LINE", 20, 100, 20, BLACK);
        // ADDボタン
        if (Button_IsInside(lineAddButton, cursor.x, cursor.y))
        {
            Button_Draw(lineAddButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentMode = add_line;
            }
        }
        else
        {
            Button_Draw(lineAddButton, LIGHTGRAY, BLACK);
        }

        // DELETEボタン
        if (Button_IsInside(lineDeleteButton, cursor.x, cursor.y))
        {
            Button_Draw(lineDeleteButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentMode = delete_line;
            }
        }
        else
        {
            Button_Draw(lineDeleteButton, LIGHTGRAY, BLACK);
        }

        // CLEARボタン
        if (Button_IsInside(lineClearButton, cursor.x, cursor.y))
        {
            Button_Draw(lineClearButton, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                lineCount = 0;
                currentMode = waiting;
            }
        }
        else
        {
            Button_Draw(lineClearButton, LIGHTGRAY, BLACK);
        }
        #pragma endregion

        #pragma region Point関係のイベント
        // 点を追加するイベント
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isInsideCanvas)
        {
            if (currentMode == add_point)
            {
                if (pointCount >= pointCapacity)
                    continue;
                pts[pointCount] = cursor;
                pointCount++;
            }
            
            if( currentMode == add_line)
            {
                if(isnan(lineStartPoint.x) || isnan(lineStartPoint.y)){
                    lineStartPoint = cursor;
                }else{
                    Line2 ln = (Line2){ lineStartPoint, cursor };
                    lines[lineCount] = ln;
                    lineCount++;
                    lineStartPoint.x = NAN;
                    lineStartPoint.y = NAN;
                }
            }
        }

        // 点を削除するイベント
        if (currentMode == delete_point && isInsideCanvas)
        {
            // eps以下ならクリックされたとして扱う
            const int tolerance = 5;

            DrawCircleLines(cursor.x, cursor.y, tolerance, RED);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // カーソル近くの点を探す
                int idx = FindClosestPointIndex(&cursor, pts, pointCount, tolerance);
                if (idx != -1)
                {
                    if (pointCount == 1 || pointCount == pointCapacity)
                    {
                        pointCount--;
                    }
                    else
                    {
                        // 左に詰める。
                        for (int i = idx; i < pointCount - 1; i++)
                        {
                            pts[i] = pts[i + 1];
                        }
                        pointCount--;
                    }
                }
            }
        }
        #pragma endregion

        #pragma region Line関係のイベント
        if (currentMode == delete_line && isInsideCanvas)
        {
            // eps以下ならクリックされたとして扱う
            const int tolerance = 5;

            DrawCircleLines(cursor.x, cursor.y, tolerance, RED);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // カーソル近くの線を探す
                int idx = FindClosestLineIndex(&cursor, lines, lineCount, tolerance);
                if (idx != -1)
                {
                    if (lineCount == 1 || lineCount == pointCapacity)
                    {
                        lineCount--;
                    }
                    else
                    {
                        // 左に詰める。
                        for (int i = idx; i < lineCount - 1; i++)
                        {
                            lines[i] = lines[i + 1];
                        }
                        lineCount--;
                    }
                }
            }
        }
        #pragma endregion

        #pragma region 全体に関わる処理
        // 仕切り線
        DrawLine(window.canvasLeftX, 0, window.canvasLeftX, window.height, GRAY);

        // モード表示
        EditMode_Draw(&currentMode, window.canvasLeftX);

        // 節点数表示
        char pointCountText[256];
        sprintf(pointCountText, "  POINT COUNT: %d", pointCount);
        DrawText(pointCountText, window.canvasLeftX + 20, 40, 16, BLACK);
        // 線分数表示
        char lineCountText[256];
        sprintf(lineCountText, "  LINE COUNT: %d", lineCount);
        DrawText(lineCountText, window.canvasLeftX + 20, 60, 16, BLACK);

        // 作成済みの点を描画
        for (int i = 0; i < pointCount; i++)
        {
            DrawCircle(pts[i].x, pts[i].y, 5.0f, BLACK);
        }

        // 作成済みの線を描画
        for (int i = 0; i < lineCount; i++)
        {
            DrawLineEx(lines[i].start, lines[i].end, 2.0, BLACK);
        }

        // 線分追加時の線分を描画
        if (!isnan(lineStartPoint.x) && !isnan(lineStartPoint.y)){
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