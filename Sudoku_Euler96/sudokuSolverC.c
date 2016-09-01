#include <stdio.h>
#include <stdlib.h>
#include "sudokuSolver.h"

#define PRINT_WHERE_CHANGED 0
#define GUESS_CHANCE_MAX 2
#define MAX_GUESS_DEPTH 3
#define SHOW_GUESSINGS 0

//Read input_file into the grid
void readVals(Cell **grid, FILE *input_file)
{
	char *read;
	int i, j;
	char *r;

	r = (char *)malloc(2 * sizeof(char)); r[1] = '\0';
	read = (char *)malloc(10 * sizeof(char));
	fgets(read, 12, input_file);
	printf("%s", read);

	for (i = 0; i < 9; i++)
	{
		fgets(read, 12, input_file);
		printf("%s", read);
		for (j = 0; j < 9; j++)
		{
			r[0] = read[j];
			grid[i][j].val = atoi(r);
		}
	}
	printf("\n\n");

	return;
}

//Used for debugging, prints out the grid
void printVals(Cell **grid)
{
	int i, j;

	printf("+-------+-------+-------+\n");
	for (i = 0; i < 9; i++)
	{
		printf("| ");
		for (j = 0; j < 9; j++)
		{
			printf("%d ", grid[i][j].val);
			if (3 * ((j + 1) / 3) == (j + 1))
				printf("| ");
		}
		if (3 * ((i + 1) / 3) == (i + 1))
			printf("\n+-------+-------+-------+");
		printf("\n");
	}
	printf("\n");

	return;
}

//Sets valid values for each cell based on the row, column, and minigrid
void setCanBe(Cell **grid)
{
	int i, j;
	int k;
	int l, m;
	int found;
	int temp1, temp2;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			//For each cell
			if (grid[i][j].val > 0)
			{
				for (k = 0; k < 9; k++)
					grid[i][j].canbe[k] = 0;
			}

			for (k = 0; k < 9; k++)
			{
				//For each canbe val
				found = 0;
				//Horizontal Check
				for (l = 0; l < 9; l++)
				{
					if (grid[i][l].val == k + 1)
						found = 1;
				}
				//Vertical Check
				for (m = 0; m < 9; m++)
				{
					if (grid[m][j].val == k + 1)
						found = 1;
				}
				//Grid Check
				for (l = 0; l < 3; l++)
				{
					for (m = 0; m < 3; m++)
					{
						temp1 = i / 3;
						temp2 = j / 3;
						if (grid[l + 3 * temp1][m + 3 * temp2].val == k + 1)
							found = 1;
					}
				}

				if (found == 1)
					grid[i][j].canbe[k] = 0;

			}//End each canbe

		}//End each cell
	}

	return;
}

//Checks values based on what they can be
int checkCanBe(Cell **grid)
{
	int i, j;
	int k;
	int num_changed = 0;
	int last_can_be;

	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			//For each cell
			last_can_be = 0;
			for (k = 0; k<9; k++)
			{
				if (grid[i][j].canbe[k] == 1)
				{
					if (last_can_be == 0)
					{
						last_can_be = k + 1;
					}
					else
					{
						last_can_be = 99;
						break;
					}
				}
			}

			if ((last_can_be>0) && (last_can_be<10))
			{
				num_changed++;
				if (PRINT_WHERE_CHANGED)
					printf("%d, %d changed to %d during checkCanBe...\n", j + 1, i + 1, last_can_be);
				setVal(grid, i, j, last_can_be);
			}

		}//End each cell
	}
	return num_changed;
}

//Print the values a cell can be
void printCanBe(Cell **grid, int x, int y)
{
	int k;

	printf("%d, %d can be:\t 0", x + 1, y + 1);
	for (k = 0; k<9; k++)
	{
		if (grid[y][x].canbe[k] == 1)
			printf(", %d", k + 1);
	}
	printf("...\n");

	return;
}

//Check each Row, Column, and minigrid (3x3) for missing values
int checkRCGMissing(Cell **grid)
{
	int num_changed = 0;
	int i, j;
	int k;
	int l, m;
	int last_spot;

	//Check Rows
	for (i = 0; i<9; i++)
	{
		//For each row
		for (k = 0; k<9; k++)
		{
			//For each val
			last_spot = -1;
			for (j = 0; j<9; j++)
			{
				if (grid[i][j].canbe[k] == 1)
				{
					if (last_spot == -1)
						last_spot = j;
					else
						last_spot = 99;
				}
			}

			if ((last_spot >= 0) && (last_spot<10))
			{
				num_changed++;
				if (PRINT_WHERE_CHANGED)
					printf("%d, %d changed to %d during checkR...\n", last_spot + 1, i + 1, k + 1);
				setVal(grid, i, last_spot, k + 1);
			}

		}//Last each val

	}//Last each row*/



	//Check Cols
	for (i = 0; i<9; i++)
	{
		//For each col
		for (k = 0; k<9; k++)
		{
			//For each val
			last_spot = -1;
			for (j = 0; j<9; j++)
			{
				if (grid[j][i].canbe[k] == 1)
				{
					if (last_spot == -1)
						last_spot = j;
					else
						last_spot = 99;
				}
			}

			if ((last_spot >= 0) && (last_spot<10))
			{
				num_changed++;
				if (PRINT_WHERE_CHANGED)
					printf("%d, %d changed to %d during checkC...\n", i + 1, last_spot + 1, k + 1);
				setVal(grid, last_spot, i, k + 1);
			}

		}//Last each val

	}//Last each col*/



	//Check Grids
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			//For each grid
			for (k = 0; k<9; k++)
			{
				//For each val
				last_spot = -1;

				for (l = 0; l<3; l++)
				{
					for (m = 0; m<3; m++)
					{
						if (grid[i * 3 + l][j * 3 + m].canbe[k] == 1)
						{
							if (last_spot == -1)
								last_spot = 3 * l + m;
							else
								last_spot = 99;
						}
					}
				}

				if ((last_spot >= 0) && (last_spot<10))
				{
					num_changed++;
					l = last_spot / 3;
					m = last_spot - 3 * l;
					if (PRINT_WHERE_CHANGED)
						printf("%d, %d changed to %d during checkG...\n", j * 3 + m + 1, i * 3 + l + 1, k + 1);
					setVal(grid, i * 3 + l, j * 3 + m, k + 1);
				}

			}//Last each val

		}//Last each grid
	}//*/

	return num_changed;
}

//Set the value of a cell, and modify others to show they can't be this value now
void setVal(Cell **grid, int y, int x, int value)
{
	int k;
	//printf("Setval called: %d, %d\n", x+1, y+1);
	grid[y][x].val = value;
	for (k = 0; k<9; k++)
		grid[y][x].canbe[k] = 0;
	setCanBe(grid);
	return;
}

//Returns number of unsolved cells
int numberLeft(Cell **grid)
{
	int i, j;
	int num_left = 0;
	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			if (grid[i][j].val == 0)
				num_left++;
		}
	}
	return num_left;
}

//Copies gridD(est) to gridS(ource)
void gridCopy(Cell **gridD, Cell **gridS)
{
	int i, j, k;
	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			gridD[i][j].val = gridS[i][j].val;
			for (k = 0; k<9; k++)
				gridD[i][j].canbe[k] = gridS[i][j].canbe[k];
		}
	}
	return;
}

//When all else fails... set up a copy of the grid with one guess made
int guess(Cell **grid, int depth)
{
	int i, j, k, l, m, n;
	int found;
	int guess_worked;
	int index_canbe;
	Cell **grid2 = (Cell **)malloc(9 * sizeof(Cell *));

	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			found = 0;
			for (k = 0; k<9; k++)
			{
				if (grid[i][j].canbe[k] == 1)
					found++;
			}
			if ((found>1) && (found <= GUESS_CHANCE_MAX))
			{
				//init grid
				for (l = 0; l<9; l++)
				{
					grid2[l] = (Cell *)malloc(9 * sizeof(Cell));
					for (m = 0; m<9; m++)
					{
						grid2[l][m].val = 9;
						grid2[l][m].canbe = (int *)malloc(9 * sizeof(int));
						for (n = 0; n<9; n++)
						{
							grid2[l][m].canbe[n] = 1;
						}
					}
				}

				index_canbe = 0;
				for (l = 0; l<found; l++)
				{
					do
					{
						index_canbe++;
					} while (grid[i][j].canbe[index_canbe] == 0);
					gridCopy(grid2, grid);
					if (SHOW_GUESSINGS)
					{
						printTabs(depth);
						printf("GUESSING\nGuess is: %d\tAt %d, %d\n", index_canbe + 1, j + 1, i + 1);
						printTabs(depth);
						//system("pause");
						printf("\n");
					}

					//guess with grid2[i][j].val=index_canbe+1
					setVal(grid2, i, j, index_canbe + 1);
					guess_worked = iterateGuess(grid2, depth + 1);

					if (guess_worked == 1)
					{
						gridCopy(grid, grid2);
						return 1;
					}
				}//Each guess at the location
			}//End guesses at this location (if)

		}
	}

	if (SHOW_GUESSINGS)
		printf("Guessing did not work, fully run through grid...\n");

	return 0;
}

//Takes a grid with an initial guess, checks to see if it can solve it
int iterateGuess(Cell **grid, int depth)
{
	int num_changed, num_left, guess_worked;

	do
	{
		setCanBe(grid);
		num_changed = 0;
		num_changed += checkCanBe(grid);
		num_changed += checkRCGMissing(grid);
		num_left = numberLeft(grid);
		if (SHOW_GUESSINGS)
		{
			printVals(grid);
			printTabs(depth);
			printf("%d changes this iteration (depth %d)...\n", num_changed, depth);
			printTabs(depth);
			printf("%d cells left to finish...\n", num_left);
			printTabs(depth);
			//system("pause");
			printf("\n");
		}
		if (num_left == 0)
			return 1;
	} while (num_changed != 0);

	//guess
	if (num_left>0)
	{
		if (depth <= MAX_GUESS_DEPTH)
		{
			guess_worked = guess(grid, depth + 1);
			if (guess_worked == 1)
				return 1;
		}
		else
		{
			if (SHOW_GUESSINGS)
				printf("MAX DEPTH REACHED!\n");
		}
	}

	return 0;
}

//Used for debugging, printfs num of tabs
void printTabs(int num)
{
	int i;
	for (i = 0; i < num; i++)
		printf("    ");
	return;
}