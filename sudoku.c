#include "sudoku.h"

int UNSOLVED = 81;

int main(){

  int array[9][9] = {{0,1,9,	0,0,2,	0,0,0},
                     {4,7,0,	6,9,0,	0,0,1},
                     {0,0,0,	4,0,0,	0,9,0},
                     
                     {8,9,4,	5,0,7,	0,0,0},
                     {0,0,0,	0,0,0,	0,0,0},
                     {0,0,0,	2,0,1,	9,5,8},
                     
                     {0,5,0,	0,0,6,	0,0,0},
                     {6,0,0,	0,2,8,	0,7,9},
                     {0,0,0,	1,0,0,	8,6,0}
  };
  Sudoku *sudoku;
  int i;
  int progress;

  sudoku = setup_puzzle(array);
  print_puzzle(sudoku->squares);

  while(UNSOLVED > 0){
    progress = check_puzzle(sudoku->squares,sudoku->boxes);

    if(progress == 0){
      printf("failed to solve puzzle \n");
      break;
    }
  }

  print_puzzle(sudoku->squares);
  
  return 0;
}
