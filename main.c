#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int FALSE = 0;
const int TRUE = 1;

const char HUMAN = 'X';
const char COMP = 'O';

int main()
{
	char pole[3*3];
	int choise, comp;
	int have_empty = TRUE;
	int have_win = FALSE;
	char why = HUMAN;


	for (int i=0; i< 3*3; i++) pole[i] = i + 1 + '0';

	srand(time(NULL));
	
	while(have_empty && !have_win) {
		printf("\033[2J");

		printf(" %c | %c | %c \n", pole[0], pole[1], pole[2]);
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", pole[3], pole[4], pole[5]);
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", pole[6], pole[7], pole[8]);



		if (why == HUMAN) {
			int agry = FALSE;
			do{
				printf("if you want to EXIT, press 10\nYour choise [1-9]:");
				scanf("%d", &choise);

				if (choise == 10) return 0;

				choise--;
				if ( choise >=0 && choise < 10 && 
							pole[choise] != HUMAN && pole[choise] != COMP)
					agry = TRUE;

			} while(!agry);
		}
		else {
			int agry = FALSE;
			do {
				choise = rand()%9;

				if (pole[choise] != HUMAN && pole[choise] != COMP) 
					agry = TRUE;

			}while(!agry);
		}

		pole[choise] = why;

		for (int i=0, have_empty = FALSE; (i< 3*3) && !have_empty; i++) {
			if (pole[i] != 'X' || pole[i] != 'O') have_empty = TRUE;
		}

		for (int i=0; i < 3;i++) {
			if (pole[i] == pole[i+1] && pole[i+1] == pole[i+2]) have_win = TRUE;
			else if (pole[i] == pole[i+3*1] && pole[i+3*1] == pole[i+ 3*2]) have_win = TRUE;
		}

		if (!have_win) {
			if (pole[0] == pole[4] && pole[4] == pole[8]) have_win = TRUE;
			else if (pole[2] == pole[4] && pole[4] == pole[6]) have_win = TRUE;
		}

		if (have_empty && !have_win) {
			if (why == HUMAN)
				why = COMP;
			else
				why = HUMAN;
		}
	}

	printf("\033[2J");
	printf(" %c | %c | %c \n", pole[0], pole[1], pole[2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n", pole[3], pole[4], pole[5]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n", pole[6], pole[7], pole[8]);
	printf("GAME OVER\n");
	if (!have_empty) printf("HUMAN && COMP WIN!!!");
	else if (why == HUMAN) printf("HUMAN WIN!!!");
	else printf("COMP WIN!!!");

	return 0;
}
