#include "sudoku.h"

void print_puzzle(Square ***puzzle){
  int i,j;

  printf("\n");
  for(i=0;i<SIZE_ROWS;i++){
    for(j=0;j<SIZE_COLS;j++){
      printf("%i ",puzzle[i][j]->number);
      if((j+1)%3 == 0 && j!=(SIZE_COLS-1)){
        printf("| ");
      }
    }
    printf("\n");
    if((i+1)%3 == 0 && i!=(SIZE_ROWS-1)){
      printf("----------------------\n");
    }
  }
  printf("\n");
  
}

Sudoku* setup_puzzle(int puzzle[][SIZE_COLS]){
  Square ***sudoku;
  Box **boxes;
  int i,j,k;
  int curr_box = 0;

  sudoku = (Square***)malloc(sizeof(Square**)*9);
  boxes = create_boxes();

  /* loop through rows */
  for(i=0;i<SIZE_ROWS;i++){
    sudoku[i] = (Square**)malloc(sizeof(Square*)*9);
    /* loop through columns */
    for(j=0;j<SIZE_COLS;j++){

      curr_box = ((i/3)*3) + (j/3); // which box are we in?

      sudoku[i][j] = (Square*)malloc(sizeof(Square)*9);
      sudoku[i][j]->number = puzzle[i][j];
      sudoku[i][j]->row = i;
      sudoku[i][j]->col = j;
      sudoku[i][j]->solvable = 9;

      boxes[curr_box]->squares[boxes[curr_box]->numbers] = sudoku[i][j];
      boxes[curr_box]->numbers++;
      sudoku[i][j]->box = boxes[curr_box];
      
      for(k=0;k<SIZE_ROWS;k++){
        sudoku[i][j]->possible[j] = 0;
      }

    }
  }

  /* loop through rows */
  for(i=0;i<SIZE_ROWS;i++){
    /* loop through columns */
    for(j=0;j<SIZE_ROWS;j++){
      /* if there's a number */
      if(sudoku[i][j]->number != 0){
        sudoku[i][j]->solvable = 0; // no possibilities
        update_sudoku(sudoku,i,j);
        update_boxes(sudoku,i,j);
        UNSOLVED--;
      }
    }
  }

  return create_sudoku(sudoku,boxes);
  
}

void update_sudoku(Square ***sudoku, int row, int col){
  int i,j;
  int number = sudoku[row][col]->number;

  /* update every empty number in same column */
  for(i=0;i<SIZE_ROWS;i++){
    if(sudoku[i][col]->possible[number-1] == 0){
      sudoku[i][col]->solvable--;
    }
    sudoku[i][col]->possible[number-1] = 1;
  }

  for(j=0;j<SIZE_ROWS;j++){
    if(sudoku[row][j]->possible[number-1] == 0){
      sudoku[row][j]->solvable--;
    }
    sudoku[row][j]->possible[number-1] = 1;
  }
}

int check_puzzle(Square ***sudoku,Box **boxes){
  int i,j,k;

  for(i=0;i<SIZE_ROWS;i++){
    for(j=0;j<SIZE_COLS;j++){
      if(sudoku[i][j]->solvable == 1){
        solve_square(sudoku[i][j]);
        update_sudoku(sudoku,i,j);
        update_boxes(sudoku,i,j);

        return 1;
      }
    }
  }

  // run functions until one returns 1 or all return 0
  return box_singles(sudoku,boxes)
  || check_rows(sudoku,boxes)
  || check_cols(sudoku,boxes);

}

Sudoku* create_sudoku(Square ***squares, Box **boxes){
  Sudoku *sudoku = (Sudoku *)malloc(sizeof(Sudoku));

  sudoku->squares = squares;
  sudoku->boxes = boxes;

  return sudoku;
}
