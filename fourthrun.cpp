//If a number is only possible within the same row or column within a single box
//then that number cannot be possible on the same row or column outside of 
//that box.

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
						initialRunThrough(sudoku);
						newValueSet = true;
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
		sameCol = false,
		diffRow = false,
		diffCol = false;
	int value = -1;
	int cnt; 
	bool changed = false;

	for(int x = 0; x < size; x++){
		value = sudoku[row][col]->possible[x];
		sameRow = false;
		sameCol = false;
		diffRow = false;
		diffCol = false;
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){

				if(!(sudoku[i][j]->isSet) && (sudoku[i][j]->box == boxNum) 
					&& (sudoku[i][j]->ID != id)){

					
					if(VectorContains(sudoku, i, j, value)){
						if(i == row)
							sameRow = true;
						if(j == col) 
							sameCol = true;
						if(i != row)
							diffRow = true;
						if(j != col)
							diffCol = true;
					}
				}
			}
		}

		if(sameRow && !diffRow){
			//remove value from rest of row
			for(int c = 0; c < 9; c++){
				if(sudoku[row][c]->box != boxNum){
					cnt = sudoku[row][c]->count;
					removeImpossibleValue(sudoku, row, c, value);
					if(cnt != sudoku[row][c]->count){
						changed = true;
						if(sudoku[row][c]->count == 1){
							setCellValue(sudoku, row, c);
						}
					}
				}
			}
		}else if(sameCol && !diffCol){
			//remove value from rest of column
			for(int r = 0; r < 9; r++){
				if(sudoku[r][col]->box != boxNum){
					cnt = sudoku[r][col]->count;
					removeImpossibleValue(sudoku, r, col, value);
					if(cnt != sudoku[r][col]->count){
						changed = true;
						if(sudoku[r][col]->count == 1){
							setCellValue(sudoku, r, col);
						}
					}
				}
			}
		}
	}

	return changed;
}





