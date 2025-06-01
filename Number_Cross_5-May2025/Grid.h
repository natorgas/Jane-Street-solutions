#ifndef GRID_H
#define GRID_H

struct Node {
  int val;
  int area;
  bool is_constant;
  bool tile;
  Node() : val(0), area(0) {}            
  Node(int v, int a) : val(v), area(a) {
    is_constant = false;
    tile = false;
  } 
};

struct Grid{

  Node grid[11][11];

  std::vector<std::pair<int, int>> directions;
  
  std::map<int, std::pair<int, int>> access_area; // area |-> (i, j) s.t. grid(i,j) is in area

  std::unordered_set<long long> seen_in_grid;

  // Hard coding areas, constant cells etc
  Grid(){
    seen_in_grid = {};

    access_area[1] = {0, 0};
    access_area[2] = {2, 0};
    access_area[3] = {2, 2};
    access_area[4] = {2, 6};
    access_area[5] = {3, 5};
    access_area[6] = {9, 0};
    access_area[7] = {7, 9};
    access_area[8] = {7, 2};
    access_area[9] = {10, 2};

    directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for(int i = 0; i < 11; ++i){
      grid[0][i] = Node(0, 1);
    }
    grid[1][0] = Node(0, 1);
    grid[1][1] = Node(0, 2);
    for(int i = 2; i < 11; ++i){
      grid[1][i] = Node(0, 1);
    }
    grid[2][0] = Node(0, 2);
    grid[2][1] = Node(0, 2);
    for(int i = 2; i <= 5; ++i){
      grid[2][i] = Node(0, 3);
    }
    for(int i = 6; i <= 8; ++i){
      grid[2][i] = Node(0, 4);
    }
    grid[2][9] = Node(0, 1);
    grid[2][10] = Node(0, 4);
    //ROW=3
    grid[3][0] = Node(0, 2);
    grid[3][1] = Node(0, 3);
    grid[3][2] = Node(0, 3);
    grid[3][3] = Node(0, 2);
    grid[3][4] = Node(0, 3);
    grid[3][5] = Node(0, 5);
    for(int i = 6; i < 11; ++i){
      grid[3][i] = Node(0, 4);
    }
    //ROW=4
    grid[4][0] = Node(0, 2);
    grid[4][1] = Node(0, 3);
    grid[4][2] = Node(0, 3);
    grid[4][3] = Node(0, 2);
    grid[4][4] = Node(0, 3);
    grid[4][5] = Node(0, 5);
    grid[4][6] = Node(0, 5);
    grid[4][7] = Node(0, 4);
    grid[4][8] = Node(0, 4);
    grid[4][9] = Node(0, 5);
    grid[4][10] = Node(0, 4);
    //ROW=5
    for(int i = 0; i < 11; i++){
      if(i<=4) grid[5][i] = Node(0, 2);
      else if(i <= 9) grid[5][i] = Node(0, 5);
      else grid[5][i] = Node(0, 4);
    }
    //ROW=6
    grid[6][0] = Node(0, 2);
    grid[6][1] = Node(0, 6);
    grid[6][2] = Node(0, 8);
    grid[6][3] = Node(0, 8);
    grid[6][4] = Node(0, 2);
    grid[6][5] = Node(0, 2);
    grid[6][6] = Node(0, 5);
    grid[6][7] = Node(0, 5);
    grid[6][8] = Node(0, 8);
    grid[6][9] = Node(0, 5);
    grid[6][10] = Node(0, 5);
    //ROW=7
    grid[7][0] = Node(0, 2);
    grid[7][1] = Node(0, 6);
    for(int i = 2; i <= 8; ++i){
      grid[7][i] = Node(0, 8);
    }
    grid[7][9] = Node(0, 7);
    grid[7][10] = Node(0, 7);
    //ROW=8
    for(int i = 0; i <= 3; ++i){
      grid[8][i] = Node(0, 6);
    }
    grid[8][4] = Node(0, 8);
    grid[8][5] = Node(0, 6);
    grid[8][6] = Node(0, 8);
    for(int i = 7; i < 11; i++){
      grid[8][i] = Node(0, 7);
    }
    //ROW=9
    for(int i = 0; i < 11; ++i){
      grid[9][i] = Node(0, 6);
    }
    //ROW=10
    grid[10][0] = Node(0, 6);
    grid[10][1] = Node(0, 6);
    for(int i = 2; i <= 7; ++i){
      grid[10][i] = Node(0, 9);
    }
    for(int i = 8; i < 11; ++i){
      grid[10][i] = Node(0, 6);
    }
    // Set constants
    grid[1][3].is_constant = true;
    grid[1][4].is_constant = true;
    grid[2][4].is_constant = true;
    grid[2][9].is_constant = true;
    grid[3][8].is_constant = true;
    grid[3][9].is_constant = true;
    grid[5][5].is_constant = true;
    grid[6][1].is_constant = true;
    grid[6][2].is_constant = true;
    grid[6][5].is_constant = true;
    grid[6][6].is_constant = true;
    grid[7][1].is_constant = true;
    grid[7][5].is_constant = true;
    grid[8][4].is_constant = true;
    grid[8][5].is_constant = true;
    grid[9][4].is_constant = true;
  }

  void printGrid();

  void updateAreaValues(int val, int area);

  void setValueArea(int row, int col, int val);

  void setValue(int row, int col, int val);

  std::vector<long long> numberInRow(int row);

  bool row0Valid();

  bool row1Valid();

  bool row2Valid();
  
  bool row3Valid();

  bool row4Valid();

  bool row5Valid();

  bool row6Valid();

  bool row7Valid();

  bool row8Valid();

  bool row9Valid();

  bool row10Valid();

  bool tilePlacable(int row, int col);

  bool bordersOk(int row, int col);

  bool areaEmpty(int area);

  bool gridCompleted();
  
  bool rowValid(int n);

  void placeTile(int row, int col);

  void removeTile(int row, int col);

  std::vector<long long> numberInRowFromIndex(int row, int right);
};

#endif
