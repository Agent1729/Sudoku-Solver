#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H



#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
	int val;
	int *canbe;
} Cell;

void readVals(Cell **grid, FILE *input_file);

int charToInt(char a);

void printVals(Cell **grid);

void setCanBe(Cell **grid);

int getGridStartNum(int y, int x);

int checkCanBe(Cell **grid);

void printCanBe(Cell **grid, int x, int y);

int checkRCGMissing(Cell **grid);

void setVal(Cell **grid, int y, int x, int value);

int numberLeft(Cell **grid);

void gridCopy(Cell **gridD, Cell **gridS);

int guess(Cell **grid, int depth);

int iterateGuess(Cell **grid, int depth);

void printTabs(int num);

#endif