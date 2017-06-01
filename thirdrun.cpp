#include "sudoku.h"

void thirdRunThrough(Cell *** &sudoku){
	bool newValueSet;
	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					twinValuePossible(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
						setCellValue(sudoku, i, j);
						nextRunThrough(sudoku);	
						newValueSet = true;
					}
				}
			}
		}		
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);

}

void twinValuePossible(Cell *** &sudoku, int row, int col){
	int id = sudoku[row][col]->ID;
	int cnt = sudoku[row][col]->count;
	int twinLocation = -1;
	int value1, value2;

	if(cnt == 2){
		value1 = sudoku[row][col]->possible[0];
		value2 = sudoku[row][col]->possible[1];

		//Check columns first
		for(int r = 0; r < 9; r++){
			if(!(sudoku[r][col]->isSet) && (sudoku[r][col]->count == cnt)
				 && (sudoku[r][col]->ID != id)){		
				if(value1 == sudoku[r][col]->possible[0] &&
					value2 == sudoku[r][col]->possible[1]){
						twinLocation = r;
						break;
				}
				
			}
		}
		for(int r = 0; r < 9; r++){
			if(r == twinLocation) continue;

			if(VectorContains(sudoku, r, col, value1)){
				removeImpossibleValue(sudoku, r, col, value1);
			}
			if(VectorContains(sudoku, r, col, value2)){
				removeImpossibleValue(sudoku, r, col, value2);
			}
		}
		twinLocation = -1;
		//Check rows
		for(int c = 0; c < 9; c++){
			if(!(sudoku[row][c]->isSet) && (sudoku[row][c]->count == cnt)
				 && (sudoku[row][c]->ID != id)){		
				if(value1 == sudoku[row][c]->possible[0] &&
					value2 == sudoku[row][c]->possible[1]){
						twinLocation = c;
						break;
				}
				
			}
		}
		for(int c = 0; c < 9; c++){
			if(c == twinLocation) continue;

			if(VectorContains(sudoku, row, c, value1)){
				removeImpossibleValue(sudoku, row, c, value1);
			}
			if(VectorContains(sudoku, row, c, value2)){
				removeImpossibleValue(sudoku, row, c, value2);
			}
		}

		int twinBoxLocation[2] = {-1, -1};
		int boxNum = sudoku[row][col]->box;
		bool innerbreak = false;
		
		for(int r = 0; r < 9; r++){
			if(innerbreak) break;   //There's a better way to do this for sure!!!
			for(int c = 0; c < 9; c++){
				if(!(sudoku[r][c]->isSet) && (sudoku[r][c]->count == cnt)
					 && (sudoku[r][c]->ID != id) && (sudoku[r][c]->box != boxNum)){
					if(value1 == sudoku[r][c]->possible[0] &&
					   value2 == sudoku[r][c]->possible[1]){
						twinBoxLocation[0] = r;
						twinBoxLocation[1] = c;
						innerbreak = true;
						break;
					}
				}
			}
		}

		for(int r = 0; r < 9; r++){
			for(int c = 0; c < 9; c++){
				if(r == twinBoxLocation[0] && c == twinBoxLocation[1]) continue;

				if(sudoku[r][c]->box == boxNum){
					if(VectorContains(sudoku, r, c, value1)){
						removeImpossibleValue(sudoku, r, c, value1);
					}
					if(VectorContains(sudoku, r, c, value2)){
						removeImpossibleValue(sudoku, r, c, value2);
					}
				}
			}
		}

	}

}