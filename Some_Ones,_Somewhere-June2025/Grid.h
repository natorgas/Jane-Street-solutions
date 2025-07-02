#ifndef GRID_H
#define GRID_H

struct Node{
  bool covered;
  std::string color;
  Node();
};

struct Grid{

  Node grid[45][45];
  int grid_number;
  std::map<std::string, int> side_length;
  std::map<int, std::string> color;
  std::map<int, int> n_available_tiles;   // sidelength of tile |-> how many more tiles can be used on this grid


  Grid();

  Grid(int grid_num);

  // (row, col) coordinates of the upper left corner of the tile
  // return true if tile was placed successfully, else false
  bool place_tile(int size, int row, int col);

  // (row, col) coordinates of the upper left corner of the tile
  // remove the given tile and increase available tiles
  void remove_tile(int size, int row, int col);

  // print the grid with correct colors
  void print_grid();

  // returns true if the cell is covered, else false
  bool cell_covered(int row, int col);

  void print_pink_coordinates();

  void place_initial_tiles_1();

  void place_initial_tiles_2();

  void place_initial_tiles_3();

  void place_initial_tiles_4();

  void place_initial_tiles_5();

  void place_initial_tiles_6();

  void place_initial_tiles_7();

  void place_initial_tiles_8();

  void place_initial_tiles_9();
};

#endif
