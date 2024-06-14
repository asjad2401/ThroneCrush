// main.c
#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "states.h"

// main contains the basic gameloop and the gamestate switch
int main()
{

    // initialize both the window and speaker
    InitWindow(screenWidth, screenHeight, "ThroneCrush");
    InitAudioDevice();

    Music backgroundSong = LoadMusicStream("assets/song.mp3");
    PlayMusicStream(backgroundSong);

    

    // image for loading screen background
    Image background = LoadImage("assets/background.png");
    Image Loadingscreen = LoadImage("assets/Loadingscreen.png");

    /* this array is a texture manager. it contains all the loaded textures in memeory. this array is passed
    throughout the code to all functions.*/

    TextureManager mymanager;
    {
        mymanager.textures[1] = LoadTextureFromImage(background);
        mymanager.textures[2] = LoadTexture("assets/button.png");
        mymanager.textures[3] = LoadTexture("assets/background.png");
        mymanager.textures[4] = LoadTextureFromImage(Loadingscreen);
        mymanager.textures[5] = LoadTexture("assets/Playmenubackground.png");
        mymanager.textures[6] = LoadTexture("assets/CastleB1.png");
        mymanager.textures[7] = LoadTexture("assets/CastleB2.png");
        mymanager.textures[8] = LoadTexture("assets/CastleB3.png");
        mymanager.textures[9] = LoadTexture("assets/CastleB4.png");
        mymanager.textures[10] = LoadTexture("assets/CastleB5.png");
        mymanager.textures[11] = LoadTexture("assets/Character.png");

        mymanager.myfont = LoadFont("assets/BLKCHCRY.TTF");

        mymanager.textures[12] = LoadTexture("assets/Castle1.png");
        mymanager.textures[13] = LoadTexture("assets/Castle2.png");
        mymanager.textures[14] = LoadTexture("assets/Castle3.png");
        mymanager.textures[15] = LoadTexture("assets/Castle4.png");
        mymanager.textures[16] = LoadTexture("assets/Castle5.png");
        mymanager.textures[17] = LoadTexture("assets/Battle.png");
        mymanager.textures[18] = LoadTexture("assets/Enemy.png"); 
        mymanager.textures[19] = LoadTexture("assets/imageback.png");
        mymanager.textures[20] = LoadTexture("assets/sword1.png");
        mymanager.textures[21] = LoadTexture("assets/Credits.png");
        mymanager.textures[22] = LoadTexture("assets/Troop.png"); 

    }

    // set the game state to main menu initially
    GameState gamestate = FIRSTLOADINGSCREEN;

    // set the refresh rate
    SetTargetFPS(60);

    // start the game loop
    while (!(WindowShouldClose()))
    {


        //replay the music if stops
        if (!IsMusicStreamPlaying(backgroundSong)) {
            
            PlayMusicStream(backgroundSong);  // Resume playback
        }
        UpdateMusicStream(backgroundSong);

        if (gamestate != CREDITS && gamestate != LOADSCREEN2)
        {
            if (Nations[0] && Nations[1] && Nations[2] && Nations[3] && Nations[4])
                gamestate = COMPLETE;
            if (!Nations[0] && !Nations[1] && !Nations[2] && !Nations[3] && !Nations[4])
                gamestate = LOST;
        }
        // this switch toggles between various gamestates and screens
        switch (gamestate)
        {

        case FIRSTLOADINGSCREEN:
            firstloadingscreen(&gamestate, &mymanager);
            break;

        case MAINMENU:
            // call the main menu function from file states.c
            // we need to pass gamestate as a pointer in order to update it when ever required to exit that state
            mainmenu(&gamestate, &mymanager);
            break;

        case QUITS:
            // call quit menu from states.c
            quitmenu(&gamestate, &mymanager);
            break;

        case OPTIONSMENU:
            // call options menu from states.c
            optionsmenu(&gamestate, &mymanager);
            break;
        case LOADSCREEN:
            // call loading screen from state.c
            loadingscreen(&gamestate, &mymanager);
            break;

        case LOADSCREEN2:
            loadingscreen2(&gamestate, &mymanager);
            break;

        case PLAYMENU:
            // call play menu from states.c
            playmenu(&gamestate, &mymanager);
            break;

        case CASTLE1:
            // call castle1 from states.c this shows details of a castle
            castle1(&gamestate, &mymanager);
            break;

        case CASTLE2:
            castle2(&gamestate, &mymanager);
            break;

        case CASTLE3:
            castle3(&gamestate, &mymanager);
            break;

        case CASTLE4:
            castle4(&gamestate, &mymanager);
            break;

        case CASTLE5:
            castle5(&gamestate, &mymanager);
            break;

        // the battle mode decides how much troops are there and what speed
        //battle function is same for all castles, handled differently
        case BATTLEMODE2:
            battle(&gamestate, &mymanager, 35, 30, 0.4, 90);
            break;

        case BATTLEMODE3:
            battle(&gamestate, &mymanager, 45, 50, 0.6, 90);
            break;

        case BATTLEMODE4:
            battle(&gamestate, &mymanager, 60, 70, 0.7, 90);
            break;

        case BATTLEMODE5:
            battle(&gamestate, &mymanager, 70, 80, 0.9, 90);
            break;

        //if you loose all 5 castles
        case LOST:
            lostGame(&gamestate, &mymanager);
            break;
        //if you win all 5
        case COMPLETE:
            completeGame(&gamestate, &mymanager);
            break;
        //credits screen
        case CREDITS:
            credits(&gamestate, &mymanager);
            break;
        }
    }
    
    //unloading data from memmory
    for (int i = 0; i <= 17; i++)
    {
        UnloadTexture(mymanager.textures[i]);
    }
    UnloadMusicStream(backgroundSong);

    CloseWindow();
    return 0;
}

