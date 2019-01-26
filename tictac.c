#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define COMP 2
#define PLAYER -2

void printGame(int ticarray[9]);

//void editGame(char ticarray[9], int location, char type);

int minimax(int ticarray[9], int type);//, int depth);

void compTurn(int ticarray[9]);

void playerTurn(int ticarray[9]);

int winCon(int ticarray[9]);

int main(void){
	int tic[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int place = 0;
	int win = 0;

	printf("computer will be 'O' and player will be 'X'\n");
	printf("will the player go (1)st or (2)nd? ");
	scanf("%d", &place);

	switch(place){
		case 1:
			printf("player will go first\n");
			break;
		case 2:
			printf("player will go second\n");
			break;
		default:
			printf("invalid choice\n");
			return EXIT_SUCCESS;
	}

	printGame(tic);

	printf("please select a cube by typing an integer from 1 - 9: ");

	if(place == 1){
		printf("player will go first\n");
	} else{
		printf("computer will go first\n");
	}

	while(win == 0){
		printf("current game state: \n");
		if(place == 1){
			printGame(tic);
			playerTurn(tic);
			//compTurn2(tic);
			printGame(tic);
			win = winCon(tic);
			compTurn(tic);
		} else{
			compTurn(tic);
			printGame(tic);
			playerTurn(tic);
		}
		win = winCon(tic);
	}

	printGame(tic);

	switch(win){
		case PLAYER:
			printf("Player wins! Wow! I thought it was impossible!\n");
			break;
		case COMP:
			printf("Computer wins! As expected :)\n");
			break;
		default:
			printf("ResidentSleeper draw\n");	
	}

	return 0;
}

void printGame(int ticarray[9]){
	int i;
	for(i = 0; i < 9; i++){
		if(ticarray[i] == 0){
			printf("□ ");
		} else if(ticarray[i] == PLAYER){
			printf("X ");
		} else{
			printf("O ");
		}
		if((i - 2)%3 == 0){
			printf("\n");
		}
	}
}

int minimax(int ticarray[9], int type){

	int win = winCon(ticarray);
	if(win != 0) {
		return win*type;
	}
	int location = -1;
	int bestValue = -69;
	for(int count = 0; count < 9; count++) {
		//do simulations
		if(ticarray[count] == 0) {
			ticarray[count] = type;
			int minmax = -minimax(ticarray, type*-1);
			if(minmax > bestValue) {
				location = count;
				bestValue = minmax;
			}
			ticarray[count] = 0;
		}
	}
	if(location == -1) return 0;
	return bestValue;
}


void compTurn(int ticarray[9]){
	int i;
	int location;
	int bestValue = -69;

	for(i = 0; i < 9; i++){
		if(ticarray[i] == 0){
			int tempValue;
			ticarray[i] = COMP;
			tempValue = -minimax(ticarray, PLAYER);
			if(tempValue > bestValue){
				bestValue = tempValue;
				location = i;
			}
			ticarray[i] = 0;
		}	
	}
	ticarray[location] = COMP;
}

void playerTurn(int ticarray[9]){
	printf("hello peng you where you like to place your X? ");
	while(1 > 0){
		int location;
		scanf("%d", &location);
		if((location >= 1 || location <= 9) && ticarray[location - 1] == 0){
			//editGame(&ticarray[9], location, 'X');
			ticarray[location - 1] = PLAYER;
			break;
		} else{
			int i; 
			int counter = 0;
			for(i = 0; i < 9; i++){
				if(ticarray[i] == 0){
					counter++;
				}
			}
			if(counter == 0){
				break;
			}
			printf("please enter a valid number\n");
		}
	}
}


int winCon(int ticarray[9]){
	    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(ticarray[wins[i][0]] != 0 &&
           ticarray[wins[i][0]] == ticarray[wins[i][1]] &&
           ticarray[wins[i][0]] == ticarray[wins[i][2]])
            return ticarray[wins[i][2]];
    }
    return 0;
}
