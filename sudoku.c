#include <string.h>
#include "sudoku.h"

int UNSOLVED = 81;

int main(int argc, char **argv){

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
  
  if(argc > 2){
    printf("usage: ./sudoku [optional puzzle]\n");
  } else if(argc == 2 && strlen(argv[1]) != 81){
    printf("usage: ./sudoku [optional puzzle]\npuzzle incomplete\n");
  } else if(argc == 2 && strlen(argv[1]) == 81){
    for(i=0;i<81;i++){
      array[i/9][i%9] = argv[1][i] - '0';
    }
  }

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
