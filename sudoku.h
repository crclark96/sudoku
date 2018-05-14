#ifndef _SUDOKU_H
#define _SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE_ROWS 9
#define SIZE_COLS 9


extern int UNSOLVED;


typedef struct Box{
  struct Square ** squares;
  int numbers;
  int possible[9];
  int solvable;
  struct Box *next;

} Box;

typedef struct Square{
  int number;
  int possible[9];
  int solvable;
  Box *box;
  int row;
  int col;
} Square;

typedef struct Sudoku{
  struct Square ***squares;
  struct Box **boxes;
} Sudoku;


void print_puzzle(Square ***puzzle);
Sudoku* setup_puzzle(int puzzle[][SIZE_COLS]);
void update_sudoku(Square ***sudoku, int row, int col);
void update_boxes(Square ***sudoku, int row, int col);
void solve_square(Square *square);
int check_puzzle(Square ***sudoku, Box **boxes);
Box** create_boxes();
Sudoku* create_sudoku(Square ***puzzle, Box **boxes);
int box_singles(Square ***squares,Box **boxes);
int check_rows(Square ***squares,Box **boxes);
int check_cols(Square ***squares,Box **boxes);

#endif
