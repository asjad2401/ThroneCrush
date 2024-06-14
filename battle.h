#ifndef BATTLE
#define BATTLE

#include "raylib.h"
#include "declarations.h"
#include "buttons.h"
#include "rlgl.h"
#include "states.h"

void spawnPlayerTroop(TextureManager* , float , float );
void spawnEnemyTroop(TextureManager *);
int battle(GameState*, TextureManager*, int , int, float,float);
void lost(GameState*,TextureManager* );
void won(GameState*,TextureManager* );
void draw(GameState*,TextureManager* );
void resetVariables();

#endif