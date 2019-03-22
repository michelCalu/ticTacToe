#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include "players.h"
#include "game.h"
#include "filesave.h"
#include "helpers.h"
#define FILENAME "gamesave.bin"

char filename[]= FILENAME;

int gameSelect (){

    int game,humans,AI,restorePlayer;
    char c;

	do{
        printf("Which type of game do you want to play?\n\n\
                1: Human Vs Human\n\
                2: Human Vs Computer\n\
                3: AI Vs AI\n\
                4: Restore suspended game\n\
                 : ");
    }while (((scanf("%d%c", &game, &c)!=2 || c!='\n') && flush_stdin()) || game < 1 || game > 4);


    switch(game){
			case 1:
			    humans=PLAYERS;
			    AI=0;
			    restorePlayer=0;
			    createFile(filename);
			    configPlayerTypes(humans,AI,restorePlayer);
				break;
            case 2:
				humans=1;
			    AI=1;
			    restorePlayer=0;
			    createFile(filename);
			    configPlayerTypes(humans,AI,restorePlayer);
				break;
            case 3:
				humans=0;
			    AI=2;
			    restorePlayer=0;
			    createFile(filename);
			    configPlayerTypes(humans,AI,restorePlayer);
				break;
            case 4:
                humans=0;
			    AI=0;
			    restorePlayer=2;
			    configPlayerTypes(humans,AI,restorePlayer);
				break;

			default:
				configPlayerTypes(1,1,0);
				break;
		}
	return game;
}

int main(void){
    gamestate oxo;
    int game_type;

    game_type=gameSelect();

    oxo = createGamestate(game_type);

    if(oxo!=NULL){

        playGame (game_type,oxo);

    }else{

        printf("Failed to allocate memory for the gamestate");
    }

    deleteGamestate(oxo);

    deleteList();

    return EXIT_SUCCESS;
}
