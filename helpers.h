#ifndef HELPERFUNCTIONS_H_INCLUDED
#define HELPERFUNCTIONS_H_INCLUDED
#include "gamestate.h"

/* Ensemble de fonction g�n�riques toujours int�gr�es � l'int�rieur d'autres fonctions*/
/* non li�es � un module*/

int readStringFromUser(char *input, int length);
int flush_stdin();
bool validCoordinates (int ligne, int colonne);
void clearConsole();
void randomAtoB(int *x, int *y, int A, int B);
void randomAdjacentCell(int *x, int *y);
void waitSeconds(float seconds);
char *drawBoard ();
char getOpponentSymbol (char mySymbol);

#endif
