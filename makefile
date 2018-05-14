CC = gcc
CFLAGS = -g -O2
OBJS = sudoku.o puzzle.o square.o box.o row.o

all: sudoku run clean

sudoku: $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

run:
	./sudoku

clean:
	rm sudoku $(OBJS)
