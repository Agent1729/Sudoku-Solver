#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H



#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
	int val;
	int *canbe;
} Cell;

//Read input_file into the grid
void readVals(Cell **grid, FILE *input_file);

//Used for debugging, prints out the grid
void printVals(Cell **grid);

//Sets valid values for each cell based on the row, column, and minigrid
void setCanBe(Cell **grid);

//Checks values based on what they can be
int checkCanBe(Cell **grid);

//Print the values a cell can be
void printCanBe(Cell **grid, int x, int y);

//Check each Row, Column, and minigrid (3x3) for missing values
int checkRCGMissing(Cell **grid);

//Set the value of a cell, and modify others to show they can't be this value now
void setVal(Cell **grid, int y, int x, int value);

//Returns number of unsolved cells
int numberLeft(Cell **grid);

//Copies gridD(est) to gridS(ource)
void gridCopy(Cell **gridD, Cell **gridS);

//When all else fails... set up a copy of the grid with one guess made
int guess(Cell **grid, int depth);

//Takes a grid with an initial guess, checks to see if it can solve it
int iterateGuess(Cell **grid, int depth);

//Used for debugging, printfs num of tabs
void printTabs(int num);

#endif