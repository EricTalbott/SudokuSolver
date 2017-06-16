#include "sudoku.h"
#include <ctime>

#define PUZZLES 50

int main()
{
	int ***puzzles;
	int solved = 0;
	puzzles = readFile("unsolvedsudoku.txt");


 	std::clock_t start;
    double duration;

    start = std::clock();

	for(int i = 0; i < PUZZLES; i++){

		Cell *** allCells;
		allCells = setUpPuzzle(puzzles[i]);

		initialRunThrough(allCells);

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
		}else{
			std::cout << "#"  << (i+1) <<", ";
			std::cout << "***NOT SOLVED!***" << std::endl;
		}

		clearBox();
		delete allCells;
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time: "<< duration <<'\n';
	 std::cout<< "Solved = " << solved <<std::endl
			 << "Unsolved = " << (PUZZLES - solved) << std::endl;
	return 0;
}
