#include "sudoku.h"

void printPuzzle(int** puzzle){
	printf("------------------------------\n" );
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(puzzle[i][j] != 0)
				printf(" %d ", puzzle[i][j]);
			else
				printf(" _ ");
			if((j+1)%3 == 0)
				printf("|");
		}
		printf("\n");
		if((i+1) % 3 == 0)
			printf("------------------------------\n");
	}
	printf("\n");
}

int** makePrintablePuzzle(Cell *** sudoku){
	int ** puzzle = (int**)malloc(sizeof(int*)*9);
	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*)malloc(sizeof(int)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = sudoku[i][j]->number;
		}
	}
	return puzzle;
}

void printPossibilities(Cell *** sudoku){
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			std::cout <<"Row " << i <<", Col " << j  << ", Box " << sudoku[i][j]->box << ": ";
  			for (int k = 0; k < sudoku[i][j]->count; k++)
    		std::cout << ' ' << sudoku[i][j]->possible[k];
  		std::cout << '\n';
		}
}
