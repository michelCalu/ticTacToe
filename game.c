#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "gamestate.h"
#include "players.h"
#include "helpers.h"

#define SCORE_TO_WIN 5
time_t TIME_LIMIT=3600;

void welcomeMessage (int rule){

	switch (rule){
    	case 1:
    printf("\n\
 ********************************************\n\
\tRULE OF THE GAME (Quick Mode):\n\
\tTime limit = 5 minutes\n\
\tVictory = 5 wins\n\
 ********************************************\n\n");
        break;

	   	case 2:
    printf("\n\
 ********************************************\n\
\tRULE OF THE GAME (Normal Mode):\n\
\tNo Time limit\n\
\t1 pt / 3-in-a row, untill board full.\n\
 ********************************************\n\n");
	break;
	}
}

time_t playtime (time_t start, gamestate oxo){
    time_t current = time(NULL);
    time_t elapsed=current-start;
    oxo->gameTime += elapsed;

    printf("\n\tElapsed time: %ld Min:%ld Sec\n\n",oxo->gameTime/60,oxo->gameTime%60);
    return oxo->gameTime;
}

void setGameRules (gamestate oxo){

    int gamestop=0;
    do{
	printf("Select a game mode:\n\n\
            1: Quick Mode\n\
            2: Full Mode\n\
             : ");
		   	scanf("%d",&gamestop);
	}while((gamestop>2 || gamestop<1));

	if(gamestop==1){
        oxo->score_to_win=5;
        TIME_LIMIT=300;
    }
    clearConsole();
    welcomeMessage(gamestop);
}


void playGame (int mode_jeu,gamestate oxo){
        int winner;
        time_t start,duration;

        if(mode_jeu!=4){

            setGameRules(oxo);
        }

        displayBoard(oxo);
        start=time(NULL);

        do{

                displayScore();

                switch( isPlayerHuman (oxo->active_player)){

                    case true:

                        humanPlaysMove(oxo);

                        break;

                    case false:

                        AIPlaysMove(oxo);

                        break;
                }

                displayBoard(oxo);

                updateGamestate(oxo);

                playerSwitch(oxo);

                duration = playtime(start,oxo);

                start=time(NULL);

        } while( !GameOver(oxo) && duration < TIME_LIMIT );

        winner=returnWinner();
        clearConsole();
        printWinnerDetails(winner);
        displayBoard(oxo);
        playtime(start,oxo);

        printf("\n\n\n");
        }
