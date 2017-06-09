#include "sudoku.h"


boxMap box;

#define PUZZLES 50

//Initialization
/*
int ** createPuzzle(){
	int **puzzle;
	int array[9][9] = {
		{0, 0, 0, 5, 0, 0, 6, 0, 9},
		{9, 5, 0, 7, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 0, 8},
		{7, 0, 3, 6, 0, 4, 0, 0, 0},
		{0, 2, 0, 0, 0, 0, 0, 8, 0},
		{0, 0, 0, 3, 0, 9, 4, 0, 7},
		{8, 0, 0, 2, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 5, 4},
		{3, 0, 2, 0, 0, 7, 0, 0, 0}
	};

	puzzle = (int**)malloc(sizeof(int*)*9);
	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*)malloc(sizeof(int)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = array[i][j];
		}
	}
	return puzzle;
}*/

Cell *** setUpPuzzle(int ** puzzle){
	Cell *** sudoku;
	int id = 0;
	sudoku = (Cell***)malloc(sizeof(Cell**)*9);
	for(int i = 0; i < 9; i++){
		sudoku[i] = (Cell**)malloc(sizeof(Cell*)*9);
		for(int j = 0; j < 9; j++){
			sudoku[i][j] = (Cell*)malloc(sizeof(Cell));

			sudoku[i][j]->number = puzzle[i][j];
			
			sudoku[i][j]->ID = id;
			sudoku[i][j]->possible = new int[9];
			id++;
			sudoku[i][j]->box = addToBox(puzzle[i][j], i, j);
				
			if(sudoku[i][j]->number != 0){
				sudoku[i][j]->count = 0;
				sudoku[i][j]->isSet = true;

			}else{
				sudoku[i][j]->isSet = false;
				sudoku[i][j]->count = 9;
				for(int x = 0; x < 9; x++){
					sudoku[i][j]->possible[x] = (x + 1);
				}
			}
		}
	}
	return sudoku;
}

int *** readFile (std::string fileName){
	//int puzzleNum;
	int array[PUZZLES][9][9];
	char ch;
	std::string gridString;
	std::ifstream infile(fileName);

	if (!infile) {
		std::cout << "There was a problem opening file "
		 	<< fileName
		 	<< " for reading."
		 	<< std::endl; 
		 	return 0;
	}

	for(int i = 0; i < PUZZLES; i++){
		getline(infile, gridString);
		for(int j = 0; j < 9; j++){
			for(int k = 0; k < 9; k++){
				infile >> ch;
				array[i][j][k] = ch - '0';
			}
		}
		getline(infile, gridString);
	}

	infile.close(); 

	int *** puzzle;
	puzzle = (int***)malloc(sizeof(int**)*50);
	for(int i = 0; i < PUZZLES; i++){
		puzzle[i] = (int**)malloc(sizeof(int*)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = (int*)malloc(sizeof(int)*9);
			for(int k = 0; k < 9; k++)
				puzzle[i][j][k] = array[i][j][k];
		}
	}
	return puzzle;
}

//Mutators
void removeImpossibleValue(Cell *** &sudoku, int row, int col, int value){
	int cnt = sudoku[row][col]->count;
	
	for(int i = 0; i < cnt; i++){
		if(sudoku[row][col]->possible[i] == value){
			for(int j = i; j < cnt; j++){
				sudoku[row][col]->possible[j] = sudoku[row][col]->possible[j+1];
			}
			--cnt;
		}
	}
	sudoku[row][col]->count = cnt;
}

void clearBox(){
	box.clear();
}

//Setters
void setPossibleValue(int value, int* &poss, int &count){
	poss[0] = value;
	count = 1;
}

void setCellValue(Cell *** &sudoku, int row, int col){
	sudoku[row][col]->number = sudoku[row][col]->possible[0];
	sudoku[row][col]->box = addToBox(sudoku[row][col]->number, row, col);
	sudoku[row][col]->isSet = true;
}

int addToBox(int number, int i, int j){
	if(i < 3){
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(0,number));
			return 0;
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(1,number));
			return 1;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(2,number));
			return 2;
		}
	}else if(i < 6){
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(3,number));
			return 3;	
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(4,number));
			return 4;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(5,number));
			return 5;
		}
	}else{
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(6,number));
			return 6;
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(7,number));
			return 7;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(8,number));
			return 8;
		}
	}	
}

//Bool Operations (Checkers)
bool puzzleSolved(Cell *** sudoku){
	int solved = 0;
	for(int r = 0; r < 9; r++){
		for (int c = 0; c < 9; c++){
			if(sudoku[r][c]->isSet){
				solved++;
			}

		}
	}
	if(solved == 81) return true;
	
	return false;
}

//Return True if a given value is contained in a given "box". Returns false if not.
bool visibleVectorContains(Cell *** sudoku, int boxNum, int value, int id, int row, int column){
	bool rowContains = false,
		colContains = false,
		boxContains = false;

	for(int rw = 0; rw < 9; rw++){
		for (int col = 0; col < 9; col++){
			if((!(sudoku[rw][col]->isSet)) && (sudoku[rw][col]->ID != id)){	
				if(rw == row){		
					if(VectorContains(sudoku, rw, col, value)) rowContains = true;
				}		
				
				if(col == column){
					if(VectorContains(sudoku, rw, col, value)) colContains = true;
		  		}

		  		if(sudoku[rw][col]->box == boxNum ){
		  			if(VectorContains(sudoku, rw, col, value)) boxContains = true;
		  		}
			}
		}
	}
	return (rowContains && colContains && boxContains);
}

bool VectorContains(Cell *** sudoku, int rw, int col, int value){
	bool contains = false;
	for (int i = 0 ; i < sudoku[rw][col]->count; i++){
		if(value == sudoku[rw][col]->possible[i]){ 
		    contains = true;
		}
	}
	return contains;
}

bool boxContains(int boxNumber, int value){
	mapIter it;

	std::pair<mapIter, mapIter> keyRange = box.equal_range(boxNumber);
	for(it = keyRange.first; it != keyRange.second; it++){
		if(value == (*it).second) return true;
	}
	return false;
}

//Return True if a given value is contained in a given row. Returns false if not.
bool rowContains(Cell *** sudoku, int value, int row){

	int checkVal;
	for(int c = 0; c < 9; c++){
		if(sudoku[row][c]->isSet){
			checkVal = sudoku[row][c]->number;
			if(checkVal == value) return true;
		}
	}
	return false;	
}

//Return True if a given value is contained in a given column. Returns false if not.
bool columnContains(Cell *** sudoku, int value, int column){

	int checkVal;
	for(int r = 0; r < 9; r++){
		if(sudoku[r][column]->isSet){
			checkVal = sudoku[r][column]->number;
			if(checkVal == value) return true;
		}
	}
	return false;	
}