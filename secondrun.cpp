#include "sudoku.h"

void nextRunThrough(Cell *** &sudoku){
	bool newValueSet;
	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					checkUniquePossibilities(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
						setCellValue(sudoku, i, j);
						initialRunThrough(sudoku);	
						newValueSet = true;
					}
				}
			}
		}		
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);
}

void checkUniquePossibilities(Cell *** &sudoku, int row, int col){
	int boxNum, value, id;

	boxNum = sudoku[row][col]->box;
	id = sudoku[row][col]->ID;

  	for (int i = 0; i < sudoku[row][col]->count; i++){
    	value = sudoku[row][col]->possible[i];
    	if(!(visibleVectorContains(sudoku, boxNum, value, id, row, col))){
    		setPossibleValue(value, sudoku[row][col]->possible, sudoku[row][col]->count);
    	}
  	}
}