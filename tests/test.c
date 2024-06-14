#include "raylib.h"
#include<ctype.h>
#include<stdlib.h>

float x = strtoull


#define NUM_RECTANGLES 3

typedef struct {
    Rectangle rectangles[NUM_RECTANGLES];
    Color color;
} IrregularRegion;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Irregular Region");

    // Create an irregular region
    IrregularRegion irregularRegion;
    irregularRegion.rectangles[0] = (Rectangle){ 100, 100, 200, 50 };
    irregularRegion.rectangles[1] = (Rectangle){ 250, 150, 50, 150 };
    irregularRegion.rectangles[2] = (Rectangle){ 200, 250, 150, 50 };
    irregularRegion.color = RED;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw irregular region
        for (int i = 0; i < NUM_RECTANGLES; i++)
        {
            DrawRectangle(irregularRegion.rectangles[i].x, irregularRegion.rectangles[i].y,
                          irregularRegion.rectangles[i].width, irregularRegion.rectangles[i].height,
                          irregularRegion.color);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}