#include "sudoku.h"
#include <ctime>

int main()
{
	int ***puzzles;
	
	puzzles = readFile("unsolvedsudoku.txt");


 	std::clock_t start;
    double duration;

    start = std::clock();

	for(int i = 0; i < 50; i++){
	//int **puzzle = createPuzzle();
		Cell *** allCells;
		std::cout << "Puzzle #"  << (i+1) <<": ";
		allCells = setUpPuzzle(puzzles[i]);

	//	puzzles[i] = makePrintablePuzzle(allCells);
	//	printPuzzle(puzzles[i]);


		initialRunThrough(allCells);

		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);

		if(puzzleSolved(allCells) != true)	
			nextRunThrough(allCells);

		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);
		
		if(puzzleSolved(allCells) != true)
			thirdRunThrough(allCells);

		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);
		
		if(puzzleSolved(allCells) != true)
			fourthRunThrough(allCells);

		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);

		if(puzzleSolved(allCells) != true)
			fifthRunThrough(allCells);

		//puzzles[i] = makePrintablePuzzle(allCells);
		//printPuzzle(puzzles[i]);
		//printPossibilities(allCells);

		if(puzzleSolved(allCells) != true)
			sixthRunThrough(allCells);


		if(puzzleSolved(allCells)){
			std::cout << "SOLVED!" << std::endl;
			//puzzles[i] = makePrintablePuzzle(allCells);
			//printPuzzle(puzzles[i]);
	
		}else{
			std::cout << "***NOT SOLVED!***" << std::endl;
			puzzles[i] = makePrintablePuzzle(allCells);
			printPuzzle(puzzles[i]);
		//	printPossibilities(allCells);
		}

		clearBox();
		delete allCells;

	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';
	
	//printPossibilities(allCells);
	return 0;
}