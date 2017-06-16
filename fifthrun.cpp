//If a number can only exist in 2-3 cells within a row or colum and those cells
//are within the same box, then it cannot exist any other location within
//that box
#include "sudoku.h"

void fifthRunThrough(Cell *** &sudoku){
	bool newValueSet;

	do{
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					if(uniqueRowColInBox(sudoku, i, j)){
						initialRunThrough(sudoku);
						thirdRunThrough(sudoku);
						newValueSet = true;
					}
				}
			}
		}
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);

}

bool uniqueRowColInBox(Cell *** &sudoku, int row, int col){

	int size = sudoku[row][col]->count;
	int id = sudoku[row][col]->ID;
	int boxNum = sudoku[row][col]->box;
	int value;
	int cnt;
	bool rowContains = false,
		colContains = false,
		changed = false;

	for(int x = 0; x < size; x++){
		rowContains = false;
		colContains = false;
		value = sudoku[row][col]->possible[x];

		for(int r = 0; r < 9; r++){
			if(sudoku[r][col]->box != boxNum){
				if(VectorContains(sudoku, r, col, value)){
					colContains = true;
				}
			}
		}

		for(int c = 0; c < 9; c++){
			if(sudoku[row][c]->box != boxNum){
				if(VectorContains(sudoku, row, c, value)){
					rowContains = true;
				}
			}
		}


		if(!rowContains){
			//remove from rest of box
			for(int r = 0; r < 9; r++){
				for(int c = 0; c < 9; c++){
					if(r != row){
						if((sudoku[r][c]->box) == boxNum && (sudoku[r][c]->ID != id)){
							cnt = sudoku[r][c]->count;
							removeImpossibleValue(sudoku, r, c, value);
							if(cnt != sudoku[r][c]->count)
								changed = true;
						}
					}
				}
			}
		}

		if(!colContains){
			//remove from rest of box
			for(int r = 0; r < 9; r++){
				for(int c = 0; c < 9; c++){
					if(c != col){
						if((sudoku[r][c]->box) == boxNum && (sudoku[r][c]->ID != id)){
							cnt = sudoku[r][c]->count;
							removeImpossibleValue(sudoku, r, c, value);
							if(cnt != sudoku[r][c]->count)
								changed = true;
						}

					}
				}
			}
		}
	}
	return changed;
}
