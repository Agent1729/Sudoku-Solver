#include <stdio.h>
#include <stdlib.h>
#include "sudokuSolver.h"

#define SHOW_WORK 0
#define MIN_GRID_NUM 1
#define MAX_GRID_NUM 50

//A program written to solve projecteuler.net problem #96, SuDoku
//As written on the site:
//"The 6K text file contains fifty different Su Doku puzzles"
//"By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid"

int main()
{
	int total_sum = 0;
	int num_changed;
	int num_left;
	int guess_worked = -1;
	int grid_num;
	int i, j, k;
	Cell **grid = (Cell **)malloc(9 * sizeof(Cell *));
	FILE *input_file = NULL;

	//Input file contains 50 sudoku puzzles
	input_file = fopen("input.txt", "r");
	if (input_file == NULL)
		return 0;

	//init grid
	for (i = 0; i < 9; i++)
	{
		grid[i] = (Cell *)malloc(9 * sizeof(Cell));
		for (j = 0; j < 9; j++)
		{
			grid[i][j].val = 9;
			grid[i][j].canbe = (int *)malloc(9 * sizeof(int));
			for (k = 0; k < 9; k++)
			{
				grid[i][j].canbe[k] = 1;
			}
		}
	}

	for (grid_num = MIN_GRID_NUM; grid_num <= MAX_GRID_NUM; grid_num++)
	{
		//reset canbes
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				for (k = 0; k < 9; k++)
				{
					grid[i][j].canbe[k] = 1;
				}
			}
		}
		//first print
		readVals(grid, input_file);
		num_left = numberLeft(grid);
		if (SHOW_WORK)
		{
			printVals(grid);
			printf("%d cells left to finish...\n", num_left);
			system("pause");
			printf("\n");
		}

		//iterate
		do
		{
			setCanBe(grid);
			num_changed = 0;
			num_changed += checkCanBe(grid);
			num_changed += checkRCGMissing(grid);
			num_left = numberLeft(grid);
			if (SHOW_WORK)
			{
				printVals(grid);
				//printTabs(0);
				printf("%d changes this iteration...\n", num_changed);
				//printTabs(0);
				printf("%d cells left to finish...\n", num_left);
				//printTabs(0);
				system("pause");
				printf("\n");
			}
		} while (num_changed != 0);

		//guess
		if (num_left>0)
			guess_worked = guess(grid, 1);
		if (guess_worked == 0)
		{
			printf("Guess failed :/\n\n");
			return;
		}

		if (SHOW_WORK)
		{
			if (guess_worked == 1)
			{
				printf("GUESS WORKED!\n\n");
				printVals(grid);
				system("pause");
				printf("\n");
			}
			if (guess_worked == 0)
				printf("Guess failed :/\n\n");
			if (guess_worked == -1)
				printf("No guessing...\n\n");

		}

		num_left = numberLeft(grid);
		if (num_left != 0)
		{
			printf("INCOMPLETE!!!\nFailed on grid #%d...\n\n", grid_num);
			system("pause");
		}

		//Now that the grid is (hopefully) solved, add it's top left to the total value for our answer
		total_sum += grid[0][0].val * 100 + grid[0][1].val * 10 + grid[0][2].val * 1;

	}

	//Print out our answer!
	printf("\n\nTotal_sum: %d\n\n", total_sum);

	return 0;
}