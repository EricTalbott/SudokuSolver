#include "sudoku.h"


void lastResort(Cell *** &sudoku){
	Cell*** temporary = sudoku;  //Temporary is pointing to sudoku's memory location, need to change that.

	for(int r = 0; r < 9; r++){
		for(int c = 0; c < 9; c++){
			if(!(temporary[r][c]->isSet)){
				if(guessAndCheck(temporary, r, c)){
					if(puzzleSolved(temporary)){
						sudoku = temporary;
						return;
					}
				}else
					temporary = sudoku;
			}
		}
	}
}

bool guessAndCheck(Cell *** sudoku, int row, int col){
	Cell*** temporary = sudoku;
	bool solved = false;
	bool unsolvable = false;
	int count = sudoku[row][col]->count;
	int current = 0;

	while(current < count){
		unsolvable = false;
		setCellValueGAC(temporary, row, col, current);
		initialRunThrough(temporary);
		
		if(!puzzleSolved(temporary)){
			nextRunThrough(temporary);
		}
		else return true;

		if(!puzzleSolved(temporary)){
			thirdRunThrough(temporary);
		}	
		else return true;

		for(int r = 0; r < 9; r++){
			for(int c = 0; c < 9; c++){
				if(!(temporary[r][c]->isSet) && temporary[r][c]->count == 0){
					unsolvable = true;
					temporary = sudoku;
					break;
				}
			}
			if(unsolvable) break;
			if(puzzleSolved(temporary)){
				solved = true; 
				break;
			}
		}

		if(solved){
			break;
		}

		current++;
	}

	return solved;

}




