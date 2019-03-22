#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "helpers.h"
#include "filesave.h"


typedef struct cell_position{
    int x;
    int y;
    }coordinate;

/* directions renvoie les 4 axes à vérifier + leur inverse
(1 vecteur par direction qui couvre "case jouée + 2 suivantes")*/
coordinate directions[LINES][LINES]={
								{{-1,0},{-2,0},{1,0}  ,{2,0}},
								{{-1,1},{-2,2},{1,-1} ,{2,-2}},
								{{0,1} ,{0,2} ,{0,-1} ,{0,-2}},
								{{1,1} ,{2,2} ,{-1,-1},{-2,-2}},
									};



gamestate createGamestate(int gametype){

    gamestate new_gamestate=malloc(sizeof(struct Game));

    if(new_gamestate==NULL){
        printf("Memory allocation error on new gamestate");
        return NULL;
    }else{
        if(gametype !=4){

            new_gamestate = initialiseGamestate (new_gamestate);

        }else{

            new_gamestate = restoreGamestate (new_gamestate);
        }
   }

    return new_gamestate;
}

gamestate initialiseGamestate(gamestate oxo){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            oxo->gameboard[i][j]=VIDE;
        }
    }
    oxo->moves_played = 0;
    oxo->active_player = 1;
    oxo->score_to_win = 109;    /*108 is the theoretic max score possible on a 2 player game */
    oxo->gameover = false;
    oxo->winnerId = 0;
    oxo->gameTime=0;

    return oxo;
}

gamestate restoreGamestate(gamestate oxo){

    oxo = readGamestateFromFile(oxo);

    return oxo;
}


void updateGamestate(gamestate oxo){

   oxo->moves_played++;

   WriteGamestateToFile(oxo);
}

gamestate deleteGamestate(gamestate oxo){

    if(oxo!=NULL){

        free(oxo);
    }
    return NULL;
}

void playerSwitch(gamestate oxo){

    if(oxo->active_player==1){

        oxo->active_player=2;
    }
    else{
        oxo->active_player=1;
    }
}

gamestate setSymbol(gamestate oxo, int ligne, int colonne, char symbole_joueur){

   if(validMove(oxo,ligne,colonne)){

        oxo->gameboard[ligne][colonne]=symbole_joueur;
    }
    return oxo;
}

bool GameOver(gamestate oxo){

    bool isGameover = false;

    if(oxo->winnerId != 0){

        isGameover = true;

    }else if (boardFull(oxo) == true){

        isGameover = true;
    }

    return isGameover;
}

bool boardFull (gamestate oxo){

    return oxo->moves_played >= SIZE*SIZE;
}

bool validMove (gamestate oxo, int ligne, int colonne){

    if(validCoordinates(ligne,colonne) && oxo->gameboard[ligne][colonne]==VIDE){

        return true;
    }

    return false;
}

void isPlayerWinner(gamestate oxo, int current_pl_score){

    if(current_pl_score >= oxo->score_to_win){

        oxo->winnerId=oxo->active_player;
    }

}

void displayBoard(gamestate oxo){

    char *boardStructure;
    int structureSize=0;
    int i=0;

    boardStructure = drawBoard(&structureSize);

    char *readPtr = *oxo->gameboard;

    while (i<=structureSize-1){
   		if(boardStructure[i]!='*'){
   			putchar(boardStructure[i]);
        }
   		else{
            printf("%c",*readPtr);
            readPtr++;
   		}
   		i++;
    }
    free(boardStructure);
    printf("\n");
}

bool isInsideBounds (int to_position, int from_position){
	bool inside=false;

	if ((from_position + to_position)>=0 && (from_position + to_position)<10){
		inside=true;
	}
	return inside;
}

/*algorithme de recherche de 3-en-ligne:
(voir rapport)
*/
int Search3_in_a_Row (gamestate oxo, int ligne, int colonne, char symbol){
    int i,j;
    int moveX,moveY;
    int points=0;
    int count=0;

    for (i=0;i<LINES;i++){
        count=0;

        for (j=0;j<LINES;j++){

                moveX=directions[i][j].x;
                moveY=directions[i][j].y;

                if( isInsideBounds(moveX,ligne) && isInsideBounds(moveY,colonne) ){

                    if( symbol==oxo->gameboard[ligne+moveX][colonne+moveY]){

                        count++;

                    } else {
                        if (j==0 || j==2){
                            j++;
                        }
                    }

                }
        }
        if(count>=2){
            points=points+count-1;
        }
    }

    return points;
}

