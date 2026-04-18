#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // 点のリスト
    const int capacity = 5;
    Vector2 *vectors;
    int v_count = 0;
    if ((vectors = calloc(capacity, sizeof(Vector2))) == NULL) {
        printf("Fail..");
        return -1;
    }    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //---------------------------------------------------------------------------------
        // Vector2 position = GetMousePosition();

        Vector2 position = GetMousePosition();

        bool is_inside_button = 0 <= position.x && position.x <= 80 && 0 <= position.y && position.y <= 25;
        bool is_inside_canvas = 0 <= position.x && position.x <= screenWidth && 0 <= position.y && position.y <= screenHeight;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // Clearボタン
        DrawRectangle(0, 0, 80, 25, BLUE);
        DrawText("Clear", 20, 10, 10, WHITE);

        

        // 左クリック
        if(is_inside_canvas && !is_inside_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(v_count < capacity) {
                vectors[v_count] = position;
                v_count++;
            }
        }
        
        // Clearボタンのクリック
        if (is_inside_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            v_count = 0;
        }

        // 点を描画する
        for (int i = 0; i < v_count; i++)
        {
            DrawCircle(vectors[i].x, vectors[i].y, 5.0f, BLACK);
        }

        for (int i = 0; i < v_count - 1; i++)
        {
            Vector2 start = vectors[i];
            Vector2 end = vectors[i + 1];
            DrawLine(start.x, start.y, end.x, end.y, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}