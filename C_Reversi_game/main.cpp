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
	system("pause");
	return 0;
}
