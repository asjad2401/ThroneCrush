// declarations.h
//here is where i defined all of structures and global variables
//the declarations are on .c file
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "raylib.h"
#include "rlgl.h"



//define an enumerator gamestate to keep track of what state the game is in
//also useful for switching between states by switch statement
typedef enum gamestate{
    BATTLEMODE1,
    BATTLEMODE2,
    BATTLEMODE3,
    BATTLEMODE4,
    BATTLEMODE5,
    MAINMENU,
    PLAYMENU,
    QUITS,
    OPTIONSMENU,
    GAMEOVER,
    GAMEWON,
    FIRSTLOADINGSCREEN,
    LOADSCREEN,
    LOADSCREEN2,
    CASTLE1,
    CASTLE2,
    CASTLE3,
    CASTLE4,
    CASTLE5,
    COMPLETE,
    LOST,
    CREDITS
}GameState;

typedef struct {
    Texture2D textures[23];
    Font myfont ;
} TextureManager;

typedef struct {
    int level;
    int troops;
    char name[20];
    
} PlayerData;

typedef struct {

} Nation;


//buttons will be used to toggle between states
//define a structure of button which contains its position and dimensions
//it also contains the postion of text if any is to be included
typedef struct{
    int posX;
    int posY;
    int ButtonWidth;
    int ButtonHeight;
    float textXpos;
    float textYpos;

}Button;


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


//define some constant global variables
extern const float  scale;
extern float screenWidth;
extern float screenHeight;
extern int Nations[5];



#endif // DECLARATIONS_H