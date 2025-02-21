#include <iostream>
#include<vector>
#include<numeric>

using namespace std;

using matrix = vector<vector<int>>;

void printSudoku(const matrix board){
  cout << "------------------" << endl;
  for (int r = 0; r < 9; ++r){
    for (int c = 0; c < 9; ++c){
      cout << board[r][c] << " ";
    }
    cout << '\n' << endl;
  }
  cout << "------------------" << endl;
}


bool canPlace(const matrix board, int row, int col, int n){
  // check if cell is empty
  if (board[row][col] != -1){return false;}
  // check if number is in row
  for (int i = 0; i < 9; ++i){
    if (n == board[row][i]){return false;}
  }
  //check if number is in column
  for (int i = 0; i < 9; ++i){
    if (n == board[i][col]){return false;}
  }
  // check if in grid
  int gridx = row-(row%3);
  int gridy = col-(col%3);

  for (int r = gridx; r < gridx+3; ++r){
    for (int c = gridy; c < gridy+3; ++c){
      if (n == board[r][c]){return false;}
    }
  }
  return true;
}

vector<int> makeNumberVector(const matrix& board){
  vector<int> numberVec = {};
  for(int i = 0; i < board.size(); ++i){
    int number = 0;
    for(int j = 0; j < 9; ++j){
      number = number * 10 + board[i][j];
    }
    numberVec.push_back(number);
  }
  return numberVec;
}

int findGCD(const vector<int> vec){
  int result = vec[0];
  for(int i = 1; i < int(vec.size()); ++i){
    result = gcd(result, vec[i]);
    if(result == 1){break;}
  }
  return result;
}

vector<int> findPlacables(const matrix board, int row, int col){
  vector<int> placables = {};
  if(row == 0){
    for (int n = 0; n <= 9; ++n){
      if (canPlace(board, row, col, n)){placables.push_back(n);}
    }
  } else{
    vector<int> validNums = {};
    for(int i = 0; i < 9; ++i){
      validNums.push_back(board[0][i]);
      if(canPlace(board, row, col, validNums[i])){placables.push_back(validNums[i]);}
    }
  }
  return placables;
}

void solveSudoku(matrix& board, int row, int col, int& lastGCD, bool newRow){
  if(newRow){
    matrix temp = {};
    for (int i = 0; i < row; ++i){
      temp.push_back(board[i]);
    }
    int gcd = findGCD(makeNumberVector(temp));
    if(gcd <= lastGCD){return;}
  }

  if (row == 9){
    lastGCD = findGCD(makeNumberVector(board));
    printSudoku(board);
    cout << lastGCD << endl;
    return;
  }

  else if(col == 9){solveSudoku(board, row+1, 0, lastGCD, true);}
  else if(board[row][col] != -1){solveSudoku(board, row, col+1, lastGCD, false);}

  vector<int> placables = findPlacables(board, row, col);
  if(placables.size()==0){return;}

  for (int i = 0; i < int(placables.size()); ++i){
    int n = placables[i];
    board[row][col] = n;
    solveSudoku(board, row, col+1, lastGCD, false);
    board[row][col] = -1;
  }
  return;
}

//MAIN FUNCTION
int main(){
  matrix board  = {
    {-1, -1, -1, -1, -1, -1, -1, 2, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, 5},
    {-1, 2, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, 0, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 0, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 2, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, 5, -1, -1}
  };

  int gcd = 1;

  solveSudoku(board, 0, 0, gcd, false);

  return 0;
}
