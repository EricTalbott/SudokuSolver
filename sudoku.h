#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


struct Cell{
	int number;
	bool isSet;
	int box;
	int ID;
	int* possible;
	int count;
};

typedef std::multimap<int, int> boxMap;
typedef boxMap::iterator mapIter;

//Initialization
int ** createPuzzle();
Cell *** setUpPuzzle(int ** puzzle);
int *** readFile (std::string fileName);

//Printers
void printPuzzle(int ** puzzle);
void printBox();
void printPossibilities(Cell *** sudoku);
int** makePrintablePuzzle(Cell *** sudoku);

//Runners and related functions
void initialRunThrough(Cell *** &sudoku);
void findPossibleValues(Cell *** &sudoku, int i, int j);

void nextRunThrough(Cell *** &sudoku);
void checkUniquePossibilities(Cell *** &sudoku, int i, int j);

void thirdRunThrough(Cell *** &sudoku);
bool twinValuePossible(Cell *** &sudoku, int row, int col);

void fourthRunThrough(Cell *** &sudoku);
bool uniqueRowOrColumn(Cell *** &sudoku, int row, int col);

//Mutators
void removeImpossibleValue(Cell *** &sudoku, int row, int col, int value);
void clearBox();

//Bool operators (Checkers)
bool puzzleSolved(Cell *** sudoku);
bool visibleVectorContains(Cell *** sudoku, int boxNum, int value, int id, int row, int column);
bool VectorContains(Cell *** sudoku, int rw, int col, int value);
bool boxContains(int boxNumber, int value);
bool rowContains(Cell *** sudoku, int value, int row);
bool columnContains(Cell *** sudoku, int value, int column);


//Setters
void setCellValue(Cell *** &sudoku, int row, int col);
void setPossibleValue(int value, int* &poss, int &count);
int addToBox(int number, int i, int j);