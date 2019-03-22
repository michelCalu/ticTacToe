#ifndef gamestate_H_
#define gamestate_H_
#include <stdbool.h>
#include <time.h>
#define SIZE 10
#define LINES 4
#define VIDE ' '

typedef char board[SIZE][SIZE];

struct Game {
    board gameboard;
    int moves_played;
    int active_player;
    int score_to_win;
    bool gameover;
    int winnerId;
    time_t gameTime;
    };
typedef struct Game *gamestate;

/*EDIT FUNCTIONS: modifient l'�tat de jeu � chaque action d'un joueur*/

gamestate createGamestate(int gametype);
gamestate initialiseGamestate(gamestate oxo);
gamestate setSymbol(gamestate oxo, int ligne, int colonne, char symbole_joueur);
void updateGamestate(gamestate oxo);
void playerSwitch(gamestate oxo);
gamestate restoreGamestate(gamestate oxo);


/*QUERY FUNCTIONS: � chaque tour --> envoie l'�tat du jeu au module "Game" */

void displayBoard(gamestate oxo);
bool boardFull (gamestate oxo);
bool GameOver(gamestate oxo);

/*QUERY FUNCTIONS: renvoie des informations de contr�le au module "Players" */

bool validMove (gamestate oxo, int ligne, int colonne);
bool isInsideBounds (int to_position, int from_position);
int Search3_in_a_Row (gamestate oxo, int ligne, int colonne, char symbole_joueur);
void isPlayerWinner(gamestate oxo, int current_pl_score);

gamestate deleteGamestate(gamestate oxo);
#endif
