OBJS = sudoku.o puzzle.o firstrun.o secondrun.o thirdrun.o printers.o fourthrun.o fifthrun.o sixthrun.o lastresort.o
CC = g++
CFLAGS = -Wall -c

sudoku: $(OBJS)
	$(CC) $(OBJS) -o sudoku

sudoku.o: sudoku.cpp sudoku.h
	$(CC) $(CFLAGS) sudoku.cpp

puzzle.o: puzzle.cpp sudoku.h
	$(CC) $(CFLAGS) puzzle.cpp

firstrun.o: firstrun.cpp sudoku.h
	$(CC) $(CFLAGS) firstrun.cpp

secondrun.o: secondrun.cpp sudoku.h
	$(CC) $(CFLAGS) secondrun.cpp

thirdrun.o: thirdrun.cpp sudoku.h
	$(CC) $(CFLAGS) thirdrun.cpp

fourthrun.o: fourthrun.cpp sudoku.h
	$(CC) $(CFLAGS) fourthrun.cpp

fifthrun.o: fifthrun.cpp sudoku.h
	$(CC) $(CFLAGS) fifthrun.cpp

sixthrun.o: sixthrun.cpp sudoku.h
	$(CC) $(CFLAGS) sixthrun.cpp

lastresort.o: lastresort.cpp sudoku.h
	$(CC) $(CFLAGS) lastresort.cpp

printers.o: printers.cpp sudoku.h
	$(CC) $(CFLAGS) printers.cpp

clean:
	\rm *.o sudoku