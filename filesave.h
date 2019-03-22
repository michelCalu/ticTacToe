#ifndef FILESAVE_H_INCLUDED
#define FILESAVE_H_INCLUDED
#include <stdio.h>
#include "gamestate.h"

/* fonctions de sauvegarde / restore */

void createFile ();

void WritePlayerToFile();
void WriteGamestateToFile(struct Game *gamestateToSave);

struct player *ReadPlayerFromFile(struct player *savedPlayer,int playerNb);
gamestate readGamestateFromFile(gamestate oxo);


#endif
