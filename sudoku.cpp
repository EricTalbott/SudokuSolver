#include "sudoku.h"

int main()
{
	int ***puzzles;
	
	puzzles = readFile("unsolvedsudoku.txt");

	for(int i = 0; i < 50; i++){
	//int **puzzle = createPuzzle();
		Cell *** allCells;
		std::cout << "Puzzle #"  << (i+1);
		if(i==5){
			std::cout << std::endl; 
			printPuzzle(puzzles[i]);
		} 
		allCells = setUpPuzzle(puzzles[i]);
		initialRunThrough(allCells);
		//puzzles[5] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[5]);
		//printPossibilities(allCells);
		if(puzzleSolved(allCells) != true)
			nextRunThrough(allCells);
		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);
		if(puzzleSolved(allCells) != true)
			thirdRunThrough(allCells);
		
		if(puzzleSolved(allCells)){
			std::cout << ": SOLVED!" << std::endl;
			//puzzles[i] = makePrintablePuzzle(allCells);
			//printPuzzle(puzzles[i]);
	
		}else{
			std::cout << ": ***NOT SOLVED!***" << std::endl;
			if(i==5){
				puzzles[i] = makePrintablePuzzle(allCells);
				printPuzzle(puzzles[i]);
				printPossibilities(allCells);
			}
		}

		clearBox();
		delete allCells;

	}
	//printPossibilities(allCells);
	return 0;
}