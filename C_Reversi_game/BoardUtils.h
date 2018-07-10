#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ReversiGame {
	char **board;	
	char *player1name;
	char *player2name;
	int whiteCount = 0;
	int blackCount = 0;
	int NumberofMoves = 0;
	int rows, cols;
	int turn = 1;   
	int state = 0;  
	int winner = 0; 
}ReversiGame;


void endGame(ReversiGame *game);
int hasMove(ReversiGame *game);
void modifyTurn(ReversiGame *game);


ReversiGame * createNewGame(int rows, int cols, char *player1, char *player2)
{
	if (cols <= 0 || rows <= 0 || player1 == NULL || player2 == NULL || cols != rows)
		return NULL;
	else
	{
		int iter1, iter2;
		ReversiGame *newlyCreatedGame = (ReversiGame *)malloc(sizeof(ReversiGame));
		char **board = (char **)malloc(sizeof(char*)*rows);
		for (int iter = 0; iter < rows; iter++)
		{
			board[iter] = (char*)malloc(sizeof(char*)*(cols + 1));
		}
		newlyCreatedGame->board = board;
		newlyCreatedGame->rows = rows;
		newlyCreatedGame->cols = cols;
		newlyCreatedGame->player1name = player1;
		newlyCreatedGame->player2name = player2;
		newlyCreatedGame->NumberofMoves = 0;
		newlyCreatedGame->state = 0;
		for (iter1 = 0; iter1 < rows; iter1++)
		{
			for (iter2 = 0; iter2 < cols + 1; iter2++)
			{
				newlyCreatedGame->board[iter1][iter2] = '-';
			}
			newlyCreatedGame->board[iter1][iter2] = '\0';
		}
		return newlyCreatedGame;
	}
}


void initializeReversiGame(ReversiGame *game, char *tobeCopiedBoard, int rows, int cols, int turn)
{
	int iter1, iter2, iter3 = 0;
	game->whiteCount = 0, game->blackCount = 0;
	for (iter1 = 0; iter1 < rows; iter1++)
	{
		for (iter2 = 0; iter2 < cols; iter2++)
		{
			char c = (*(tobeCopiedBoard + iter3));
			if (c == 'w')
			{
				game->whiteCount++;
			}
			else if (c == 'b')
			{
				game->blackCount++;
			}
			game->board[iter1][iter2] = (*(tobeCopiedBoard + (iter3++)));
		}
		game->board[iter1][iter2] = '\0';
		iter3++;
	}
	game->turn = turn;
	if (game->whiteCount + game->blackCount == game->rows*game->cols)
		game->state = 1;
	else
		game->state = 0;

}


int checkReversiGameOver(ReversiGame *game)
{
	int iter1, iter2;
	if (!hasMove(game))
	{
		game->turn = (-1)*(game->turn);
		if (!hasMove(game))
		{
			game->turn = (-1)*(game->turn);
			return 0;
		}
	}
	return 1;
}

void printMoves(ReversiGame *game)
{

	printf("\t\tWhites Count : %d\n", game->whiteCount);
	printf("\t\tBlack Count : %d\n", game->blackCount);
	printf("\t\tMove Count : %d\n", game->blackCount + game->whiteCount);
	return;
}



void drawBoardOnScreen(ReversiGame *game)
{ 
	for (int iter1 = 0; iter1 < game->rows; iter1++)
	{
		printf("\t\t");
		for (int iter2 = 0; iter2 < game->cols; iter2++)
		{
			printf("%c ", game->board[iter1][iter2]);
		}
		printf("\n");
	}
	//printf("wc-%d bc-%d\n", game->whiteCount, game->blackCount);
	printMoves(game);
	printf("\n\n\n");
	return;
}



void clearScreen(ReversiGame *game){
	system("cls");
}


void clearAndRedrawScreen(ReversiGame *game)
{
	system("cls");
	drawBoardOnScreen(game);
}






