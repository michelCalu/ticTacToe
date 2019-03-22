
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "gamestate.h"
#include "players.h"
#include <time.h>


time_t playtime (time_t start, gamestate oxo);
void setGameRules (gamestate oxo);
void playGame (int mode_jeu,gamestate oxo);


#endif
