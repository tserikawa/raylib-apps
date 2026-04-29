#include "button.h"
#include "edit_mode.h"
#include "line2.h"
#include "raylib.h"
#include "raymath.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_points(const Vector2 *cursor, const Vector2 *pts, int count, int eps)
{
    assert(eps > 0);

    for (int i = 0; i < count; i++)
    {
        int dx = cursor->x - pts[i].x;
        int dy = cursor->y - pts[i].y;
        int dxy = dx * dx + dy * dy;
        if (dxy <= eps * eps)
        {
            return i;
        }
    }
    return -1;
}

int find_line(const Vector2 *cursor, const line2 *lines, int count, int eps)
{
    assert(eps > 0);

    int lineIndex = -1;
    float minimumDistance = 10000000.0f;
    for (int i = 0; i < count; i++)
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
        TraceLog(LOG_INFO, "最短距離 %f", distance);
        if (distance < minimumDistance && distance <= (float)eps) {
            minimumDistance = distance;
            lineIndex = i;
        }
    }
    TraceLog(LOG_INFO, "line_index %d", lineIndex);
    return lineIndex;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 800;
    const int canvas_left = 240;

    SetTraceLogLevel(LOG_ALL);
    InitWindow(screenWidth, screenHeight, "GEOMETRY EDITOR");
    TraceLog(LOG_INFO, "test");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // 点のリスト
    const int capacity = 10;
    Vector2 *pts;
    int pts_count = 0;
    if ((pts = calloc(capacity, sizeof(Vector2))) == NULL)
    {
        printf("Fail..");
        return -1;
    }

    // 線分のリスト
    const int line_capacity = 10;
    line2 *lines;
    int lines_count = 0;
    if ((lines = calloc(line_capacity, sizeof(line2))) == NULL)
    {
        printf("Faile...");
        return -1;
    }
    // 未設定を表すためにNANを使う。
    Vector2 line_first_point = {NAN, NAN};

    // UI
    edit_mode mode = waiting;
    button *point_add_button = button_calloc(20, 40, 50, 20, "ADD");
    button *point_delete_button = button_calloc(80, 40, 70, 20, "DELETE");
    button *point_clear_button = button_calloc(160, 40, 60, 20, "CLEAR");
    button *line_add_button = button_calloc(20, 120, 50, 20, "ADD");
    button *line_delete_button = button_calloc(80, 120, 70, 20, "DELETE");
    button *line_clear_button = button_calloc(160, 120, 60, 20, "CLEAR");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //---------------------------------------------------------------------------------
        // マウスの位置
        Vector2 cursor = GetMousePosition();
        bool is_inside_canvas =
            canvas_left <= cursor.x && cursor.x <= screenWidth && 0 <= cursor.y && cursor.y <= screenHeight;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        // 背景
        ClearBackground(RAYWHITE);

        #pragma region Pointカテゴリー
        // ラベル
        DrawText("POINT", 20, 20, 20, BLACK);
        // ADDボタン
        if (button_is_inside(point_add_button, cursor.x, cursor.y))
        {
            button_draw(point_add_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                mode = add_point;
            }
        }
        else
        {
            button_draw(point_add_button, LIGHTGRAY, BLACK);
        }

        // DELETEボタン
        if (button_is_inside(point_delete_button, cursor.x, cursor.y))
        {
            button_draw(point_delete_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                mode = delete_point;
            }
        }
        else
        {
            button_draw(point_delete_button, LIGHTGRAY, BLACK);
        }

        // CLEARボタン
        if (button_is_inside(point_clear_button, cursor.x, cursor.y))
        {
            button_draw(point_clear_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                pts_count = 0;
                mode = waiting;
            }
        }
        else
        {
            button_draw(point_clear_button, LIGHTGRAY, BLACK);
        }
        #pragma endregion

        #pragma region Lineカテゴリー
        // ラベル
        DrawText("LINE", 20, 100, 20, BLACK);
        // ADDボタン
        if (button_is_inside(line_add_button, cursor.x, cursor.y))
        {
            button_draw(line_add_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                mode = add_line;
            }
        }
        else
        {
            button_draw(line_add_button, LIGHTGRAY, BLACK);
        }

        // DELETEボタン
        if (button_is_inside(line_delete_button, cursor.x, cursor.y))
        {
            button_draw(line_delete_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                mode = delete_line;
            }
        }
        else
        {
            button_draw(line_delete_button, LIGHTGRAY, BLACK);
        }

        // CLEARボタン
        if (button_is_inside(line_clear_button, cursor.x, cursor.y))
        {
            button_draw(line_clear_button, DARKGRAY, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                lines_count = 0;
                mode = waiting;
            }
        }
        else
        {
            button_draw(line_clear_button, LIGHTGRAY, BLACK);
        }
        #pragma endregion

        #pragma region Point関係のイベント
        // 点を追加するイベント
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_inside_canvas)
        {
            if (mode == add_point)
            {
                if (pts_count >= capacity)
                    continue;
                pts[pts_count] = cursor;
                pts_count++;
            }
            
            if( mode == add_line)
            {
                if(isnan(line_first_point.x) || isnan(line_first_point.y)){
                    line_first_point = cursor;
                }else{
                    line2 ln = (line2){ line_first_point, cursor };
                    lines[lines_count] = ln;
                    lines_count++;
                    line_first_point.x = NAN;
                    line_first_point.y = NAN;
                }
            }
        }

        // 点を削除するイベント
        if (mode == delete_point && is_inside_canvas)
        {
            // eps以下ならクリックされたとして扱う
            const int eps = 5;

            DrawCircleLines(cursor.x, cursor.y, eps, RED);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // カーソル近くの点を探す
                int idx = find_points(&cursor, pts, pts_count, eps);
                if (idx != -1)
                {
                    if (pts_count == 1 || pts_count == capacity)
                    {
                        pts_count--;
                    }
                    else
                    {
                        // 左に詰める。
                        for (int i = idx; i < pts_count - 1; i++)
                        {
                            pts[i] = pts[i + 1];
                        }
                        pts_count--;
                    }
                }
            }
        }
        #pragma endregion

        #pragma region Line関係のイベント
        if (mode == delete_line && is_inside_canvas)
        {
            // eps以下ならクリックされたとして扱う
            const int eps = 5;

            DrawCircleLines(cursor.x, cursor.y, eps, RED);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // カーソル近くの線を探す
                int idx = find_line(&cursor, lines, lines_count, eps);
                if (idx != -1)
                {
                    if (lines_count == 1 || lines_count == capacity)
                    {
                        lines_count--;
                    }
                    else
                    {
                        // 左に詰める。
                        for (int i = idx; i < lines_count - 1; i++)
                        {
                            lines[i] = lines[i + 1];
                        }
                        lines_count--;
                    }
                }
            }
        }
        #pragma endregion

        #pragma region 全体に関わる処理
        // 仕切り線
        DrawLine(canvas_left, 0, canvas_left, screenHeight, GRAY);

        // モード表示
        mode_draw_label(&mode, canvas_left);

        // 節点数表示
        char pt_cnt_txt[256];
        sprintf(pt_cnt_txt, "  POINT COUNT: %d", pts_count);
        DrawText(pt_cnt_txt, canvas_left + 20, 40, 16, BLACK);
        // 線分数表示
        char line_cnt_txt[256];
        sprintf(line_cnt_txt, "  LINE COUNT: %d", lines_count);
        DrawText(line_cnt_txt, canvas_left + 20, 60, 16, BLACK);

        // 作成済みの点を描画
        for (int i = 0; i < pts_count; i++)
        {
            DrawCircle(pts[i].x, pts[i].y, 5.0f, BLACK);
        }

        // 作成済みの線を描画
        for (int i = 0; i < lines_count; i++)
        {
            DrawLineEx(lines[i].start, lines[i].end, 2.0, BLACK);
        }

        // 線分追加時の線分を描画
        if (!isnan(line_first_point.x) && !isnan(line_first_point.y)){
            DrawLineEx(line_first_point, cursor, 1.0, BLUE);
        }
        #pragma endregion

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    button_free(line_clear_button);
    button_free(line_delete_button);
    button_free(line_add_button);
    button_free(point_clear_button);
    button_free(point_delete_button);
    button_free(point_add_button);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}