#define _CRT_SECURE_NO_WARNINGS
#include "BoardUtils.h"
#include "BoardMoves.h"




int main(){

	int rows = 4, cols = 4;
	char *player1 = (char *)malloc(sizeof(char) * 50);
	char *player2 = (char *)malloc(sizeof(char) * 50);
	printf("Enter player1 name:\n");
	scanf("%[^\n]", player1);
	printf("Enter player2 name:\n");
	scanf("\n%[^\n]", player2);

	ReversiGame *game = createNewGame(rows, cols,player1, player2);

	char table1[4][5] =
	{
		"    ",
		" wb ",
		" bw ",
		"    "
	};

	initializeReversiGame(game, (char *)table1, rows, cols, 1);
	clearAndRedrawScreen(game);
	while (hasMove(game))
	{
		if (game->turn == 1)
			printf("%s turn 'w' \n", game->player1name);
		else if (game->turn == -1)
			printf("%s turn 'b' \n", game->player2name);

		playMove(game,inputMove(game));
		clearAndRedrawScreen(game);
	}

	printWinner(game);


	/*int MoveX[] = { 4, 4, 2, 4, 1, 1, 3, 4, 1, 1, 3 };
	int MoveY[] = { 2, 3, 4, 1, 4, 3, 4, 4, 2, 1, 1 };
	int whiteMoveCount[] = { 4, 3, 6, 5, 3, 5, 3, 5, 2, 4, 3, };
	int blackMoveCount[] = { 1, 3, 1, 3, 6, 5, 8, 7, 11, 10, 12 };
	int turn[] = { 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1 };

	for (int i = 0; i < 11; i++){

		playMove(game, createMove(MoveX[i], MoveY[i]));
		for (int iter1 = 0; iter1 < game->rows; iter1++)
		{
			for (int iter2 = 0; iter2 < game->cols; iter2++)
			{
				printf("%c ", game->board[iter1][iter2]);
			}
			printf("\n");
		}
		printf("wc-%d bc-%d\n", game->whiteCount, game->blackCount);
	}*/










	


	system("pause");
	return 0;
}
