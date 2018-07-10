#include<stdio.h>

typedef struct ReversiMove {
	int x, y;
}ReversiMove;


ReversiMove *createMove(int x, int y)
{
	ReversiMove *newMove = (ReversiMove*)malloc(sizeof(ReversiMove));
	newMove->x = x;
	newMove->y = y;
	return newMove;
}



ReversiMove *inputMove(ReversiGame *game)
{
	int x, y;
	printf("Enter row of the move: ");
	scanf("%d", &x);
	printf("Enter column of the move: ");
	scanf("%d", &y);
	ReversiMove *newMove = (ReversiMove*)malloc(sizeof(ReversiMove));
	newMove->x = x;
	newMove->y = y;
	return newMove;
}



int isvalidCoordinate(ReversiGame *game, int x, int y)
{
	if (x > game->cols || y > game->rows || x <= 0 || y <= 0)
		return 0;
	else
	{
		if (game->board[y - 1][x - 1] != ' ')
			return 0;
	}
	return 1;
}



int isValidMove(ReversiGame *game, ReversiMove *move)
{
	if (isvalidCoordinate(game, move->x, move->y))
	{
		int iter1, iter2, iter3, iter4, count = 0;
		char c, d;
		if (game->turn == 1)
		{
			c = 'w';
			d = 'b';
		}
		else if (game->turn == -1)
		{
			c = 'b';
			d = 'w';
		}

		for (iter1 = move->x - 2; iter1 >= 0; iter1--)
		{
			if (game->board[move->y - 1][iter1] == c)
			{
				for (iter2 = move->x - 2; iter2 > iter1; iter2--)
				{
					if (game->board[move->y - 1][iter2] == d)
						count++;
				}
				if ((move->x - 1) - iter1 - 1 == count && count != 0)
					return 1;
				break;
			}
		}


		for (iter1 = move->y - 2; iter1 >= 0; iter1--)
		{
			if (game->board[iter1][move->x - 1] == c)
			{
				for (iter2 = move->y - 2; iter2 > iter1; iter2--)
				{
					if (game->board[iter2][move->x - 1] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		for (iter1 = move->x; iter1 < game->cols; iter1++)
		{
			if (game->board[move->y - 1][iter1] == c)
			{
				for (iter2 = move->x; iter2 < iter1; iter2++)
				{
					if (game->board[move->y - 1][iter2] == d)
						count++;
				}
				if (iter1 - (move->x - 1) - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		for (iter1 = move->y; iter1 < game->rows; iter1++)
		{
			if (game->board[iter1][move->x - 1] == c)
			{
				for (iter2 = move->y; iter2 < iter1; iter2++)
				{
					if (game->board[iter2][move->x - 1] == d)
						count++;
				}
				if (iter1 - (move->y - 1) - 1 == count && count != 0)
					return 1;
				break;
			}
		}


		for (iter2 = move->x - 2, iter1 = move->y - 2; iter1 >= 0 && iter2 >= 0; iter1--, iter2--)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter4 = move->x - 2, iter3 = move->y - 2; iter3 > iter1 && iter4 > iter2; iter3--, iter4--)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		for (iter2 = move->x - 2, iter1 = move->y; iter1 < game->rows && iter2 >= 0; iter1++, iter2--)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y, iter4 = move->x - 2; iter3 < iter1 && iter4 > iter2; iter3++, iter4--)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->x - 1) - iter2 - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		for (iter2 = move->x, iter1 = move->y - 2; iter1 >= 0 && iter2 < game->cols; iter1--, iter2++)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y - 2, iter4 = move->x; iter4 < iter2 && iter3 >= 0; iter3--, iter4++)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		for (iter2 = move->x, iter1 = move->y; iter1 < game->rows && iter2 < game->cols; iter1++, iter2++)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y, iter4 = move->x; iter4 < iter2 && iter3 < iter1; iter3++, iter4++)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if (iter2 - (move->x - 1) - 1 == count && count != 0)
					return 1;
				break;
			}
		}

		return 0;

	}
	else
	{
		return 0;
	}
}


int hasMove(ReversiGame *game)
{
	int count = 0;
	for (int iter1 = 0; iter1 < game->rows; iter1++)
	{
		for (int iter2 = 0; iter2 < game->cols; iter2++)
		{
			if (game->board[iter1][iter2] == ' ')
			{
				count++;
			}
		}
	}
	if (count == 0)
	{
		endGame(game);
		return 0;
	}
	else
	{
		count = 0;
		for (int iter1 = 0; iter1 < game->rows; iter1++)
		{
			for (int iter2 = 0; iter2 < game->cols; iter2++)
			{

				ReversiMove *Move = createMove(iter1 + 1, iter2 + 1);
				if (isValidMove(game, Move))
				{
					count++;
				}
			}
		}
		if (count == 0)
		{
			endGame(game);
			return 0;
		}
		return 1;
	}
}


void incrementMoves(ReversiGame *game)
{
	game->NumberofMoves++;
	return;
}


void modifyTurn(ReversiGame *game)
{
	if (game->turn == -1)
		game->turn = 1;
	else if (game->turn == 1)
		game->turn = -1;
	return;
}


void endGame(ReversiGame *game)
{
	int count1 = 0, count2 = 0;
	for (int iter1 = 0; iter1 < game->rows; iter1++)
	{
		for (int iter2 = 0; iter2 < game->cols; iter2++)
		{
			if (game->board[iter1][iter2] == 'w')
			{
				count1++;
			}
			else if (game->board[iter1][iter2] == 'b')
			{
				count2++;
			}

		}
	}
	if (count1 > count2)
		game->winner = 1;
	else if (count2 > count1)
		game->winner = -1;
	else
		game->winner = 0;
	game->state = 1;
	return;
}



void modify(ReversiGame *game)
{
	incrementMoves(game);
	modifyTurn(game);
}


bool playMove(ReversiGame *game, ReversiMove *move)
{
	if (isValidMove(game, move))
	{
		int iter1, iter2, iter3, iter4, count = 0;
		char c, d;
		if (game->turn == 1)
		{
			c = 'w';
			d = 'b';
		}
		else if (game->turn == -1)
		{
			c = 'b';
			d = 'w';
		}
		game->board[move->y - 1][move->x - 1] = c;
		count = 0;
		for (iter1 = move->x - 2; iter1 >= 0; iter1--)
		{
			if (game->board[move->y - 1][iter1] == c)
			{
				for (iter2 = move->x - 2; iter2 > iter1; iter2--)
				{
					if (game->board[move->y - 1][iter2] == d)
						count++;
				}
				if ((move->x - 1) - iter1 - 1 == count && count != 0)
				{
					for (iter2 = move->x - 2; iter2 > iter1; iter2--)
					{
						game->board[move->y - 1][iter2] = c;
					}
				}
				break;
			}
		}

		count = 0;
		for (iter1 = move->y - 2; iter1 >= 0; iter1--)
		{
			if (game->board[iter1][move->x - 1] == c)
			{
				for (iter2 = move->y - 2; iter2 > iter1; iter2--)
				{
					if (game->board[iter2][move->x - 1] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
				{
					for (iter2 = move->y - 2; iter2 > iter1; iter2--)
					{
						game->board[iter2][move->x - 1] = c;
					}
				}
				break;
			}
		}
		count = 0;

		for (iter1 = move->x; iter1 < game->cols; iter1++)
		{
			if (game->board[move->y - 1][iter1] == c)
			{
				for (iter2 = move->x; iter2 < iter1; iter2++)
				{
					if (game->board[move->y - 1][iter2] == d)
						count++;
				}
				if (iter1 - (move->x - 1) - 1 == count && count != 0)
				{
					for (iter2 = move->x; iter2 < iter1; iter2++)
					{
						game->board[move->y - 1][iter2] = c;
					}
				}
				break;
			}
		}
		count = 0;
		for (iter1 = move->y; iter1 < game->rows; iter1++)
		{
			if (game->board[iter1][move->x - 1] == c)
			{
				for (iter2 = move->y; iter2 < iter1; iter2++)
				{
					if (game->board[iter2][move->x - 1] == d)
						count++;
				}
				if (iter1 - (move->y - 1) - 1 == count && count != 0)
				{
					for (iter2 = move->y; iter2 < iter1; iter2++)
					{
						game->board[iter2][move->x - 1] = c;
					}
				}

				break;
			}
		}

		count = 0;
		for (iter2 = move->x - 2, iter1 = move->y - 2; iter1 >= 0 && iter2 >= 0; iter1--, iter2--)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter4 = move->x - 2, iter3 = move->y - 2; iter3 > iter1 && iter4 > iter2; iter3--, iter4--)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
				{
					for (iter4 = move->x - 2, iter3 = move->y - 2; iter3 > iter1 && iter4 > iter2; iter3--, iter4--)
					{
						game->board[iter3][iter4] = c;
					}

				}

				break;
			}
		}
		count = 0;
		for (iter2 = move->x - 2, iter1 = move->y; iter1 < game->rows && iter2 >= 0; iter1++, iter2--)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y, iter4 = move->x - 2; iter3 < iter1 && iter4 > iter2; iter3++, iter4--)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->x - 1) - iter2 - 1 == count && count != 0)
				{
					for (iter3 = move->y, iter4 = move->x - 2; iter3 < iter1 && iter4 > iter2; iter3++, iter4--)
					{
						game->board[iter3][iter4] = c;
					}

				}

				break;
			}
		}
		count = 0;
		for (iter2 = move->x, iter1 = move->y - 2; iter1 >= 0 && iter2 < game->cols; iter1--, iter2++)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y - 2, iter4 = move->x; iter4 < iter2 && iter3 >= 0; iter3--, iter4++)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if ((move->y - 1) - iter1 - 1 == count && count != 0)
				{
					for (iter3 = move->y - 2, iter4 = move->x; iter4 < iter2 && iter3 >= 0; iter3--, iter4++)
					{
						game->board[iter3][iter4] = c;
					}
				}

				break;
			}
		}
		count = 0;
		for (iter2 = move->x, iter1 = move->y; iter1 < game->rows && iter2 < game->cols; iter1++, iter2++)
		{
			if (game->board[iter1][iter2] == c)
			{
				for (iter3 = move->y, iter4 = move->x; iter4 < iter2 && iter3 < iter1; iter3++, iter4++)
				{
					if (game->board[iter3][iter4] == d)
						count++;
				}
				if (iter2 - (move->x - 1) - 1 == count && count != 0)
				{
					for (iter3 = move->y, iter4 = move->x; iter4 < iter2 && iter3 < iter1; iter3++, iter4++)
					{
						game->board[iter3][iter4] = c;
					}
				}
				break;
			}
		}
		game->whiteCount = 0;
		game->blackCount = 0;
		for (iter1 = 0; iter1 < game->rows; iter1++)
		{
			for (iter2 = 0; iter2 < game->cols; iter2++)
			{
				char c = game->board[iter1][iter2];
				if (c == 'w')
				{
					game->whiteCount++;
				}
				else if (c == 'b')
				{
					game->blackCount++;
				}
			}
		}
		modify(game);
		if (!hasMove(game))
		{
			game->turn = (-1)*(game->turn);
		}
		return true;
	}
	else
	{
		printf("Enter a valid Move\n");
		return false;
	}

}


void printWinner(ReversiGame *game)
{
	if (game->winner == 1)
		printf("Result: %s has won\n", game->player1name);
	else if (game->winner == -1)
		printf("Result: %s has won\n", game->player2name);
	else
		printf("Result: Game is draw\n");
}