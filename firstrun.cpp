//Find every possible value for each cell, and if there is only 1 possible value, 
//set it as the value for the cell. 

#include "sudoku.h"

void initialRunThrough(Cell *** &sudoku){ 
	bool newValueSet;

	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					findPossibleValues(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
						setCellValue(sudoku, i, j);	
						initialRunThrough(sudoku);
					}
				}
			}
		}
		if(puzzleSolved(sudoku)) break;
	}while(newValueSet);
}

void findPossibleValues(Cell *** &sudoku, int row, int col){
	int notPos[9] = {-1};
	int notPosCnt = 0;
	int boxNum = sudoku[row][col]->box;

	//Check if value is contained in "visible" cell
	for(int val = 1; val <= 9; val++){
		if(columnContains(sudoku, val, col) || rowContains(sudoku, val, row) || boxContains(boxNum, val)){
			notPos[notPosCnt] = val;
			notPosCnt++;
		}
	}
	int value;

	for(int i = 0; i < notPosCnt; i++){
		value = notPos[i];
		removeImpossibleValue(sudoku, row, col, value);
	}
	/*
	//Set the possible values
	sudoku[row][col]->count = (9 - notPosCnt);
	int current = 0;

	int *finder;
	for(int i = 1; i <= 9; i++){
		finder = std::find(std::begin(notPos), std::end(notPos), i);
		if(finder == std::end(notPos)){
			sudoku[row][col]->possible[current]=i;
			current++;
		}
	}*/
}