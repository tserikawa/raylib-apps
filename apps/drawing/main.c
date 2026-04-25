#include "button.h"
#include "edit_mode.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    InitWindow(screenWidth, screenHeight, "GEOMETRY EDITOR");

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

    // UI
    edit_mode mode = waiting;
    button *point_add_button = button_calloc(20, 40, 50, 20, "ADD");
    button *point_delete_button = button_calloc(80, 40, 70, 20, "DELETE");
    button *point_clear_button = button_calloc(160, 40, 60, 20, "CLEAR");

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

        // Pointカテゴリー
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

        // 点を追加するイベント
        if (mode == add_point && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_inside_canvas)
        {
            if (pts_count >= capacity)
                continue;
            pts[pts_count] = cursor;
            pts_count++;
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

        // 仕切り線
        DrawLine(canvas_left, 0, canvas_left, screenHeight, GRAY);

        // モード表示
        mode_draw_label(&mode, canvas_left);

        // 節点数表示
        char pt_cnt_txt[256];
        sprintf(pt_cnt_txt, "  POINT COUNT: %d", pts_count);
        DrawText(pt_cnt_txt, canvas_left + 20, 40, 16, BLACK);

        // 点を描画
        for (int i = 0; i < pts_count; i++)
        {
            DrawCircle(pts[i].x, pts[i].y, 5.0f, BLACK);
        }

        // Lineカテゴリー
        // DrawText("Line", 20, 80, 15, BLACK);

        // // Clearボタン
        // DrawRectangle(0, 0, 80, 25, BLUE);
        // DrawText("Clear", 20, 10, 10, WHITE);

        // // Pointカテゴリー

        // // 左クリック
        // if(is_inside_canvas && !is_inside_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        //     if(v_count < capacity) {
        //         pts[v_count] = position;
        //         v_count++;
        //     }
        // }

        // // Clearボタンのクリック
        // if (is_inside_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        // {
        //     v_count = 0;
        // }

        // // 点を描画する
        // for (int i = 0; i < v_count; i++)
        // {
        //     DrawCircle(pts[i].x, pts[i].y, 5.0f, BLACK);
        // }

        // for (int i = 0; i < v_count - 1; i++)
        // {
        //     Vector2 start = pts[i];
        //     Vector2 end = pts[i + 1];
        //     DrawLine(start.x, start.y, end.x, end.y, BLACK);
        // }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    button_free(point_clear_button);
    button_free(point_delete_button);
    button_free(point_add_button);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}