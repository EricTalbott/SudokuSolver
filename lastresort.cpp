#include "sudoku.h"


void lastResort(Cell *** &sudoku){

	clearBox();
	Cell*** temporary;
	temporary = createCopy(sudoku);

	int* coords;
	coords = unsetCellLocation(sudoku);
	int r = coords[0];
	int c = coords[1];
	if(r != -1 && c != -1){
		if(guessAndCheck(temporary, r, c)){
			delete sudoku;
			sudoku = createCopy(temporary);
			delete temporary;
		}
	}
}

//will return true if solved
bool guessAndCheck(Cell *** &sudoku, int row, int col){
	Cell*** temp;
	clearBox();
	temp = createCopy(sudoku);
	int count = sudoku[row][col]->count;
	int current = 0;

	while(current < count){
		setCellValueGAC(temp, row, col, current);
		temp[row][col]->count = 1;

		initialRunThrough(temp);

		if(unsolvable(temp)){
			current++;
			delete temp;
			clearBox();
			temp = createCopy(sudoku);
		}else{

			if(puzzleSolved(temp)){
				delete sudoku;
				clearBox();
				sudoku = createCopy(temp);
				return true;
			}

			int* coords;
			coords = unsetCellLocation(temp);
			int r = coords[0];
			int c = coords[1];
			if(r != -1 && c != -1){
				if(guessAndCheck(temp, r, c)){
					if(puzzleSolved(temp)){
						delete sudoku;
						clearBox();
						sudoku = createCopy(temp);
						return true;
					}
				}else{
					current++;
					delete temp;
					clearBox();
					temp = createCopy(sudoku);
				}
			}
		}
	}
	return false;
}

bool unsolvable(Cell *** sudoku){
	for(int r = 0; r < 9; r++){
		for(int c = 0; c < 9; c++){
			if(!(sudoku[r][c]->isSet) && sudoku[r][c]->count == 0 ){
				return true;
			}
		}
	}
	return false;
}

int* unsetCellLocation(Cell *** sudoku){
	int *coords = new int[2];
	coords[0] = -1;
	coords[1] = -1;
	for(int r = 0; r < 9; r++){
		for(int c = 0; c < 9; c++){
			if(!(sudoku[r][c]->isSet)){
				coords[0] = r;
				coords[1] = c;
				return coords;
			}
		}
	}
	return coords;
}
