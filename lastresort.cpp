#include "sudoku.h"


void lastResort(Cell *** &sudoku){
	Cell*** temporary;
	temporary = createTemporary(sudoku);
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

bool guessAndCheck(Cell *** &sudoku, int row, int col){
	Cell*** temporary;
	temporary = createTemporary(sudoku);
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
		else solved = true;

		if(!puzzleSolved(temporary)){
			thirdRunThrough(temporary);
		}
		else solved = true;;

		if(!solved){
			for(int r = 0; r < 9; r++){
				for(int c = 0; c < 9; c++){
					if(!(temporary[r][c]->isSet) && temporary[r][c]->count == 0){
						unsolvable = true;
						break;
					}
				}
				if(unsolvable) break;
				if(puzzleSolved(temporary)){
					solved = true;
					break;
				}
			}
		}

		if(solved){
			sudoku = temporary;

			break;
		}

		current++;
	}

	return solved;

}




Cell *** createTemporary(Cell *** sudoku){
	Cell*** temporary;

	temporary = (Cell***)malloc(sizeof(Cell**)*9);
	for(int i = 0; i < 9; i++){
		temporary[i] = (Cell**)malloc(sizeof(Cell*)*9);
		for(int j = 0; j < 9; j++){
			temporary[i][j] = (Cell*)malloc(sizeof(Cell));

			temporary[i][j]->number = sudoku[i][j]->number;
			temporary[i][j]->isSet = sudoku[i][j]->isSet;
			temporary[i][j]->ID = sudoku[i][j]->ID;
			temporary[i][j]->box = sudoku[i][j]->box;
			temporary[i][j]->count = sudoku[i][j]->count;
			temporary[i][j]->possible = new int[temporary[i][j]->count];
			for(int x = 0; x < temporary[i][j]->count; x++){
				temporary[i][j]->possible[x] = sudoku[i][j]->possible[x];
			}
		}
	}
	return temporary;
}
