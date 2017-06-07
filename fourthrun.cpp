#include "sudoku.h"

void fourthRunThrough(Cell *** &sudoku){
	bool newValueSet;
	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					if(uniqueRowOrColumn(sudoku, i, j)){
						thirdRunThrough(sudoku);	
						//newValueSet = true;
					}
				}
			}
		}		
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);
}


bool uniqueRowOrColumn(Cell *** &sudoku, int row, int col){

	int boxNum = sudoku[row][col]->box;
	int id = sudoku[row][col]->ID;
	int size = sudoku[row][col]->count;
	bool sameRow = false,
		sameCol = false;
	int value = -1;
	bool changed = false;


	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(!(sudoku[i][j]->isSet) && (sudoku[i][j]->box == boxNum) && (sudoku[i][j]->ID != id)){
				for(int x = 0; x < size; x++){
					sameRow = false;
					sameCol = false;
					value = sudoku[row][col]->possible[x];
					if(VectorContains(sudoku, i, j, value)){
						if(i == row){
							sameRow = true;
						} 
						if(j == col){ 
							sameCol = true;
						}

					if(sameRow && !sameCol)
						//remove value from rest of row
						for(int c = 0; c < 9; c++){
							if(sudoku[row][c]->box != boxNum){
								removeImpossibleValue(sudoku, row, c, value);
								changed = true;
							}
						}
					}else if(sameCol && !sameRow){
						//remove value from rest of column
						for(int r = 0; r < 9; r++){
							if(sudoku[r][col]->box != boxNum){
								removeImpossibleValue(sudoku, r, col, value);
								changed = true;
							}
						}
					}
				}
			}
		}
	}

	return changed;
}