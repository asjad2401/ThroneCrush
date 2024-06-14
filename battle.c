#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "states.h"
#include "raymath.h"
#include <stdio.h>
#include <unistd.h>
#include "states.h"

// the structures used here are defined in declarations.h

// controll variable for transparency
float bgt = 0;
// controll variable for animation frames of troops
int x = 100;

#define MAX_TROOPS_IN_ARMY 100
#define SPAWN_INTERVAL 150
#define START_Y_POSITION 100

// controll variable for enemy troop spawn cool down
int nextSpawnTime = SPAWN_INTERVAL;
// track variables for enemy troop count and player troop count
int enemyTroopCount = 0;
int playerTroopCount = 0;
// delay in between two player troop spawns
float click_delay = 300;
// controll variables for time for which error messages display
int error_timer = 0;
int error_timer1 = 0;
int error_timer2 = 0;

// track variables for troops who have hit the castle
int rTroopPlayer = 0;
int rTroopEnemy = 0;

// initial position of troops outside screen
int spawnXenemy = 1000;
int spawnXplayer = -1000;

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
        spawnXenemy = GetRandomValue(240, 1000);
        // the rectangle and texture(picture) for the troop structure is set here
        enemyTroops[enemyTroopCount].place = (Rectangle){spawnXenemy, START_Y_POSITION, textureManager->textures[18].width, textureManager->textures[18].height};
        enemyTroops[enemyTroopCount].picts = textureManager->textures[18];
        enemyTroops[enemyTroopCount].currentFrame = 0; // current frame is initialized
        enemyTroopCount++;                             // troop count is increased after every spawn
    }
}

// this function mostly works like the spawnEnemyTroop function
//  this function takes the x and y coords of mouse click as well
void spawnPlayerTroop(TextureManager *textureManager, float clickY, float clickX)
{
    Vector2 mouse = GetMousePosition();
    if (playerTroopCount < MAX_TROOPS_IN_ARMY)
    {
        // the spawn position is determined by where the mouse was clicked
        int spawnXplayer = mouse.x - 20;
        playerTroops[playerTroopCount].place = (Rectangle){spawnXplayer, clickY, enemyTroops[1].picts.width, enemyTroops[1].picts.height};
        playerTroops[playerTroopCount].picts = textureManager->textures[22];
        playerTroopCount++;
    }
}

// this function simulates the battle
int battle(GameState *state, TextureManager *textureManager, int playerTroopsMax, int enemyTroopsMax, float troopspeed, float spawnInterval)
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
    click_delay += (spawnInterval) / 15;

    BeginDrawing();
    // background is drawn
    DrawTextureEx(textureManager->textures[17], (Vector2){0, 0}, 0, scale, (Color){255, 255, 255, bgt});

    // this loop goes through the array of troops and performs movement as well as animation
    for (int i = 0; i < enemyTroopsMax; i++)
    {
        enemyTroops[i].place.y += troopspeed; // Move enemy troops down

        // Calculate the source rectangle of troops based on the current frame
        Rectangle sourceRect = {
            enemyTroops[i].currentFrame * (enemyTroops[i].picts.width / 4),
            0,
            enemyTroops[i].picts.width / 4,
            enemyTroops[i].picts.height};

        // Draw the current frame of troop
        DrawTextureRec(enemyTroops[i].picts, sourceRect, (Vector2){enemyTroops[i].place.x, enemyTroops[i].place.y}, WHITE);

        // Update the current frame for the next iteration of animation
        if (x % 35 == 0)
            enemyTroops[i].currentFrame = (enemyTroops[i].currentFrame + 1) % 4;
    }

    // run loop to move all troops in the array one step as well as move the animation
    for (int i = 0; i < playerTroopsMax; i++)
    {
        playerTroops[i].place.y -= 0.8; // Move player troops up the screen

        Rectangle sourceRect1 = {
            enemyTroops[i].currentFrame * (enemyTroops[i].picts.width / 4),
            0,
            enemyTroops[i].picts.width / 4,
            enemyTroops[i].picts.height};
        DrawTextureRec(playerTroops[i].picts, sourceRect1, (Vector2){playerTroops[i].place.x, playerTroops[i].place.y}, WHITE);
        if (x % 35 == 0)
            playerTroops[i].currentFrame = (playerTroops[i].currentFrame + 1) % 4;
    }

    Vector2 mousePosition = GetMousePosition();

    // this block checks for various cinditions of player troop spawn
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Check if the troop count is less than the maximum allowed
        if (playerTroopCount < playerTroopsMax)
        {
            // Check if the mouse is clicked within a specified rectangle

            Vector2 mousePosition = GetMousePosition();

            if (mousePosition.y > screenHeight / 2 && mousePosition.x > 240 && mousePosition.x < 1015)
            {
                // Check if the timer is greater than or equal to the spawn delay
                if (click_delay >= 300)
                {
                    // Spawn a troop at the mouse position
                    spawnPlayerTroop(textureManager, mousePosition.y, mousePosition.x);

                    // Reset the timer
                    click_delay = 0;
                }
                else
                {
                    // Display an error message if the timer condition is not met
                    // (troop cannot be spawned yet)
                    error_timer = 50;
                }
            }
            else
            {
                // Display an error message if the mouse is clicked outside the spawn area
                error_timer1 = 50;
            }
        }
        else
        {
            // Display an error message if the maximum troop count is reached
            error_timer2 = 50;
        }
    }

    // error message for delay
    if (error_timer > 1)
    {
        DrawText("Wait for delay", 100, 900, 35, WHITE);
        error_timer--;
    }

    // error for wrong placement
    if (error_timer1 > 1)
    {
        DrawText("Can't place there", 500, 900, 35, WHITE);
        error_timer1--;
    }

    //error if you run out of troops
    if (error_timer2 > 1)
    {
        DrawText("No more troops", 900, 900, 35, WHITE);
        error_timer2--;
    }

    // checks for delay between enemy spawn and if there is enough delay, enemy spawn function is called
    if (x > nextSpawnTime)
    {
        spawnEnemyTroop(textureManager);
        //reset the count
        nextSpawnTime = nextSpawnTime + spawnInterval;
    }

    // draw the castle health of both castles
    DrawRectangle(570, 50, 200, 20, GRAY);
    DrawRectangle(570, 950, 200, 20, GRAY);
    DrawRectangle(570, 50, 200 - (20 * rTroopPlayer), 20, GREEN);
    DrawRectangle(570, 950, 200 - (20 * rTroopEnemy), 20, GREEN);

    EndDrawing();

    // this nested loop checks for collisions between player and enemy troops
    for (int i = 0; i < enemyTroopsMax; i++)
    {
        for (int j = 0; j < playerTroopsMax; j++)
        {
            // this condition check if ith enemy troop collides with jth player troop, but since the image of troop is wider than its
            // actual size (to accomodate the animation), we divide the collision rectangle by frame number ie 5
            if (CheckCollisionRecs((Rectangle){enemyTroops[i].place.x, enemyTroops[i].place.y, enemyTroops[i].place.width / 5, enemyTroops[i].place.height}, (Rectangle){playerTroops[j].place.x, playerTroops[j].place.y, playerTroops[j].place.width / 5, playerTroops[j].place.height}))
            {

                // Randomly decide whether both troops die or only one
                if (GetRandomValue(0, 1) == 0)
                {
                    // we kill the troops by making them disappear.. this happens when their position is moved out of screen
                    //  kill both troops
                    enemyTroops[i].place.y = -1000;  // Move enemy troop off-screen
                    playerTroops[j].place.y = -1000; // Move player troop off-screen
                }
                else
                {
                    // Disappear one troop
                    if (GetRandomValue(0, 1) == 0)
                    {
                        enemyTroops[i].place.y = 1000; // Move enemy troop off-screen
                    }
                    else
                    {
                        playerTroops[j].place.y = -1000; // Move player troop off-screen
                    }
                }
            }
        }

        // check if any of your troops has hit enemy tower
        if (CheckCollisionRecs((Rectangle){playerTroops[i].place.x, playerTroops[i].place.y, playerTroops[i].place.width / 5, playerTroops[i].place.height}, (Rectangle){0, 90, screenWidth * scale, 2}))
        {
            playerTroops[i].place.y = -1000;
            // count the number of troops who hit the castle
            rTroopPlayer++;
        }

        // check if any of thr enemy troops has hit your tower
        if (CheckCollisionRecs((Rectangle){enemyTroops[i].place.x, enemyTroops[i].place.y, enemyTroops[i].place.width / 5, enemyTroops[i].place.height}, (Rectangle){0, 900, screenWidth * scale, 2}))
        {
            enemyTroops[i].place.y = 1000;
            // count the number of troops who hit the castle
            rTroopEnemy++;
        }
    }

    // check for winning conditions, this checks if 10 enemy troops have hit your wall
    if (rTroopEnemy == 10)
    {
        // loose
        lost(state, textureManager);
    }
    else if (rTroopPlayer == 10) // this checks if your 10 troops have hit enemy wall
    {

        // win

        won(state, textureManager);

        // check the condition where both sides run out of troops
        if (rTroopEnemy != 10 && rTroopPlayer != 10 && playerTroopCount == playerTroopsMax && enemyTroopCount == enemyTroopsMax)
        {
            if (rTroopEnemy > rTroopPlayer)
            {
                // loose
                lost(state, textureManager);
            }
            else if (rTroopEnemy == rTroopPlayer)
            {
                draw(state, textureManager);
                // draw
            }
            else if (rTroopEnemy < rTroopPlayer)
            {
                won(state, textureManager);
                // win
            }
        }
    }
}

int winloseCount = 0; // variable to pose delay while win or lose screen is displayed
// this function is called when battle ends.. this resets all the values of variables in order to reuse them for next battle
void resetVariables()
{
    bgt = 0;
    x = 100;
    nextSpawnTime = SPAWN_INTERVAL;
    for (int i = 0; i < playerTroopCount; i++)
    {
        playerTroops[i].place.y = -1000;
    }
    for (int i = 0; i < enemyTroopCount; i++)
    {
        enemyTroops[i].place.y = 1000;
    }
    enemyTroopCount = 0;
    playerTroopCount = 0;
    click_delay = 300;
    error_timer = 0;
    error_timer1 = 0;
    error_timer2 = 0;
    rTroopPlayer = 0;
    rTroopEnemy = 0;
    spawnXenemy = 1000;
    spawnXplayer = -1000;
    winloseCount = 0;
}


// win or loose functions modify the nations array to keep track of which nations you have conquered
//if you lose battle
void lost(GameState *state, TextureManager *textureManager)
{
    BeginDrawing();
    DrawText("You Lost ", 500, 500, 50, RED);
    DrawRectangle(570, 950, 200, 20, GRAY);

    // this condition is so that if you are at any castle, you'll loose the previous castle if you lost the battle.
    switch (*state)
    {

    case BATTLEMODE2:
        DrawTextEx(textureManager->myfont, "You lost Castle Bug Bridge", (Vector2){700, 700}, 35, 5, WHITE);
        Nations[0] = 0;
        break;
    case BATTLEMODE3:
        DrawTextEx(textureManager->myfont, "You lost Castle Mid Town", (Vector2){700, 700}, 35, 5, WHITE);
        Nations[1] = 0;
        break;
    case BATTLEMODE4:
        DrawTextEx(textureManager->myfont, "You lost Castle BoatBar", (Vector2){700, 700}, 35, 5, WHITE);
        Nations[2] = 0;
        break;
    case BATTLEMODE5:
        DrawTextEx(textureManager->myfont, "You lost Castle Gaurdon", (Vector2){700, 700}, 35, 5, WHITE);
        Nations[3] = 0;
        break;
    }
    EndDrawing();

   

    winloseCount++;
    if (winloseCount > 300)
    {
        *state = PLAYMENU;
        // reset all variables
        resetVariables();
        return;
    }
    lost(state, textureManager);
}
// if you win a battle
void won(GameState *state, TextureManager *textureManager)
{
    BeginDrawing();
    DrawText("You Won ", 500, 500, 50, RED);
    DrawRectangle(570, 50, 200, 20, GRAY);
    EndDrawing();
    // reset all variables

    switch (*state)
    {
    case BATTLEMODE2:
        Nations[1] = 1;
        break;
    case BATTLEMODE3:
        Nations[2] = 1;
        break;
    case BATTLEMODE4:
        Nations[3] = 1;
        break;
    case BATTLEMODE5:
        Nations[4] = 1;
        break;
    }
    winloseCount++;
    if (winloseCount > 300)
    {
        *state = PLAYMENU;
        resetVariables();
        return;
    }
    won(state, textureManager);
}
void draw(GameState *state, TextureManager *textureManager)
{
    BeginDrawing();
    DrawText("Its a draw ", 500, 500, 50, RED);
    EndDrawing();
    // reset all variables

    winloseCount++;
    if (winloseCount > 300)
    {
        // after a set time, battle gamestate exits and we return to play menu
        *state = PLAYMENU;
        resetVariables();
        return;
    }
    // recursion, in order to keep the message displayed for a set time.
    draw(state, textureManager);
}
