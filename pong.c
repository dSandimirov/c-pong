#include <stdio.h>

const int Bottom = 25;
const int Border = 80;
const int RocketAction = 1;
const int speedBall = 1;
const int maxXRocket = 2, minXRocket = 23;
int Vector_x = 1, Vector_y = 1;

void gameField();
void printGameField(int x, int y, int LeftRocket_y, int RightRocket_y, int Ball_x, int Ball_y);
int rightRocketAction(char action, int RightRocket_y);
int leftRocketAction(char action, int LeftRocket_y);
int horisontalBallAction(int Ball_x);
int verticalBallAction(int Ball_y);
int gol(int Ball_y, int LeftRocket_y, int RightRocket_y);
void clear(void);

int main()
{
	return 0;
}

void gameField()
{
	int LeftRocket_y = 12;
	int RightRocket_y = 12;
	int Ball_x = 36, Ball_y = 12;

	char action;
	int scoreLeftPleer = 0;
	int scoreRightPleer = 0;
	int score = 21;

	clear();
	while (scoreLeftPleer != score && scoreRightPleer != score)
	{
		fflush(stdout);
		clear();

		printf("| Score player1: %d | Score player2: %d |\n", scoreLeftPleer, scoreRightPleer);

		for (int y = 0; y <= Bottom; y++)
		{
			if (y == 0 || y == Bottom)
			{
				for (int x = 0; x <= Border; x++)
				{
					printf("-");
				}
				printf("\n");
				continue;
			}

			for (int x = 0; x <= Border; x++)
			{
				printGameField(x, y, LeftRocket_y, RightRocket_y, Ball_x, Ball_y);
			}

			printf("\n");
		}

		scanf("%c", &action);

		if (action == 'a' || action == 'z' || action == 'A' || action == 'Z')
		{
			LeftRocket_y = leftRocketAction(action, LeftRocket_y);
			continue;
		}

		if (action == 'k' || action == 'm' || action == 'K' || action == 'M')
		{
			RightRocket_y = rightRocketAction(action, RightRocket_y);
			continue;
		}

		if (action == ' ' || action != EOF)
		{
			for (int i = 1; i <= speedBall; i++)
			{
				Ball_x = horisontalBallAction(Ball_x);
				Ball_y = verticalBallAction(Ball_y);

				if ((Ball_y != LeftRocket_y) ||
					(Ball_y != LeftRocket_y + 1) ||
					(Ball_y != LeftRocket_y - 1))
				{
					if (Ball_x == 1)
					{
						scoreRightPleer++;
						Ball_x = 35;
						Ball_y = 12;
						Vector_x = -1 * Vector_x;
					}
					if (Ball_x == Border - 1)
					{
						scoreLeftPleer++;
						Ball_x = 45;
						Ball_y = 12;
						Vector_x = -1 * Vector_x;
					}
				}

				if (((Ball_y == LeftRocket_y) ||
					 (Ball_y == LeftRocket_y + 1) ||
					 (Ball_y == LeftRocket_y - 1)) &&
					Ball_x == 3)
				{
					Vector_x = -1 * Vector_x;
				}
				if (((Ball_y == RightRocket_y) ||
					 (Ball_y == RightRocket_y + 1) ||
					 (Ball_y == RightRocket_y - 1)) &&
					Ball_x == Border - 3)
				{
					Vector_x = -1 * Vector_x;
				}
			}
		}

		if (action == 'q' || action == 'Q')
		{
			break;
		}

		// printf("|%d|%d|-|%d|%d|-|%d|%d|-|%d|%d|\n",
		// Ball_x, Ball_y,
		// LeftRocket_y, RightRocket_y,
		// scoreLeftPleer, scoreRightPleer,
		// Vector_x, Vector_y
		// );
	}
}

void printGameField(
	int x,
	int y,
	int LeftRocket_y,
	int RightRocket_y,
	int Ball_x,
	int Ball_y)
{
	if (x == Ball_x && y == Ball_y)
	{
		printf("*");
		return;
	}

	if (
		(
			x == Border / 2 ||
			x == Border ||
			x == 0))
	{
		printf("|");
		return;
	}

	if (x == 2 && (y == LeftRocket_y ||
				   y + 1 == LeftRocket_y ||
				   y - 1 == LeftRocket_y))
	{
		printf("|");
		return;
	}

	if (x == 78 && (y == RightRocket_y || y + 1 == RightRocket_y || y - 1 == RightRocket_y))
	{
		printf("|");
		return;
	}

	printf(" ");
}

int rightRocketAction(char action, int RightRocket_y)
{
	if ((action == 'k' || action == 'K') && RightRocket_y > maxXRocket)
	{
		return RightRocket_y - RocketAction;
	}

	if ((action == 'm' || action == 'M') && RightRocket_y < minXRocket)
	{
		return RightRocket_y + RocketAction;
	}

	return RightRocket_y;
}

int leftRocketAction(char action, int LeftRocket_y)
{
	if ((action == 'a' || action == 'A') && LeftRocket_y > maxXRocket)
	{
		return LeftRocket_y - RocketAction;
	}

	if ((action == 'z' || action == 'Z') && LeftRocket_y < minXRocket)
	{
		return LeftRocket_y + RocketAction;
	}

	return LeftRocket_y;
}

int horisontalBallAction(int Ball_x)
{
	if ((Ball_x < Border) && (Ball_x != 1) && (Ball_x != Border - 1))
	{
		return Ball_x + Vector_x;
	}

	if (Ball_x == 1)
	{
		Vector_x = -1 * Vector_x;
		return Ball_x + Vector_x;
	}

	if (Ball_x == Border - 1)
	{
		Vector_x = -1 * Vector_x;
		return Ball_x + Vector_x;
	}

	return 0;
}

int verticalBallAction(int Ball_y)
{
	if ((Ball_y < Bottom) && (Ball_y != 1) && (Ball_y != Bottom - 1))
	{
		return Ball_y + Vector_y;
	}

	if (Ball_y == 1)
	{
		Vector_y = -1 * Vector_y;
		return Ball_y + Vector_y;
	}

	if (Ball_y == Bottom - 1)
	{
		Vector_y = -1 * Vector_y;
		return Ball_y + Vector_y;
	}

	return 0;
}

void clear(void)
{
	printf("\033[2J");
	printf("\033[0;0f");
}
