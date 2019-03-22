
#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED
#define SIZE_NAME 20
#include "gamestate.h"
#include <time.h>
#define PLAYERS 2       /* MAX number of players int the game*/

struct player {
    int id;
    char name[SIZE_NAME];
    char symbol;
    bool human;
    int score;
    int moves;
    struct player *next_player;
    struct player *prev_player;
};

/* fonctions de creation / initialisation des joueurs Humain et AI */

struct player *createPlayerList (void);
void configPlayerTypes(int nb_human,int nb_AI, int nb_restorePlayer );
void configureHumanPlayer (int nb_players);
void configureAIplayer (int nb_AIplayers);
void addPlayer (int playerId, char playerName[SIZE_NAME],char playerSymbol,bool humanP,int countMoves, int score);
void restorePlayersFromSave (int nb_restorePlayer);

/* fonctions de consultation du player courant par le module Game */

struct player *getPlayer (struct player *player_list,int player_number);
bool isPlayerHuman (int number);
void displayScore();

/* fonctions d'actions sur le gamestate: controle saisie (H) ou calcul du coup (AI) */

void humanPlaysMove (gamestate oxo);
void humanPlayerInput (gamestate oxo,int *x, int *y );
void AIPlaysMove (gamestate oxo);
int threatFound(gamestate oxo, int *row, int *col, char symbolTested );
int makePoints (gamestate oxo,int *row, int *col, char symbolTested );

/* election du joueur gagnant */

int returnWinner ();
void printWinnerDetails(int player_id);
void deleteList();
#endif
