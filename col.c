#include "sudoku.h"

int check_cols(Square ***squares, Box **boxes){

  int i,j,k;
  int sum[SIZE_COLS];
  int place[SIZE_COLS];

  // loop through all cols
  for(i=0;i<SIZE_COLS;i++){
    // initialize sum to 0 for this row
    for(j=0;j<SIZE_COLS;j++){
      sum[j] = 0;
      place[j] = 0;
    }
    // loop through all rows
    for(j=0;j<SIZE_ROWS;j++){
      // skip existing numbers
      if(squares[j][i]->number != 0){
        continue;
      }
      // loop through values
      for(k=0;k<SIZE_COLS;k++){
        if(squares[j][i]->possible[k] == 0){
          place[k] = j;
          sum[k]++;
        }
      }
    }
    // loop through possible values again
    for(j=0;j<SIZE_COLS;j++){
      if(sum[j] == 1){
        squares[place[j]][i]->number = j+1;
        squares[place[j]][i]->solvable = 0;
        UNSOLVED--;

        update_sudoku(squares,place[j],i);
        update_boxes(squares,place[j],i);
        return 1;
      }
    }
  }

  return 0;
}
