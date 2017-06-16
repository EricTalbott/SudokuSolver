#include "sudoku.h"
#include <ctime>

int main()
{
	int ***puzzles;
	int solved = 0;
	puzzles = readFile("unsolvedsudoku.txt");


 	std::clock_t start;
    double duration;

    start = std::clock();

	for(int i = 0; i < 50; i++){

		Cell *** allCells;
		std::cout << "Puzzle #"  << (i+1) <<": ";
		allCells = setUpPuzzle(puzzles[i]);

	//	puzzles[i] = makePrintablePuzzle(allCells);
	//	printPuzzle(puzzles[i]);

		initialRunThrough(allCells);

	//	puzzles[i] = makePrintablePuzzle(allCells);
	//	printPuzzle(puzzles[i]);

		if(puzzleSolved(allCells) != true)
			nextRunThrough(allCells);

		if(puzzleSolved(allCells) != true)
			thirdRunThrough(allCells);

		if(puzzleSolved(allCells) != true)
			fourthRunThrough(allCells);

		if(puzzleSolved(allCells) != true)
			fifthRunThrough(allCells);

		if(puzzleSolved(allCells) != true)
			sixthRunThrough(allCells);

		if(!puzzleSolved(allCells))
			lastResort(allCells);

		if(puzzleSolved(allCells)){
			solved++;
			std::cout << "SOLVED!" << std::endl;
//			puzzles[i] = makePrintablePuzzle(allCells);
//			printPuzzle(puzzles[i]);
		}else{
			std::cout << "***NOT SOLVED!***" << std::endl;
	//		puzzles[i] = makePrintablePuzzle(allCells);
	//		printPuzzle(puzzles[i]);
		//	printPossibilities(allCells);
		}

		clearBox();
		delete allCells;
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time: "<< duration <<'\n';
	 std::cout<< "Solved = " << solved <<std::endl
			 << "Unsolved = " << (50 - solved) << std::endl;
	return 0;
}
