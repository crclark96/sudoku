#include "sudoku.h"

int check_rows(Square ***squares, Box **boxes){

  int i,j,k;
  int sum[SIZE_ROWS];
  int place[SIZE_ROWS];

  // loop through all rows
  for(i=0;i<SIZE_ROWS;i++){
    // initialize sum to 0 for this row
    for(j=0;j<SIZE_ROWS;j++){
      sum[j] = 0;
      place[j] = 0;
    }
    // loop through all cols
    for(j=0;j<SIZE_COLS;j++){
      // skip existing numbers
      if(squares[i][j]->number != 0){
        continue;
      }
      // loop through values
      for(k=0;k<SIZE_COLS;k++){
        if(squares[i][j]->possible[k] == 0){
          place[k] = j;
          sum[k]++;
        }
      }
    }
    // loop through possible values again
    for(j=0;j<SIZE_ROWS;j++){
      if(sum[j] == 1){
        squares[i][place[j]]->number = j+1;
        squares[i][place[j]]->solvable = 0;
        UNSOLVED--;

        update_sudoku(squares,i,place[j]);
        update_boxes(squares,i,place[j]);
        return 1;
      }
    }
  }


  return 0;
}
