// states.h
//this file contains declarations of all the possible gamestates and associated game screens
#ifndef STATES_H
#define STATES_H

#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "rlgl.h"
#include "battle.h"


void mainmenu(GameState*,TextureManager*);
void playmenu(GameState*,TextureManager*);
int loadingscreen(GameState*,TextureManager*);
int loadingscreen2(GameState *, TextureManager *);
int firstloadingscreen(GameState*,TextureManager*);

void castle1(GameState*,TextureManager*);
void castle2(GameState*,TextureManager*);
void castle3(GameState*,TextureManager*);
void castle4(GameState*,TextureManager*);
void castle5(GameState*,TextureManager*);
void quitmenu(GameState*,TextureManager*);
void optionsmenu(GameState*,TextureManager*);

void completeGame(GameState*,TextureManager*);
void lostGame(GameState*,TextureManager*);

void credits(GameState*, TextureManager*);

#endif // STATES_H