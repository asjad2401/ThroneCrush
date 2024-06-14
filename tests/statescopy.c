// states.c
#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "states.h"
#include "raymath.h"

void mainmenu(Texture2D background, Button *playButton, Button *optionsButton)
{
    mousePoint = GetMousePosition();
    mouseTrack(&mousePoint, playButton);
    mouseTrack(&mousePoint, optionsButton);

    Rectangle sourceMainrec = {0, 0, (float)playButton->image.width, playButton->image.height / 3};
    sourceMainrec.y = playButton->buttonState * (float)playButton->image.height / 3;
    Rectangle sourceMainrec1 = {0, 0, (float)optionsButton->image.width, optionsButton->image.height / 3};
    sourceMainrec1.y = optionsButton->buttonState * (float)optionsButton->image.height / 3;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw background and buttons
    DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);
    DrawTextureRec(playButton->image, sourceMainrec, (Vector2){playButton->pos.x, playButton->pos.y}, RAYWHITE);
    DrawTextureRec(optionsButton->image, sourceMainrec1, (Vector2){optionsButton->pos.x, optionsButton->pos.y}, RAYWHITE);

    EndDrawing();
}

void playmenu(Texture2D background, Button *battleButton)
{
    mousePoint = GetMousePosition();
    mouseTrack(&mousePoint, battleButton);

    Rectangle sourceMainrec = {0, 0, (float)battleButton->image.width, battleButton->image.height / 3};
    sourceMainrec.y = battleButton->buttonState * (float)battleButton->image.height / 3;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw background and buttons
    DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);
    DrawTextureRec(battleButton->image, sourceMainrec, (Vector2){battleButton->pos.x, battleButton->pos.y}, RAYWHITE);

    EndDrawing();
}



int x = 0, y = 0;


void Battle(Texture2D background, Rectangle *textureRect , Rectangle *cameraRect)
{
    Texture2D country1 = LoadTexture("country1.png");
    Maptexture textures[2];
    textures[0].texture = background;
    textures[0].rect = *textureRect;
    Rectangle country1rect = (Rectangle){300,300, country1.width, country1.height};

    textures[1].texture = country1;
    textures[2].rect = country1rect;
 
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Update camera zoom
        cam.zoom += wheel * 0.125f;

        if (cam.zoom < 1.0f)
            cam.zoom = 1.0f;

        if (cam.zoom > 4.0f)
            cam.zoom = 4.0f;

        // Adjust camera rectangle size based on zoom
        cameraRect->width = screenWidth / cam.zoom;
        cameraRect->height = screenHeight / cam.zoom;
    }

    if (IsKeyDown(KEY_RIGHT))
        cameraRect->x += 10.0f;
    if (IsKeyDown(KEY_LEFT))
        cameraRect->x -= 10.0f;
    if (IsKeyDown(KEY_UP))
        cameraRect->y -= 10.0f;
    if (IsKeyDown(KEY_DOWN))
        cameraRect->y += 10.0f;

    // Update texture rectangle size based on the background texture and camera zoom
    textureRect->width = background.width * cam.zoom;
    textureRect->height = background.height * cam.zoom;

    // Update camera position
    cam.target = (Vector2){cameraRect->x + cameraRect->width / 2, cameraRect->y + cameraRect->height / 2};
    cam.offset = (Vector2){screenWidth / 2, screenHeight / 2};

    for (int i =0; i<2; i++){
        textures[i].rect.width = textures[i].texture.width * cam.zoom;
        textures[i].rect.height = textures[i].texture.height * cam.zoom;
    }
    // Adjust camera position to stay within the texture bounds
    AdjustCameraToBounds(cameraRect, textureRect);


    // Drawing
    BeginDrawing();
    ClearBackground(MYBLUE);

    BeginMode2D(cam);

    //DrawTexturePro(background, (Rectangle){0, 0, background.width, background.height}, (*textureRect), (Vector2){x, y}, 0, WHITE);
    // Draw other things
    for(int i=0; i<2;i++){
        DrawTexturePro(textures[i].texture, (Rectangle){0,0,textures[i].texture.width,textures[i].texture.height},textures[i].rect, (Vector2){x,y},0,WHITE);
    }

    EndMode2D();

    DrawText("Use arrow keys to move, mouse wheel to zoom", 2, 2, 20, BLACK);

    EndDrawing();
    EndDrawing();
}
