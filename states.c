// states.c
#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "states.h"
#include "raymath.h"
#include <stdio.h>
#include <unistd.h>
#include "battle.h"

// an array of length 5 is used to keep track of conquered and un conquered nations
// 1 represents conquered and 0 represents not.

void quitmenu(GameState *state, TextureManager *textureManager)
{

    BeginDrawing();

    DrawTextureEx(textureManager->textures[3], (Vector2){0, 0}, 0, scale, WHITE);
    DrawRectangle(0, 0, screenWidth * scale, screenHeight * scale, (Color){0, 0, 0, 150});
    DrawTextEx(textureManager->myfont, "   Press Enter to quit", (Vector2){screenWidth / 2 - 410, screenHeight / 2 - 100}, 80, 15, WHITE);
    DrawTextEx(textureManager->myfont, "Press Backspace to go back", (Vector2){screenWidth / 2 - 480, screenHeight / 2 + 50}, 80, 15, WHITE);

    if (IsKeyPressed(KEY_ENTER))
        CloseWindow();
    else if (IsKeyPressed(KEY_BACKSPACE))
        *state = MAINMENU;

    EndDrawing();
}
// main menu

void optionsmenu(GameState *state, TextureManager *textureManager)
{

    BeginDrawing();

    DrawTextureEx(textureManager->textures[1], (Vector2){0, 0}, 0, scale, WHITE);
    DrawRectangle(0, 0, screenWidth * scale, screenHeight * scale, (Color){0, 0, 0, 150});
    // todo: add more options
    DrawTextEx(textureManager->myfont, "How To Play", (Vector2){screenWidth / 2 - 480, screenHeight / 2 - 475}, 80, 15, WHITE);
    
    DrawTextEx(textureManager->myfont, "The Game Starts With One Castle Under ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 400},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "Your Controll", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 340},50, 15, WHITE);
    
    DrawTextEx(textureManager->myfont, "Your Goal Is to Conquer All 5 Castles ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 280},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "On The Map", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 220},50, 15, WHITE);

    DrawTextEx(textureManager->myfont, "You Can Only Attack A Castle If you ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 160},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "Have Conquered Previous One", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 100},50, 15, WHITE);

    DrawTextEx(textureManager->myfont, "During The Battle You Can Place Your ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 - 40},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "Troops On Screen", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +20},50, 15, WHITE);

    DrawTextEx(textureManager->myfont, "You Can Not Place Troops Outside Lower ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +80},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "Half Of Arena", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +140},50, 15, WHITE);
    
    DrawTextEx(textureManager->myfont, "There Is A Delay Between Two Spawns, ", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +200},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "You Can't Spam!!", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +260},50, 15, WHITE);
    
    DrawTextEx(textureManager->myfont, "If You Have All 5 Castles, You Win!", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +320},50, 15, WHITE);
    DrawTextEx(textureManager->myfont, "If You Loose All 5 Castles, You Loose!", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +380},50, 15, WHITE);




    DrawTextEx(textureManager->myfont, "Press Backspace to go back", (Vector2){screenWidth / 2 - 550, screenHeight / 2 +450},40, 15, WHITE);

    if (IsKeyPressed(KEY_BACKSPACE))
        *state = MAINMENU;

    EndDrawing();
}
void mainmenu(GameState *state, TextureManager *textureManager)
{

    /*createbuttons
      i first declare a variable (name of button) with data type "Button" (which is a struct).
      then i call createbutton function (from buttons.c) to create a button. That function returns
      a button which is stored in "variable name" as a button struct
    */

    // buttons mainly serve to toggle between states
    Button playbutton = createButton(524, 293, textureManager->textures[2].width, textureManager->textures[2].height);
    Button optionsbutton = createButton(524, 580, textureManager->textures[2].width, textureManager->textures[2].height);
    Button quitbutton = createButton(524, 867, textureManager->textures[2].width, textureManager->textures[2].height);

    BeginDrawing();
    // in every iteration, back ground is cleared (refreshed) at the set refresh rate i.e. 60 hz

    // i draw buttons as textures using attributes of button structs
    DrawTextureEx(textureManager->textures[1], (Vector2){0, 0}, 0, scale, WHITE);
    DrawTexture(textureManager->textures[2], playbutton.posX, playbutton.posY, WHITE);
    DrawTexture(textureManager->textures[2], screenWidth / 2 - textureManager->textures[2].width / 2, screenHeight / 2 - textureManager->textures[2].height / 2, WHITE);
    DrawTexture(textureManager->textures[2], screenWidth / 2 - textureManager->textures[2].width / 2, screenHeight / 2 + textureManager->textures[2].height - 50, WHITE);

    // text is also displayed according to button structs.
    DrawTextEx(textureManager->myfont, "Play Game", (Vector2){playbutton.textXpos, playbutton.textYpos}, 35, 6, WHITE);
    DrawTextEx(textureManager->myfont, "How To Play", (Vector2){optionsbutton.textXpos -20, optionsbutton.textYpos}, 35, 6, WHITE);
    DrawTextEx(textureManager->myfont, "Quit Game", (Vector2){quitbutton.textXpos, quitbutton.textYpos}, 35, 6, WHITE);
    EndDrawing();

    // get the current position of mouse as a vector (with every iteraction, so we track the mouse pointer)
    Vector2 mouse = GetMousePosition();

    // check if mouse collides with any of the buttons
    // for play button
    if (CheckCollisionPointRec(mouse, (Rectangle){playbutton.posX, playbutton.posY, 291, 128}))
    {
        // during collision, checks if button is pressed, if so, change the gamestate accordingly
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            // toggle the state accordingly
            *state = LOADSCREEN;
    }
    // for options button
    if (CheckCollisionPointRec(mouse, (Rectangle){screenWidth / 2 - optionsbutton.ButtonWidth / 2, screenHeight / 2 - optionsbutton.ButtonHeight / 2, 291, 128}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = OPTIONSMENU;
    }
    // for quit button
    if (CheckCollisionPointRec(mouse, (Rectangle){screenWidth / 2 - quitbutton.ButtonWidth / 2, screenHeight / 2 - quitbutton.ButtonHeight / 2 + 287 / 2, 291, 128}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = QUITS;
    }
}

// transparency controll variables for loading screen
float bgtrans = 0; // background transparency
float loadbar = 0; // loading bar length

// loading screen
int loadingscreen(GameState *state, TextureManager *textureManager)
{

    // controll system for changing transparency of loading screen
    if (bgtrans < 70)
        bgtrans += 1.5f;
    else if (bgtrans >= 70)
        bgtrans = 70;

    if (loadbar < 500)
        loadbar += 5;
    else
    {
        bgtrans = 0;
        *state = PLAYMENU;
    }

    BeginDrawing();

    // draw background and loading bar using controll variables
    DrawTextureEx(textureManager->textures[4], (Vector2){0, 0}, 0, scale, (Color){bgtrans, bgtrans, bgtrans, bgtrans});
    DrawRectangle(screenWidth / 2 - 250, 875, 500, 30, (Color){255, 255, 255, bgtrans});
    DrawRectangle(screenWidth / 2 - 250, 875, loadbar, 30, (Color){0, 228, 48, 150});
    // todo : add tips
    EndDrawing();
}

float bgtrans1 = 0;
float loadbar1 = 0;
int firstloadingscreen(GameState *state, TextureManager *textureManager)
{

    // controll system for changing transparency of loading screen
    if (bgtrans1 < 70)
        bgtrans1 += 1.5f;
    else if (bgtrans1 >= 70)
        bgtrans1 = 70;

    if (loadbar1 < 500)
        loadbar1 += 5;
    else
    {
        bgtrans1 = 0;
        *state = MAINMENU;
    }

    BeginDrawing();

    // draw background and loading bar using controll variables
    DrawTextureEx(textureManager->textures[4], (Vector2){0, 0}, 0, scale, (Color){bgtrans1, bgtrans1, bgtrans1, bgtrans1});
    DrawRectangle(screenWidth / 2 - 250, 875, 500, 30, (Color){255, 255, 255, bgtrans1});
    DrawRectangle(screenWidth / 2 - 250, 875, loadbar1, 30, (Color){0, 228, 48, 150});
    // todo : add tips
    EndDrawing();
}

// transparency controll variables for playmenu
float playbgtrans = 0;
// playmenu
void playmenu(GameState *state, TextureManager *textureManager)
{

    // controlling transparency of playmenu background to show fade in effect
    if (playbgtrans < 255)
    {
        playbgtrans += 1.2;
    }
    else if (playbgtrans > 255)
        playbgtrans = 255;

    // backspace will let you escape to main menu
    if (IsKeyPressed(KEY_X))
    {
        *state = MAINMENU;
        bgtrans = 0;
        loadbar = 0;
    }
    // tracking th mouse cursor
    Vector2 mouse = GetMousePosition();

    BeginDrawing();

    // draw the background map
    DrawTextureEx(textureManager->textures[5], (Vector2){0, 0}, 0, scale, (Color){255, 255, 255, playbgtrans});
    // write names of all 5 castles
    DrawRectangle(850, 850, 180, 35, (Color){255, 255, 255, 120});
    DrawTextEx(textureManager->myfont, "BugBridge", (Vector2){852, 852}, 33, 7, BLACK);

    DrawRectangle(238, 758, 180, 35, (Color){255, 255, 255, 120});
    DrawTextEx(textureManager->myfont, "Mid-Town", (Vector2){240, 760}, 35, 7, BLACK);

    DrawRectangle(268, 548, 140, 35, (Color){255, 255, 255, 120});
    DrawTextEx(textureManager->myfont, "Boatbar", (Vector2){270, 550}, 35, 7, BLACK);

    DrawRectangle(328, 168, 140, 35, (Color){255, 255, 255, 120});
    DrawTextEx(textureManager->myfont, "Gaurdon", (Vector2){330, 170}, 35, 7, BLACK);

    DrawRectangle(988, 178, 180, 35, (Color){255, 255, 255, 120});
    DrawTextEx(textureManager->myfont, "Iron Rock", (Vector2){990, 180}, 35, 7, BLACK);

    DrawRectangle(35, 60, 380, 28, (Color){255, 255, 255, 100});
    DrawTextEx(textureManager->myfont, "Press X to return to main menu!", (Vector2){40, 60}, 25, 5, BLACK);

    /*this following block of code serves two purposes:
    1. check if the mouse hovers over a castle i.e the cursor collides with the rectangle of the castle
        in this case a small icon of that castle shows up
    2. if the collision condition is true, then we check if the button is being press.
        if the button is pressed on a particular castle, we update the gamestate accordingly
    */

    if (CheckCollisionPointRec(mouse, (Rectangle){700, 800, 200, 200})) // check hover
    {                                                                   // draw the icon
        DrawTextureEx(textureManager->textures[12], (Vector2){650, 610}, 0, .7, WHITE);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) // check for button press
            *state = CASTLE1;                     // update gamestate
    }
    if (CheckCollisionPointRec(mouse, (Rectangle){350, 700, 250, 200}))
    {
        DrawTextureEx(textureManager->textures[13], (Vector2){150, 520}, 0, .7, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = CASTLE2;
    }
    if (CheckCollisionPointRec(mouse, (Rectangle){100, 450, 300, 200}))
    {
        DrawTextureEx(textureManager->textures[14], (Vector2){100, 320}, 0, .7, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = CASTLE3;
    }
    if (CheckCollisionPointRec(mouse, (Rectangle){300, 100, 300, 200}))
    {
        DrawTextureEx(textureManager->textures[15], (Vector2){430, 150}, 0, .7, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = CASTLE4;
    }
    if (CheckCollisionPointRec(mouse, (Rectangle){1100, 160, 200, 100}))
    {
        DrawTextureEx(textureManager->textures[16], (Vector2){900, 260}, 0, .7, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            *state = CASTLE5;
    }
    EndDrawing();
}

/*
this following code is the part that handles the display of info of indivisual castles once the player clicks on it
*/

float castleTrans = 0; // transparency controll variable
void castle1(GameState *state, TextureManager *textureManager)
{

    // transparency controll
    if (castleTrans < 255)
        castleTrans += 4;
    else if (castleTrans >= 255)
        castleTrans = 255;

    // the picture of the respective castle is loaded and displayed at center of screen

    BeginDrawing();

    DrawTextureEx(textureManager->textures[6], (Vector2){screenWidth / 2 - textureManager->textures[6].width / (2 * scale), screenHeight / 2 - textureManager->textures[6].height / (2 * scale)}, 0, 0.8, (Color){255, 255, 255, castleTrans});

    // font file is loaded into memory

    // details about the castle are added
    // todo : add more details
    DrawRectangle(638, 888, 460, 35, (Color){0, 0, 0, 120});
    DrawTextEx(textureManager->myfont, "Press Backspace to go back!", (Vector2){640, 890}, 35, 7, WHITE);

    DrawRectangle(278, 118, 295, 158, (Color){0, 0, 0, 120});
    DrawTextEx(textureManager->myfont, "Bug Bridge", (Vector2){280, 120}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Level 1", (Vector2){280, 170}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Troops : 100", (Vector2){280, 220}, 60, 5, WHITE);

    // this condition checks if the selected castle has been conquered by you or not
    // if yes, your character shows up on one side of screen
    if (Nations[0] == 1)
    {
        DrawRectangle(676, 118, 420, 58, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status : Conquered", (Vector2){680, 120}, 60, 5, WHITE);

        DrawTextureEx(textureManager->textures[11], (Vector2){162, screenHeight - textureManager->textures[11].height + 100}, 0, 0.8, (Color){255, 255, 255, castleTrans});
    }

    EndDrawing();

    // backspace is udes to exit the castle details and go back to playmenu
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        // transparency is reset
        castleTrans = 0;
        *state = PLAYMENU;
    }
}
void castle2(GameState *state, TextureManager *textureManager)
{
    if (castleTrans < 255)
        castleTrans += 4;
    else if (castleTrans >= 255)
        castleTrans = 255;

    BeginDrawing();

    DrawTextureEx(textureManager->textures[7], (Vector2){screenWidth / 2 - textureManager->textures[7].width / (2 * scale), screenHeight / 2 - textureManager->textures[7].height / (2 * scale)}, 0, 0.8, (Color){255, 255, 255, castleTrans});

    DrawRectangle(638, 900, 460, 35, (Color){0, 0, 0, 120});
    DrawTextEx(textureManager->myfont, "Press Backspace to go back!", (Vector2){640, 900}, 35, 7, WHITE);

    DrawRectangle(278, 118, 295, 158, (Color){0, 0, 0, 120});
    DrawTextEx(textureManager->myfont, "Mid Town", (Vector2){280, 120}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Level 2", (Vector2){280, 170}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Troops : 110", (Vector2){280, 220}, 60, 5, WHITE);
    if (Nations[1] == 1)
    {
        DrawRectangle(676, 118, 420, 58, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status : Conquered", (Vector2){680, 120}, 60, 5, WHITE);
        DrawTextureEx(textureManager->textures[11], (Vector2){162, screenHeight - textureManager->textures[11].height + 100}, 0, 0.8, (Color){255, 255, 255, castleTrans});
    }
    else
    {
        DrawRectangle(601, 118, 500, 100, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status: Not Conquered", (Vector2){600, 120}, 60, 5, WHITE);
        DrawTextEx(textureManager->myfont, "Press Enter to battle", (Vector2){700, 170}, 40, 5, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            // transparency is reset
            castleTrans = 0;

            *state = BATTLEMODE2;
        }
    }
    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        castleTrans = 0;
        *state = PLAYMENU;
    }
}
void castle3(GameState *state, TextureManager *textureManager)
{
    if (castleTrans < 255)
        castleTrans += 4;
    else if (castleTrans >= 255)
        castleTrans = 255;

    BeginDrawing();

    DrawTextureEx(textureManager->textures[8], (Vector2){screenWidth / 2 - textureManager->textures[8].width / (2 * scale), screenHeight / 2 - textureManager->textures[8].height / (2 * scale)}, 0, 0.8, (Color){255, 255, 255, castleTrans});

    DrawRectangle(636, 888, 460, 35, (Color){0, 0, 0, 120});

    DrawRectangle(278, 118, 295, 158, (Color){0, 0, 0, 120});
    DrawTextEx(textureManager->myfont, "Press Backspace to go back!", (Vector2){638, 898}, 30, 7, WHITE);
    DrawTextEx(textureManager->myfont, "Troops : 220", (Vector2){280, 220}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Boatbar ", (Vector2){280, 130}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Level 3", (Vector2){280, 180}, 60, 5, WHITE);
    if (Nations[2] == 1)
    {

        DrawRectangle(675, 120, 420, 58, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status : Conquered", (Vector2){680, 120}, 60, 5, WHITE);
        DrawTextureEx(textureManager->textures[11], (Vector2){162, screenHeight - textureManager->textures[11].height + 100}, 0, 0.8, (Color){255, 255, 255, castleTrans});
    }
    else
    {
        DrawRectangle(595, 118, 495, 100, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status: Not Conquered", (Vector2){600, 120}, 58, 5, WHITE);
        DrawTextEx(textureManager->myfont, "Press Enter to battle", (Vector2){700, 170}, 40, 5, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            // transparency is reset
            castleTrans = 0;
            if (Nations[1] == 1)
                *state = BATTLEMODE3;
            else
            {
                DrawRectangle(308, 10, 750, 55, (Color){0, 0, 0, 120});
                DrawTextEx(textureManager->myfont, "Beat the previous level first", (Vector2){310, 10}, 70, 7, WHITE);
            }
        }
    }
    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        castleTrans = 0;
        *state = PLAYMENU;
    }
}
void castle4(GameState *state, TextureManager *textureManager)
{
    if (castleTrans < 255)
        castleTrans += 4;
    else if (castleTrans >= 255)
        castleTrans = 255;

    BeginDrawing();

    DrawTextureEx(textureManager->textures[9], (Vector2){screenWidth / 2 - textureManager->textures[9].width / (2 * scale) - 50, screenHeight / 2 - textureManager->textures[9].height / (2 * scale) - 50}, 0, 0.9, (Color){255, 255, 255, castleTrans});

    DrawRectangle(636, 895, 460, 35, (Color){0, 0, 0, 120});
    DrawRectangle(278, 90, 295, 158, (Color){0, 0, 0, 120});

    DrawTextEx(textureManager->myfont, "Press Backspace to go back!", (Vector2){640, 900}, 35, 7, WHITE);
    DrawTextEx(textureManager->myfont, "Troops : 450", (Vector2){300, 190}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Gaurdon ", (Vector2){300, 100}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Level 4", (Vector2){300, 150}, 60, 5, WHITE);
    if (Nations[3] == 1)
    {

        DrawRectangle(680, 110, 420, 58, (Color){0, 0, 0, 120});

        DrawTextEx(textureManager->myfont, "Status : Conquered", (Vector2){680, 110}, 60, 5, WHITE);

        DrawTextureEx(textureManager->textures[11], (Vector2){162, screenHeight - textureManager->textures[11].height + 100}, 0, 0.8, (Color){255, 255, 255, castleTrans});
    }
    else
    {
        DrawRectangle(595, 118, 505, 100, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status: Not Conquered", (Vector2){600, 120}, 60, 5, WHITE);
        DrawTextEx(textureManager->myfont, "Press Enter to battle", (Vector2){700, 170}, 40, 5, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            // transparency is reset
            castleTrans = 0;
            if (Nations[2] == 1)
                *state = BATTLEMODE4;
            else
            {
                DrawRectangle(308, 10, 750, 55, (Color){0, 0, 0, 120});

                DrawTextEx(textureManager->myfont, "Beat the previous level first", (Vector2){310, 10}, 70, 7, WHITE);
            }
        }
    }
    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        castleTrans = 0;
        *state = PLAYMENU;
    }
}
void castle5(GameState *state, TextureManager *textureManager)
{
    if (castleTrans < 255)
        castleTrans += 4;
    else if (castleTrans >= 255)
        castleTrans = 255;

    BeginDrawing();
    DrawTextureEx(textureManager->textures[10], (Vector2){screenWidth / 2 - textureManager->textures[10].width / (2 * scale) - 10, screenHeight / 2 - textureManager->textures[10].height / (2 * scale) - 10}, 0, 0.85, (Color){255, 255, 255, castleTrans});

    DrawRectangle(636, 895, 460, 35, (Color){0, 0, 0, 120});
    DrawRectangle(278, 131, 295, 158, (Color){0, 0, 0, 120});

    DrawTextEx(textureManager->myfont, "Press Backspace to go back!", (Vector2){640, 900}, 35, 7, WHITE);
    DrawTextEx(textureManager->myfont, "Troops : 1000", (Vector2){280, 220}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Iron Rock ", (Vector2){280, 130}, 60, 5, WHITE);
    DrawTextEx(textureManager->myfont, "Level 5", (Vector2){280, 180}, 60, 5, WHITE);
    if (Nations[4] == 1)
    {
        DrawRectangle(656, 138, 420, 58, (Color){0, 0, 0, 120});
        DrawTextEx(textureManager->myfont, "Status : Conquered", (Vector2){656, 138}, 60, 5, WHITE);

        DrawTextureEx(textureManager->textures[11], (Vector2){162, screenHeight - textureManager->textures[11].height + 100}, 0, 0.8, (Color){255, 255, 255, castleTrans});
    }
    else
    {

        DrawRectangle(595, 118, 505, 100, (Color){0, 0, 0, 120});

        DrawTextEx(textureManager->myfont, "Status: Not Conquered", (Vector2){600, 120}, 60, 5, WHITE);
        DrawTextEx(textureManager->myfont, "Press Enter to battle", (Vector2){700, 170}, 40, 5, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            // transparency is reset
            castleTrans = 0;
            if (Nations[3] == 1)
                *state = BATTLEMODE5;
            else
            {
                DrawRectangle(308, 10, 750, 55, (Color){0, 0, 0, 120});

                DrawTextEx(textureManager->myfont, "Beat the previous level first", (Vector2){310, 10}, 70, 7, WHITE);
            }
        }
    }
    EndDrawing();
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        castleTrans = 0;
        *state = PLAYMENU;
    }
}

float bgtrans2 = 0; // controll variable for loading screen

int loadingscreen2(GameState *state, TextureManager *textureManager)
{

    // controll system for changing transparency of loading screen
    if (bgtrans < 70)
        bgtrans += 1.5f;
    else if (bgtrans >= 70)
        bgtrans = 70;

    if (loadbar < 500)
        loadbar += 5;
    else
    {
        bgtrans = 0;
        //move on to credits screen
        *state = CREDITS;
    }

    BeginDrawing();

    // draw background and loading bar using controll variables
    DrawTextureEx(textureManager->textures[4], (Vector2){0, 0}, 0, scale, (Color){bgtrans, bgtrans, bgtrans, bgtrans});
    DrawRectangle(screenWidth / 2 - 250, 875, 500, 30, (Color){255, 255, 255, bgtrans});
    DrawRectangle(screenWidth / 2 - 250, 875, loadbar, 30, (Color){0, 228, 48, 150});
    // todo : add tips
    EndDrawing();
}

void completeGame(GameState *state, TextureManager *textureManager)
{
    Vector2 mouse = GetMousePosition();

    if (bgtrans2 < 255)
        bgtrans2 += 1;
    else
        bgtrans2 = 255;
    if (IsKeyPressed(KEY_ENTER))
    {
        *state = LOADSCREEN2;
        return;
        
    }
    BeginDrawing();
    DrawTextureEx(textureManager->textures[10], (Vector2){0, 0}, 0, 1.4, (Color){255, 255, 255, bgtrans2});
    DrawTextureEx(textureManager->textures[11], (Vector2){0, 510}, 0, 1.0, (Color){255, 255, 255, bgtrans2});
    DrawTextEx(textureManager->myfont, "Press Enter to Continue", (Vector2){900, 900}, 35, 6, (Color){255, 255, 255, bgtrans2});

    DrawTextureEx(textureManager->textures[20], (Vector2){1700, -600}, 90, 2.5, (Color){255, 255, 255, bgtrans2/2});
    DrawTextEx(textureManager->myfont, "Victory", (Vector2){900, 200}, 85, 6, (Color){0, 0, 0, 255});

    EndDrawing();
}
void lostGame(GameState *state, TextureManager *textureManager)
{

    Vector2 mouse = GetMousePosition();

    if (bgtrans2 < 255)
        bgtrans2 += 1;
    else
        bgtrans2 = 255;
    //Button continueToCredits = createButton(524, 293, textureManager->textures[2].width, textureManager->textures[2].height);
    if (IsKeyPressed(KEY_ENTER))
    {
        *state = LOADSCREEN2;
        return;
        
        //loadingscreen2(state,textureManager);
    }
    BeginDrawing();
    DrawTextureEx(textureManager->textures[10], (Vector2){0, 0}, 0, 1.4, (Color){255, 255, 255, bgtrans2});
    DrawTextureEx(textureManager->textures[11], (Vector2){0, 510}, 0, 1.0, (Color){255, 255, 255, bgtrans2});
    DrawTextEx(textureManager->myfont, "Press Enter to Continue", (Vector2){900, 900}, 35, 6, (Color){255, 255, 255, bgtrans2});

    DrawTextureEx(textureManager->textures[20], (Vector2){1700, -600}, 90, 2.5, (Color){255, 255, 255, bgtrans2});
    DrawTextEx(textureManager->myfont, "Defeat", (Vector2){900, 200}, 85, 6, (Color){0, 0, 0, 255});

    EndDrawing();
}


int bgtrans3 =0;
float scroll1 = 0;
void credits(GameState* state,TextureManager* textureManager){
    *state = CREDITS;
    
    if (bgtrans3 < 255)
        bgtrans3 += 1;
    else
        bgtrans3 = 255;
    if (scroll1 > -1500)
        scroll1--;
    else 
        {scroll1 = -1500;
        CloseWindow();}
    BeginDrawing();
    
    DrawTextureEx(textureManager->textures[21],(Vector2){0,scroll1},0,1.01,(Color){ 255, 255, 255, bgtrans3 });
    EndDrawing();
    

}