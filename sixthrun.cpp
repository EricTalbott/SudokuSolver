//If a set of three numbers (and only three numbers) exists in exactly
//three locations on any row, column or box, then those three numbers cannot
//exist in any other location within that row, column or box.

#include "sudoku.h"

void sixthRunThrough(Cell *** &sudoku){
	bool newValueSet;
	do{
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					if(tripleValuePossible(sudoku, i, j)){
						nextRunThrough(sudoku);
						newValueSet = true;
					}
				}
			}
		}
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);
}

bool tripleValuePossible(Cell *** &sudoku, int row, int col){

	int currID = sudoku[row][col]->ID;
	int cnt = sudoku[row][col]->count;
	int boxNum = sudoku[row][col]->box;
	int* values;
	bool notTwin = false;
	bool changes = false;

	//int cantidates[3] = {0};
	int locations[2] = {0};
	int twins = 0;
	//int numberTwinsFound = 0;
	//int numbersFound = 0;


	if(cnt == 3){
		values = new int[cnt];

		for(int i = 0; i < cnt; i++)
			values[i] = sudoku[row][col]->possible[i];

		//Check Column
		for(int r = 0; r < 9; r++){
			if(!(sudoku[r][col]->isSet) && r != row){

				//Other Cell has 3 possible
				if(sudoku[r][col]->count == 3){
					for(int i = 0; i < cnt; i++){
						if(values[i] != sudoku[r][col]->possible[i]){
							notTwin = true;
							break;
						}
					}
					if(!notTwin){
						locations[twins] = r;
						twins++;
					}
				}
				else if(sudoku[r][col]->count == 2){
					int loc = 0;
					for(int i = 0; i < 3; i++){
						if(values[i] == sudoku[r][col]->possible[loc]){
							loc++;
						}
						if(loc == 2){
							locations[twins] = r;
							twins++;
							break;
						}
					}
				}
			}
			if(twins == 2) break;
		}
		if(twins == 2){
			for(int r = 0; r < 9; r++){
				if(!(sudoku[r][col]->isSet) && r != row && r != locations[0] && r != locations[1]){
					for(int i = 0; i < 3; i++){
						int current = sudoku[r][col]->count;
						removeImpossibleValue(sudoku, r, col, values[i]);
						if(current != sudoku[r][col]->count){
							changes = true;
						}
					}
				}
			}
		}

		twins = 0;

		//Check Row
		for(int c = 0; c < 9; c++){
			if(!(sudoku[row][c]->isSet) && c != col){

				//Other Cell has 3 possible
				if(sudoku[row][c]->count == 3){
					for(int i = 0; i < cnt; i++){
						if(values[i] != sudoku[row][c]->possible[i]){
							notTwin = true;
							break;
						}
					}
					if(!notTwin){
						locations[twins] = c;
						twins++;
					}
				}
				else if(sudoku[row][c]->count == 2){
					int loc = 0;
					for(int i = 0; i < 3; i++){
						if(values[i] == sudoku[row][c]->possible[loc]){
							loc++;
						}
						if(loc == 2){
							locations[twins] = c;
							twins++;
							break;
						}
					}
				}
			}
			if(twins == 2) break;
		}
		if(twins == 2){
			for(int c = 0; c < 9; c++){
				if(!(sudoku[row][c]->isSet) && c != col && c != locations[0] && c != locations[1]){
					for(int i = 0; i < 3; i++){
						int current = sudoku[row][c]->count;
						removeImpossibleValue(sudoku, row, c, values[i]);
						if(current != sudoku[row][c]->count){
							changes = true;
						}
					}
				}
			}
		}

		twins = 0;

		//Check Boxes
		for(int r = 0; r < 9; r++){
			for(int c = 0; c < 9; c++){
				if(!(sudoku[r][c]->isSet) && c != col && r != row && sudoku[r][c]->box == boxNum){

					//Other Cell has 3 possible
					if(sudoku[r][c]->count == 3){
						for(int i = 0; i < cnt; i++){
							if(values[i] != sudoku[r][c]->possible[i]){
								notTwin = true;
								break;
							}
						}
						if(!notTwin){
							locations[twins] = sudoku[r][c]->ID;
							twins++;
						}
					}
					else if(sudoku[r][c]->count == 2){
						int loc = 0;
						for(int i = 0; i < 3; i++){
							if(values[i] == sudoku[r][c]->possible[loc]){
								loc++;
							}
							if(loc == 2){
								locations[twins] = sudoku[r][c]->ID;
								twins++;
								break;
							}
						}
					}
				}
				if(twins == 2) break;
			}
			if(twins == 2) break;
		}

		int id;
		if(twins == 2){
			for(int r = 0; r < 9; r++){
				for(int c = 0; c < 9; c++){
					id = sudoku[r][c]->ID;
					if(!(sudoku[r][c]->isSet) && id != currID && id != locations[0] && id != locations[1]){
						for(int i = 0; i < 3; i++){
							int current = sudoku[r][c]->count;
							removeImpossibleValue(sudoku, r, c, values[i]);
							if(current != sudoku[r][c]->count){
								std::cout<< r << c <<std::endl;
								changes = true;
							}
						}
					}
				}
			}
		}

	}

	return changes;

}
