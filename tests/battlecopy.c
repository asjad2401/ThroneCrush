#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "states.h"
#include "raymath.h"
#include <stdio.h>
#include <unistd.h>
#include "states.h"

float bgt = 0;
float troopMove = 200;
int x = 100;
int y;

#define MAX_TROOPS_IN_ARMY 100
#define SPAWN_INTERVAL 150
#define START_Y_POSITION 100

int nextSpawnTime = SPAWN_INTERVAL;
int collisionCooldown = 0;
int enemyTroopCount = 0;
int playerTroopCount = 0;
float click_delay = 300;
int error_timer = 0;
int error_timer1 = 0;
// create a structure for enemy troop that contains its rectangle and its picture
typedef struct
{
    Rectangle place;
    Texture2D picts;
    int currentFrame; // this keeps track of the current frame, there are 5 frames in the picture, this helps with walking animations.
} EnemyTroop;

// create a structure for player troops
typedef struct
{
    Rectangle place;
    Texture2D picts;
    int currentFrame;
} PlayerTroop;

// these arrays contain a set number of troops (that is an array of structures) to keep track of how many troops are deployed
EnemyTroop enemyTroops[MAX_TROOPS_IN_ARMY];
PlayerTroop playerTroops[MAX_TROOPS_IN_ARMY];

// this function when called, places a structure of enemytroop inside the array of enemy troops
void spawnEnemyTroop(TextureManager *textureManager)
{
    // check if the number of troops hasnt exceeded the limit
    if (enemyTroopCount < MAX_TROOPS_IN_ARMY)
    {
        // this is the x coordinate generated randomly for spawning the enemy troop
        int spawnX = GetRandomValue(200, 1000);

        // the rectangle and texture(picture) for the troop structure is set here
        enemyTroops[enemyTroopCount].place = (Rectangle){spawnX, START_Y_POSITION, textureManager->textures[18].width, textureManager->textures[18].height};
        enemyTroops[enemyTroopCount].picts = textureManager->textures[18];

        enemyTroops[enemyTroopCount].currentFrame = 0; // current frame is initialized
        enemyTroopCount++;                             // troop count is increased after every spawn
    }
}

// this function mostly works like the spawnEnemyTroop function
//  this function takes the x and y coords of mouse click as well
void spawnPlayerTroop(TextureManager *textureManager, float clickY, float clickX)
{
    if (playerTroopCount < MAX_TROOPS_IN_ARMY)
    {
        // the spawn position is determined by where the mouse was clicked
        int spawnX = clickX - 20;
        playerTroops[playerTroopCount].place = (Rectangle){spawnX, clickY, enemyTroops[1].picts.width, enemyTroops[1].picts.height};
        playerTroops[playerTroopCount].picts = enemyTroops[1].picts;
        playerTroopCount++;
    }
}

// this function simulated the battle
int battle2(GameState *state, TextureManager *textureManager)
{

    // this block causes the fade in effect
    if (bgt < 255)
    {
        bgt += 0.2;
    }
    else if (bgt >= 255)
    {
        bgt = 255;
    }

    // x is a counter set to controll the animation speed for troops walking animation
    x += 1;
    // click delay controlls how much you have to wait in between two click to spawn a troop of player
    click_delay += 3;

    BeginDrawing();

    // background and text is drawn
    DrawTextureEx(textureManager->textures[17], (Vector2){0, 0}, 0, scale, (Color){255, 255, 255, bgt});
    DrawTextEx(textureManager->myfont, "Your troops: 100 ", (Vector2){40, 120}, 40, 5, BLACK);
    DrawTextEx(textureManager->myfont, "Enemy troops: 110 ", (Vector2){40, 180}, 40, 5, BLACK);

    // this loop goes through the array of troops and performs movement as well as animation
    for (int i = 0; i < enemyTroopCount; i++)
    {
        enemyTroops[i].place.y += 0.8; // Move enemy troops down

        // Calculate the source rectangle based on the current frame
        Rectangle sourceRect = {
            enemyTroops[i].currentFrame * (enemyTroops[i].picts.width / 5),
            0,
            enemyTroops[i].picts.width / 5,
            enemyTroops[i].picts.height};

        // Draw the current frame according to moved place and the animated frame
        DrawTextureRec(enemyTroops[i].picts, sourceRect, (Vector2){enemyTroops[i].place.x, enemyTroops[i].place.y}, WHITE);

        // Update the current frame in order to perform animation
        if (x % 35 == 0)
            enemyTroops[i].currentFrame = (enemyTroops[i].currentFrame + 1) % 5;
    }

    // this loop goes through the array of player troops and performs movement as well as animation
    for (int i = 0; i < playerTroopCount; i++)
    {

        playerTroops[i].place.y -= 0.8; // Move player troops up

        // define source rectangle for animation
        Rectangle sourceRect1 = {
            enemyTroops[i].currentFrame * (enemyTroops[i].picts.width / 5),
            0,
            enemyTroops[i].picts.width / 5,
            enemyTroops[i].picts.height};
        // draw player troop as per the movement and animation
        DrawTextureRec(playerTroops[i].picts, sourceRect1, (Vector2){playerTroops[i].place.x, playerTroops[i].place.y}, WHITE);
        if (x % 35 == 0)
            playerTroops[i].currentFrame = (playerTroops[i].currentFrame + 1) % 5;
    }

    // this part of code checks when to spawn the player troop
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // first we check if the mouse button was clicked
    {
        Vector2 mousePosition = GetMousePosition(); // we track the mouse position continuously

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();

            if (mousePosition.y > screenHeight / 2)
            {
                if (click_delay > 300 && mousePosition.x > 250 && mousePosition.x < 1000)
                {
                    spawnPlayerTroop(textureManager, mousePosition.y, mousePosition.x);
                    click_delay = 0;
                }
                else
                {
                    error_timer = 50;
                }
            }
        }

        // error message for delay
        if (error_timer > 1)
        {
            DrawText("Wait for delay", 500, 700, 35, WHITE);
            error_timer--;
        }

        // error message for placing troop outside
        if (error_timer1 > 1)
        {
            DrawText("Cant place troop here", 100, 700, 35, WHITE);
            error_timer1--;
        }



        if (CheckCollisionRecs(enemyTroops[0].place, (Rectangle){0, 1120, screenWidth, 1}))
        {
            enemyTroopCount = 0;
            playerTroopCount = 0;
            x = 100;
            *state = PLAYMENU;
        }

        EndDrawing();
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            enemyTroopCount = 0;
            playerTroopCount = 0;
            *state = PLAYMENU;
        }

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                // loop through both arrays
                // this check if any two one of the enemy troops collides with any troop of player
                if (CheckCollisionRecs((Rectangle){enemyTroops[i].place.x, enemyTroops[i].place.y, enemyTroops[i].place.width / 5, enemyTroops[i].place.height}, (Rectangle){playerTroops[j].place.x, playerTroops[j].place.y, playerTroops[j].place.width / 5, playerTroops[j].place.height}))
                {
                    // Randomly decide whether both troops die or only one
                    if (GetRandomValue(0, 1) == 0)
                    {
                        // to kill a troop, we just displace it out of the screen
                        enemyTroops[i].place.y = -1000;  // Move enemy troop off-screen
                        playerTroops[j].place.y = -1000; // Move player troop off-screen
                    }
                    else
                    {
                        // kill one troop
                        if (GetRandomValue(0, 1) == 0)
                        {
                            enemyTroops[i].place.y = -1000; // Move enemy troop off-screen
                        }
                        else
                        {
                            playerTroops[j].place.y = -1000; // Move player troop off-screen
                        }
                    }
                }
            }
        }
    }
}

int battle3(GameState *state, TextureManager *textureManager)
{

    if (bgt < 255)
    {
        bgt += 1.2;
    }
    else if (bgt >= 255)
        bgt = 255;

    BeginDrawing();
    DrawTextureEx(textureManager->textures[17], (Vector2){0, 0}, 0, scale, (Color){bgt, bgt, bgt, bgt});

    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        *state = PLAYMENU;
        return 0;
    }
}
int battle4(GameState *state, TextureManager *textureManager)
{

    if (bgt < 255)
    {
        bgt += 1.2;
    }
    else if (bgt >= 255)
        bgt = 255;

    BeginDrawing();
    DrawTextureEx(textureManager->textures[17], (Vector2){0, 0}, 0, scale, (Color){bgt, bgt, bgt, bgt});

    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        *state = PLAYMENU;
        return 0;
    }
}
int battle5(GameState *state, TextureManager *textureManager)
{

    if (bgt < 255)
    {
        bgt += 1.2;
    }
    else if (bgt >= 255)
        bgt = 255;

    BeginDrawing();
    DrawTextureEx(textureManager->textures[17], (Vector2){0, 0}, 0, scale, (Color){bgt, bgt, bgt, bgt});

    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        *state = PLAYMENU;
        return 0;
    }
}
