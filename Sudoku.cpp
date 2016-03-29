#include <iostream>
#include <cstring>

// Sudoku solver!
// By Allan Rodriguez
// Started Monday, 20th of July, 2015
// Can solve up to hard sudoku puzzles

void checkForPossibleNumbers(int puzzle[9][9]);

void runTheHalls(int puzzle[9][9], int bleh[9], int k, int l);

int sum(int bleh[9]);

void print(int puzzle[9][9]);

void setNumber(int puzzle[9][9], int naynay[9][9][9], int row, int column, int num);

void checkNonet(int puzzle[9][9], int naynay[9][9][9], int nonet);

void newFunction(int puzzle[9][9], int naynay[9][9][9]);

int main(void)
{
	int puzzle[9][9] = { { 0 } };

	printf("Sudoku solver!\n");
#ifndef DEBUG
	for (int i = 0; i < 9; i++)
	{
		switch (i + 1)
		{
		case 1:
			printf("Please enter the numbers in the 1st row of the puzzle: ");
			break;
		case 2:
			printf("Please enter the numbers in the 2nd row of the puzzle: ");
			break;
		case 3:
			printf("Please enter the numbers in the 3rd row of the puzzle: ");
			break;
		default:
			printf("Please enter the numbers in the %dth row of the puzzle: ", i + 1);
			break;
		}
		std::cin >> puzzle[i][0] >> puzzle[i][1] >> puzzle[i][2] >> puzzle[i][3] >> puzzle[i][4] >> puzzle[i][5] >>
			puzzle[i][6] >> puzzle[i][7] >> puzzle[i][8];
	}
#endif

#ifdef DEBUG
	puzzle[0][2] = puzzle[3][1] = 1;
	puzzle[4][2] = puzzle[5][7] = 2;
	puzzle[1][3] = puzzle[4][8] = puzzle[8][6] = 3;
	puzzle[2][0] = puzzle[8][4] = 4;
	puzzle[2][8] = puzzle[6][2] = puzzle[8][7] = 5;
	puzzle[1][5] = puzzle[4][6] = puzzle[6][8] = puzzle[7][3] = 6;
	puzzle[0][1] = puzzle[2][6] = puzzle[6][7] = puzzle[7][5] = puzzle[8][2] = 7;
	puzzle[0][6] = puzzle[5][5] = puzzle[6][0] = 8;
	puzzle[0][4] = puzzle[2][1] = puzzle[3][3] = puzzle[4][0] = 9;

#endif
	checkForPossibleNumbers(puzzle);

	system("PAUSE");

	return 0;
}

void checkForPossibleNumbers(int puzzle[9][9])
{
	int naynay[9][9][9] = { { { 0 } } };
	int x;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (puzzle[i][j] == 0)
			{
				runTheHalls(puzzle, naynay[i][j], i, j);
			}
		}
	}

	for (int i = 0; i < 50; i++)		// Hopefully by this many iterations, the program will have solved a sudoku puzzle :0
	{
		newFunction(puzzle, naynay);

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				x = 0;
				x = sum(naynay[i][j]);
				if (x != -1)
				{
					setNumber(puzzle, naynay, i, j, x + 1);
					newFunction(puzzle, naynay);
				}
			}
		}

		for (int i = 0; i < 9; i++)
		{
			checkNonet(puzzle, naynay, i);
		}
	}
	std::cout << "\nSolved! Below is your puzzle :)";
	print(puzzle);
}

void runTheHalls(int puzzle[9][9], int bleh[9], int k, int l)	// Eliminates numbers already given in the puzzle from the list of
{								// possible numbers
	int i;

	for (i = 0; i < 9; i++)
	{
		bleh[i] = 1;
	}
	for (i = 0; i < 9; i++)
	{
		if (puzzle[k][i] != 0)
		{
			bleh[puzzle[k][i] - 1] = 0;
		}
		if (puzzle[i][l] != 0)
		{
			bleh[puzzle[i][l] - 1] = 0;
		}
	}
}

int sum(int bleh[9])			// Checks to see if there is only one available number for a given spot to fill
{
	int g = 0, k = 0;
	for (int i = 0; i < 9; i++)
	{
		g += bleh[i];
		if (bleh[i] == 1)
		{
			k = i;
		}
	}

	if (g == 1)
	{
		return k;
	}

	return -1;
}

void print(int puzzle[9][9])								// Prints the puzzle out to the screen
{
	std::cout << "\n\n";
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 0)
			{
				std::cout << "\n";
			}
			(puzzle[i][j] == 0) ? std::cout << "_ " : std::cout << puzzle[i][j] << " ";
		}
	}
	std::cout << "\n\n\n";
}

void setNumber(int puzzle[9][9], int naynay[9][9][9], int row, int column, int num)	// Sets a number in the puzzle and clears
{											// the array for possible numbers (naynay)
	puzzle[row][column] = num;
	memset(naynay[row][column], 0, sizeof naynay[row][column]);

	for (int i = 0; i < 9; i++)
	{
		naynay[row][i][num - 1] = 0;
		naynay[i][column][num - 1] = 0;
	}
}

void checkNonet(int puzzle[9][9], int naynay[9][9][9], int nonet)
{
	int hi = 0, jay = 0;
	int lisa[9] = { 0 };

	for (int i = nonet / 3 * 3; i < nonet / 3 * 3 + 3; i++)		// Nonets should be 0-8, NOT 1-9
	{
		for (int j = nonet % 3 * 3; j < nonet % 3 * 3 + 3; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (naynay[i][j][k] != 0)
				{
					lisa[k] += naynay[i][j][k];
				}
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (lisa[i] == 1)
		{
			hi = i;
			for (int j = nonet / 3 * 3; j < nonet / 3 * 3 + 3; j++)		// Nonets should be 0-8, NOT 1-9
			{
				for (int k = nonet % 3 * 3; k < nonet % 3 * 3 + 3; k++)
				{
					if (naynay[j][k][i] == 1)
					{
						i = k = j = 10;
					}
					else
					{
						jay++;
					}
				}
			}

			setNumber(puzzle, naynay, nonet / 3 * 3 + jay / 3, nonet % 3 * 3 + jay % 3, hi + 1);
		}
	}
}

void newFunction(int puzzle[9][9], int naynay[9][9][9])
{
	for (int a = 0; a < 9; a++)
	{
		for (int i = a / 3 * 3; i < a / 3 * 3 + 3; i++)
		{
			for (int j = a % 3 * 3; j < a % 3 * 3 + 3; j++)
			{
				if (puzzle[i][j] != 0)
				{
					for (int k = a / 3 * 3; k < a / 3 * 3 + 3; k++)
					{
						for (int l = a % 3 * 3; l < a % 3 * 3 + 3; l++)
						{
							naynay[k][l][puzzle[i][j] - 1] = 0;
						}
					}
				}
			}
		}
	}
}
