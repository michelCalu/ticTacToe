#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "gamestate.h"
#include "players.h"
#include "helpers.h"
#include "filesave.h"

#define SIZE_NAME 20    /* MAX length of player name */


char takenbyP1=0;       /* symbol chosen by P1. global to be sure AI can't take the same as the human */

struct player *player_list;
struct player *current_player;

struct player *createPlayerList (void){
 	player_list = malloc(sizeof(struct player));
    if (player_list == NULL){
        printf("erreur creation liste");
        return NULL;
    }
    else {
    	player_list->id = 0;
    	strcpy(player_list->name, "sentinelle");
        player_list->next_player = player_list;
        player_list->prev_player = player_list;
        return player_list;
    }
}

void addPlayer (int playerId, char playerName[SIZE_NAME],char playerSymbol,bool humanP,int countMoves, int score){

	struct player* nplayer = malloc(sizeof(struct player));
    if(nplayer!=NULL){
        nplayer->id=playerId;
        strcpy(nplayer->name, playerName);
        nplayer->symbol=playerSymbol;
        nplayer->score=score;
        nplayer->moves=countMoves;
        nplayer->human=humanP;



        nplayer->prev_player=player_list->prev_player;
        nplayer->next_player=player_list;
        player_list->prev_player->next_player=nplayer;
        player_list->prev_player=nplayer;
    }

}

void deleteList(){

   struct player *playerPtr = player_list->next_player;
   struct player *playerToDelete = NULL;

   while (playerPtr!=player_list){
        playerToDelete=playerPtr;
        playerPtr = playerPtr->next_player;
        free(playerToDelete);

    }
    free(player_list);
}

struct player *getPlayer (struct player *player_list,int player_number) {

	current_player = player_list->next_player;
	while(current_player!=player_list){
		if(current_player->id==player_number){
		return current_player;
		}
		current_player = current_player->next_player;
	}
	return NULL;
}

bool isPlayerHuman (int number){
    current_player = player_list->next_player;
        while(current_player!=player_list){
            if(current_player->id==number){
                return current_player->human;
            }
		current_player = current_player->next_player;
        }
        return false;
}

void configPlayerTypes(int nb_human,int nb_AI, int nb_restorePlayer ){

	player_list=createPlayerList();

    if(nb_human>0)
    configureHumanPlayer(nb_human);

    if(nb_AI>0)
    configureAIplayer(nb_AI);

    if (nb_restorePlayer>0)
    restorePlayersFromSave(nb_restorePlayer);

}

void configureHumanPlayer (int nb_players){
	char name[SIZE_NAME]={0};
	char symbol=' ';
	bool humanP=true;
    int i=1;

    while (i<=nb_players) {

        printf("\nEnter player %d's name:",i);

        int name_input=readStringFromUser(name,SIZE_NAME);

        if(name_input){

            do{
                printf("Enter player %d's symbol (O/X): ",i);
                scanf(" %c", &symbol);

                if (symbol==takenbyP1){
                    printf("Player 1 took the %c's already!\n",takenbyP1);
                }

            }while( ((symbol!='O') && (symbol!='X')) || (symbol==takenbyP1));

            takenbyP1=symbol;
            addPlayer(i,name,symbol,humanP,0,0);
            i++;
            flush_stdin();
        }
	}
}

void configureAIplayer (int nb_AIplayers){
	char name[SIZE_NAME]="Computer";
	char symbol;
	bool humanP=false;

    int i=2;
    while (i>2-nb_AIplayers) {        /* inverser le sens de la boucle permet de créer les configs H+AI et AI+AI */
                                        /* dans 2 contextes différents */
        if(takenbyP1=='X'||takenbyP1==0){
            symbol='O';

        }else if (takenbyP1=='O'){
            symbol='X';
        }

        addPlayer(i,name,symbol,humanP,0,0);

        takenbyP1=symbol; /*AI will be player 2 by default*/
        i--;
    }
}

void restorePlayersFromSave (int nb_restorePlayer){

    int i=1;

    while(i<=nb_restorePlayer){
        struct player *savedPlayer = malloc(sizeof(struct player));
            if(savedPlayer!=NULL){

                savedPlayer = ReadPlayerFromFile(savedPlayer, i);

                addPlayer (savedPlayer->id, savedPlayer->name, savedPlayer->symbol,
                           savedPlayer->human,savedPlayer->moves,savedPlayer->score);

            }else{
                printf("error creating player in restore process");
            }
        i++;
        free(savedPlayer);
    }
}

void displayScore(){
    int i=1;
    struct player *player;

    while(i<=PLAYERS){
        player=getPlayer(player_list,i);

        printf("  _________________________________________\n");
        printf("  Player %d:%-20s\t",player->id,player->name);
        printf("  Score: %d\n",player->score);

        i++;
    }
        printf("  _________________________________________\n\n");
}

void printWinnerDetails(int player_id){
    struct player *winner;

    printf("\n\n  Gameover! Final score:\n\n");
    displayScore();

    if(player_id==0){
        printf("\nIt's a draw: play a new game!\n\n");
    }
    else{
        winner=getPlayer(player_list,player_id);
        printf("\n\n  Player %d (%s) wins the game! \n\n",winner->id,winner->name);
    }
}

int returnWinner(){
    int best_score=0;
    int winner=0;
    struct player *current_player;

	current_player = player_list->next_player;
	while(current_player!=player_list){
		if(current_player->score > best_score){
            best_score=current_player->score;
            winner=current_player->id;
		}
		else if (current_player->score == best_score){
            winner=0;
		}
        current_player = current_player->next_player;
	}
	return winner;
}

void humanPlaysMove (gamestate oxo){
    int wins;
    int x,y;

    current_player=getPlayer(player_list,oxo->active_player);

    humanPlayerInput ( oxo, &x, &y);
    setSymbol (oxo, x, y, current_player->symbol);

    current_player->moves++;

    wins=Search3_in_a_Row(oxo, x, y, current_player->symbol);
    current_player->score += wins;
    printf("\n    %d wins with this move. Next player:\n\n",wins);

    WritePlayerToFile (current_player,oxo->active_player);
    isPlayerWinner (oxo,current_player->score);
}

void humanPlayerInput (gamestate oxo,int *x, int *y ){  /* this function reads the x/y position input by a human player */
                                                        /* forces to input a A->J char and protects integer input */
    char col,c;                                         /* against wrong scanf (e.g typing a char instead)*/
    int row=-1;                                         /* returns 1 char + 1 integer for being put on the grid */
    bool valid_play=false;

    while(valid_play==false){
            printf("\t\t  Turn:%d\n",current_player->moves+1);

            do{
                printf("\n    %s, enter column (exit with 'q'):",current_player->name);

                scanf(" %c", &col);

                if((int)col==81 || (int)col==113){				/* make a "clean" exit procedure to suspend game so I can free memory */

                        clearConsole();
                        printf("Suspending Game...");
                        deleteList ();
                        waitSeconds(1);
                        exit(0);
                    }

            }while(((int)col)<65 || ((int)col)> 74);

            do{
                printf("Please enter row:");
            }while (((scanf("%d%c", &row, &c)!=2 || c!='\n') && flush_stdin()) || row<1 || row>10);

            *x=row-1;                        /*-1 = match avec indices tableau */
            *y=((int)col)-65;                /* ASCII A-65 = 0 */


            if(validMove(oxo,*x,*y)){
                valid_play=true;
            }else{
                printf("\n\nInvalid move (cell is full). Try again!\n\n");
            }
    }
    clearConsole();
}

void AIPlaysMove (gamestate oxo){
    bool valid = false;
    bool blockOpponent = false;
    bool scorePoint = false;
    int wins;
    int x,y;

    current_player = getPlayer( player_list, oxo->active_player );

    printf("\nComputer playing...\n");

    waitSeconds(1);

    do{
            if (current_player->moves == 0) {

                randomAtoB(&x,&y,0,SIZE);
                    if(validMove(oxo,x,y)){
                        valid=true;
                    }
            }

            else if ( threatFound (oxo, &x, &y,getOpponentSymbol(current_player->symbol)) > 0) {

                blockOpponent = true;

            }

            else if ( makePoints (oxo, &x, &y, current_player->symbol) >= 0)  {

                scorePoint = true;

            }
            else {
                randomAtoB(&x,&y,0,SIZE);
                    if(validMove(oxo,x,y)){
                        valid=true;
                    }
				}
    }  while (valid==false && blockOpponent==false && scorePoint==false);

    clearConsole();

    current_player->moves++;

	setSymbol(oxo, x, y, current_player->symbol);
    wins=Search3_in_a_Row (oxo, x, y, current_player->symbol);
    current_player->score += wins;
    printf("\n    %d wins with this move. Next player:\n\n",wins);

	WritePlayerToFile(current_player,oxo->active_player);

    isPlayerWinner(oxo, current_player->score);
}

int threatFound (gamestate oxo,int *row, int *col, char symbolTested ){
    int i,j;
    int bestMove=0;
    int threats=0;
    for (i=0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){

            if ( validMove(oxo,i,j) )  {

                threats = Search3_in_a_Row(oxo,i,j,symbolTested);

                    if (threats > bestMove ){
                        bestMove = threats;
                        *row = i;
                        *col = j;
                        }

            }
        }
    }
    return bestMove;							/* this procedure returns the best score the opponent could play at next turn */
}

int makePoints (gamestate oxo,int *row, int *col, char symbolTested ){

    int i,j;
    int bestMove=0;
    int pointsPossible=0;
    for (i=0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){

                if ( validMove(oxo,i,j) ){
                    *row = i;
                    *col = j;
                    pointsPossible = Search3_in_a_Row(oxo,i,j,symbolTested);
                        if (pointsPossible >= bestMove ){
                            bestMove = pointsPossible;
                            *row = i;
                            *col = j;

                    }
                }

                else {
                        if (oxo->gameboard[i][j] == symbolTested) {
                            int randX=0;
                            int randY=0;
                            do{
                                randomAdjacentCell(&randX,&randY);

                            } while (! validMove(oxo,i+randX,j+randY) || (randX == 0 && randY ==0));
                                *row = i + randX;
                                *col = j + randY;

                        }
                }
        }
    }

    return bestMove;

}


