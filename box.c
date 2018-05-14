#include "sudoku.h"

Box** create_boxes(){
  Box **boxes;
  int i,j;

  boxes = (Box**)malloc(sizeof(Box*)*9);

  for(i=0;i<SIZE_ROWS;i++){
    boxes[i] = (Box*)malloc(sizeof(Box));
    boxes[i]->squares = (Square**)malloc(sizeof(Square*)*9);
    boxes[i]->numbers = 0;
    boxes[i]->solvable = 9;
    for(j=0;j<SIZE_COLS;j++){
      boxes[i]->possible[j] = 0;
    }
  }
  
  return boxes;
}

void update_boxes(Square ***sudoku, int row, int col){
  int i,j;

  int number = sudoku[row][col]->number;

  Box *box = sudoku[row][col]->box;

  for(i=0;i<SIZE_ROWS;i++){
    if(box->squares[i]->possible[number-1] == 0){
      box->squares[i]->solvable--;
      box->squares[i]->possible[number-1] = 1;
    }
  }
}

int box_singles(Square ***squares, Box **boxes){
  int i,j,k;
  int count,temp;

  // loop through boxes
  for(i=0;i<SIZE_COLS;i++){
    // loop through possible array values
    for(j=0;j<SIZE_ROWS;j++){
      count = 0;
      // loop through squares
      for(k=0;k<SIZE_COLS;k++){
        // if square has value, cont
        if(boxes[i]->squares[k]->number != 0){
          continue;
        }
        // if current value is a candidate for this square
        if(boxes[i]->squares[k]->possible[j] == 0){
          temp = k;
          count++;
        }
        // no singletons in this box for this value
        if(count >= 2){
          break;
        }
      }
      // only one possible square for this value
      if(count == 1){
        boxes[i]->squares[temp]->number = j+1;
        UNSOLVED--;
        boxes[i]->squares[temp]->solvable = 0;
        update_sudoku(squares,
                      boxes[i]->squares[temp]->row,
                      boxes[i]->squares[temp]->col);
        return 1;
      }
    }
  }
  return 0;
}
