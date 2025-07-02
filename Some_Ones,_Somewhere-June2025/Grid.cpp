#include <map>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include "Grid.h"

Node::Node(){
  covered = false; 
  color = "";
}

Grid::Grid(){
  grid_number = 1; // Default is grid 1

  side_length = { 
    {"pink", 1},
    {"green", 2},
    {"orange", 3},
    {"dark-blue", 4},
    {"red", 5},
    {"light-blue", 6},
    {"yellow", 7},
    {"brown", 8},
    {"transparent", 9}
  };

  color = { 
    {1, "pink"},
    {2, "green"},
    {3, "orange"},
    {4, "dark-blue"},
    {5, "red"},
    {6, "light-blue"},
    {7, "yellow"},
    {8, "brown"},
    {9, "transparent"}
  };

  n_available_tiles = {
    {1, 1},
    {2, 2},
    {3, 3},
    {4, 4},
    {5, 5},
    {6, 6},
    {7, 7},
    {8, 8},
    {9, 9}
  };  

}

Grid::Grid(int grid_n){
  grid_number = grid_n;

  side_length = { 
    {"pink", 1},
    {"green", 2},
    {"orange", 3},
    {"dark-blue", 4},
    {"red", 5},
    {"light-blue", 6},
    {"yellow", 7},
    {"brown", 8},
    {"transparent", 9}
  };

  color = { 
    {1, "pink"},
    {2, "green"},
    {3, "orange"},
    {4, "dark-blue"},
    {5, "red"},
    {6, "light-blue"},
    {7, "yellow"},
    {8, "brown"},
    {9, "transparent"}
  };

  n_available_tiles = {
    {1, 1},
    {2, 2},
    {3, 3},
    {4, 4},
    {5, 5},
    {6, 6},
    {7, 7},
    {8, 8},
    {9, 9}
  };  

  // set inital tiles corresponding to correct grid
  
  if(grid_n == 1) place_initial_tiles_1();
  if(grid_n == 2) place_initial_tiles_2();
  if(grid_n == 3) place_initial_tiles_3();
  if(grid_n == 4) place_initial_tiles_4();
  if(grid_n == 5) place_initial_tiles_5();
  if(grid_n == 6) place_initial_tiles_6();
  if(grid_n == 7) place_initial_tiles_7();
  if(grid_n == 8) place_initial_tiles_8();
  if(grid_n == 9) place_initial_tiles_9();
}

void Grid::print_grid(){
  for(int i = 0; i < 45; ++i){
    std::cout << i/10 << " ";
  }
  std::cout << "\n";
  for(int i = 0; i < 45; ++i){
    std::cout << i%10 << " ";
  }
  std::cout << "\n";
  for(int row = 0; row < 45; ++row){
    for(int col = 0; col < 45; ++col){
      std::string color = grid[row][col].color;

      if(!grid[row][col].covered){
        std::cout << "\033[38;2;158;158;158mX \033[0m";
      }
      // else print in corresponding color

      else if(color == "pink"){
        std::cout << "\033[38;2;171;71;188mX \033[0m";
        //std::cout << "\033[38;2;200;0;0mX \033[0m";
      }
      else if(color == "green"){
        std::cout << "\033[38;2;124;179;66mX \033[0m";
      }
      else if(color == "orange"){
        std::cout << "\033[38;2;255;143;0mX \033[0m";
      }
      else if(color == "dark-blue"){
        std::cout << "\033[38;2;57;73;171mX \033[0m";
      }
      else if(color == "red"){
        std::cout << "\033[38;2;191;54;12mX \033[0m";
      }
      else if(color == "light-blue"){
        std::cout << "\033[38;2;3;155;229mX \033[0m";
      }
      else if(color == "yellow"){
        std::cout << "\033[38;2;255;235;59mX \033[0m";
      }
      else if(color == "brown"){
        std::cout << "\033[38;2;109;76;65mX \033[0m";
      }
      else if(color == "transparent"){
        std::cout << "\033[38;2;178;235;242mX \033[0m";
      }
    }
    std::cout << " " << row << "\n";
  }
  std::cout << "\n";
}

bool Grid::place_tile(int size, int row, int col){
  assert(n_available_tiles[size] > 0);
  if(row + size > 45 || col + size > 45) return false;
  for(int r = row; r < row + size; ++r){
    for(int c = col; c < col + size; ++c){
      if(grid[r][c].covered) return false;
    }
  }
  // No covered cells -> tile can be placed
  for(int r = row; r < row + size; ++r){
    for(int c = col; c < col + size; ++c){
      grid[r][c].covered = true;
      grid[r][c].color = color[size];
    }
  }
  n_available_tiles[size]--;
  return true;
}

void Grid::remove_tile(int size, int row, int col){
  assert(n_available_tiles[size] < size);
  if(row + size > 45 || col + size > 45) assert(false);
  for(int r = row; r < row + size; ++r){
    for(int c = col; c < col + size; ++c){
      if(grid[r][c].color != color[size]){
        std::cout << "Tried to remove but this is not a color \n";
        assert(false);
      }
    }
  }
  for(int r = row; r < row + size; ++r){
    for(int c = col; c < col + size; ++c){
      grid[r][c].covered = false;
      grid[r][c].color = "";
    }
  }
  n_available_tiles[size]++;
}

bool Grid::cell_covered(int row, int col){
  return grid[row][col].covered;
}

void Grid::print_pink_coordinates(){
  for(int i = 0; i < 45; ++i){
    for(int j = 0; j < 45; ++j){
      if(grid[i][j].color == "pink"){
        std::cout << "1x1 at: (" << i << "," << j << ")\n";
      }
    }
  }
}

void Grid::place_initial_tiles_1(){
  // transparent ones:
  place_tile(9, 36, 0);
  place_tile(9, 27, 0);
  place_tile(9, 18, 0);
  place_tile(9, 9, 0);
  place_tile(9, 13, 29);
  place_tile(9, 0, 24);
  place_tile(9, 0, 15);
  // brown ones:
  place_tile(8, 37, 9);
  place_tile(8, 29, 9);
  place_tile(8, 30, 37);
  place_tile(8, 22, 37);
  place_tile(8, 30, 29);
  place_tile(8, 0, 37);
  // yellow ones:
  place_tile(7, 38, 38);
  place_tile(7, 38, 31);
  place_tile(7, 15, 38);
  place_tile(7, 8, 38);
  // light-blue ones;
  place_tile(6, 13, 9);
  // red ones:
  place_tile(5, 24, 9);
  place_tile(5, 19, 9);
  place_tile(5, 8, 33);
  // dark-blue ones:
  place_tile(4, 4, 33);
  place_tile(4, 0, 33);
  place_tile(4, 0, 11);
  // orange ones:
  place_tile(3, 4, 12);
}

void Grid::place_initial_tiles_2(){
  // transparent ones:
  place_tile(9, 36, 0);
  place_tile(9, 36, 9);
  place_tile(9, 36, 18);
  place_tile(9, 36, 27);
  place_tile(9, 36, 36);
  place_tile(9, 19, 36);
  place_tile(9, 19, 27);
  place_tile(9, 10, 36);
  place_tile(9, 4, 0);
  // brown ones:
  place_tile(8, 28, 21);
  place_tile(8, 28, 29);
  place_tile(8, 28, 37);
  place_tile(8, 0, 32);
  place_tile(8, 13, 0);
  place_tile(8, 13, 8);
  // yellow ones:
  place_tile(7, 29, 0);
  place_tile(7, 29, 7);
  place_tile(7, 29, 14);
  place_tile(7, 0, 19);
  place_tile(7, 0, 12);
  // light-blue ones:
  place_tile(6, 0, 26);
  // red ones:
  place_tile(5, 0, 40);
  place_tile(5, 5, 40);
  place_tile(5, 24, 16);
  // dark-blue ones:
  place_tile(4, 0, 0);
  place_tile(4, 0, 4);
  place_tile(4, 0, 8);
  // orange ones:
  place_tile(3, 4, 9);
  place_tile(3, 25, 21);
}

void Grid::place_initial_tiles_3(){
  // transparent ones:
  place_tile(9, 0, 0);
  place_tile(9, 9, 0);
  place_tile(9, 18, 0);
  place_tile(9, 27, 0);
  place_tile(9, 36, 0);
  place_tile(9, 0, 36);
  place_tile(9, 0, 17);
  place_tile(9, 36, 28);
  place_tile(9, 27, 28);
  // brown ones:
  place_tile(8, 0, 9);
  place_tile(8, 8, 9);
  place_tile(8, 33, 37);
  place_tile(8, 25, 37);
  place_tile(8, 17, 37);
  // yellow ones:
  place_tile(7, 16, 9);
  place_tile(7, 9, 17);
  place_tile(7, 38, 9);
  place_tile(7, 32, 16);
  // light-blue ones:
  place_tile(6, 39, 16);
  place_tile(6, 39, 22);
  place_tile(6, 21, 31);
  place_tile(6, 15, 31);
  // red ones:
  place_tile(5, 0, 26);
  place_tile(5, 34, 23);
  place_tile(5, 29, 23);
  // dark-blue ones:
  place_tile(4, 41, 37);
  place_tile(4, 41, 41);
  place_tile(4, 5, 26);
  // orange ones:
  place_tile(3, 24, 28);
  place_tile(3, 29, 20);
  // green ones:
  place_tile(2, 5, 30);
}

void Grid::place_initial_tiles_4(){
  // transparent ones:
  place_tile(9, 0, 0);
  place_tile(9, 0, 9);
  place_tile(9, 36, 0);
  place_tile(9, 27, 0);
  place_tile(9, 36, 9);
  place_tile(9, 36, 18);
  place_tile(9, 19, 28);
  // brown ones:
  place_tile(8, 9, 0);
  place_tile(8, 31, 37);
  place_tile(8, 23, 37);
  place_tile(8, 15, 37);
  place_tile(8, 7, 37);
  // yellow ones:
  place_tile(7, 9, 8);
  place_tile(7, 20, 5);
  place_tile(7, 0, 38);
  place_tile(7, 0, 31);
  // light-blue ones;
  place_tile(6, 0, 18);
  place_tile(6, 6, 18);
  place_tile(6, 39, 39);
  place_tile(6, 39, 33);
  // red ones:
  place_tile(5, 17, 0);
  place_tile(5, 22, 0);
  place_tile(5, 28, 32);
  // dark-blue ones:
  place_tile(4, 16, 8);
  place_tile(4, 35, 33);
  place_tile(4, 15, 33);
  // orange ones:
  place_tile(3, 9, 15);
  place_tile(3, 17, 5);
  // green ones:
  place_tile(2, 33, 35);
}

void Grid::place_initial_tiles_5(){
  // transparent ones:
  place_tile(9, 36, 0);
  place_tile(9, 36, 9);
  place_tile(9, 36, 36);
  place_tile(9, 0, 36);
  place_tile(9, 11, 7);
  // brown ones:
  place_tile(8, 28, 0);
  place_tile(8, 20, 0);
  place_tile(8, 28, 8);
  place_tile(8, 28, 16);
  place_tile(8, 20, 8);
  place_tile(8, 21, 37);
  // yellow ones:
  place_tile(7, 29, 38);
  place_tile(7, 29, 31);
  place_tile(7, 0, 29);
  place_tile(7, 0, 22);
  place_tile(7, 13, 0);
  place_tile(7, 6, 0);
  // light-blue ones;
  place_tile(6, 15, 39);
  // red ones:
  place_tile(5, 7, 31);
  place_tile(5, 6, 7);
  place_tile(5, 6, 12);
  // dark-blue ones:
  place_tile(4, 25, 33);
  place_tile(4, 2, 0);
  // orange ones:
  place_tile(3, 12, 42);
  // green ones:
}

void Grid::place_initial_tiles_6() {
  // 9x9 (light blue)
  place_tile(9, 0, 0);
  place_tile(9, 9, 0);
  place_tile(9, 18, 0);
  place_tile(9, 27, 0);
  place_tile(9, 36, 0);
  place_tile(9, 36, 17);
  place_tile(9, 13, 36);

  // 8x8 (brown)
  place_tile(8, 37, 9);
  place_tile(8, 29, 9);
  place_tile(8, 7, 25);

  // 7x7 (yellow)
  place_tile(7, 0, 17);
  place_tile(7, 0, 24);
  place_tile(7, 0, 31);
  place_tile(7, 0, 38);
  place_tile(7, 29, 17);
  place_tile(7, 22, 32);

  // 6x6 (medium blue)
  place_tile(6, 7, 39);
  place_tile(6, 7, 33);
  place_tile(6, 22, 39);
  place_tile(6, 28, 39);
  place_tile(6, 34, 39);

  // 5x5 (red)
  place_tile(5, 40, 40);
  place_tile(5, 40, 35);

  // 4x4 (dark blue)
  place_tile(4, 0, 9);
  place_tile(4, 0, 13);

  // 3x3 (orange)
  place_tile(3, 26, 9);

  // 2x2 (green)
  place_tile(2, 20, 34);
}

void Grid::place_initial_tiles_7() {
  // 9x9 (light blue)
  place_tile(9, 0, 0);
  place_tile(9, 9, 0);
  place_tile(9, 18, 0);
  place_tile(9, 27, 0);
  place_tile(9, 36, 0);
  place_tile(9, 36, 17);
  place_tile(9, 36, 36);
  place_tile(9, 0, 28);

  // 8x8 (brown)
  place_tile(8, 0, 37);
  place_tile(8, 7, 9);
  place_tile(8, 29, 9);
  place_tile(8, 37, 9);
  place_tile(8, 28, 37);
  place_tile(8, 20, 37);

  // 7x7 (yellow)
  place_tile(7, 0, 9);
  place_tile(7, 15, 9);
  place_tile(7, 22, 9);
  place_tile(7, 15, 16);
  place_tile(7, 29, 17);

  // 6x6 (medium blue)
  place_tile(6, 0, 22);

  // 5x5 (red)
  place_tile(5, 40, 31);
  place_tile(5, 40, 26);

  // 4x4 (dark blue)
  place_tile(4, 16, 41);
  place_tile(4, 36, 26);

  // 3x3 (orange)
  place_tile(3, 12, 17);

  // 2x2 (green)
  place_tile(2, 38, 34);
}

void Grid::place_initial_tiles_8() {
  // 9x9 (light blue)
  place_tile(9, 0, 0);
  place_tile(9, 0, 9);
  place_tile(9, 0, 18);
  place_tile(9, 0, 36);
  place_tile(9, 27, 0);
  place_tile(9, 9, 0);
  place_tile(9, 18, 0);

  // 8x8 (brown)
  place_tile(8, 37, 37);
  place_tile(8, 37, 29);
  place_tile(8, 23, 37);
  place_tile(8, 21, 16);

  // 7x7 (yellow)
  place_tile(7, 9, 38);
  place_tile(7, 16, 38);
  place_tile(7, 9, 9);
  place_tile(7, 16, 9);
  place_tile(7, 14, 22);

  // 6x6 (medium blue)
  place_tile(6, 9, 16);
  place_tile(6, 15, 16);

  // 5x5 (red)
  place_tile(5, 0, 31);
  place_tile(5, 9, 22);

  // 4x4 (dark blue)
  place_tile(4, 0, 27);
  place_tile(4, 41, 25);

  // 3x3 (orange)
  place_tile(3, 34, 42);

  // 2x2 (green)
  place_tile(2, 5, 34);
}

void Grid::place_initial_tiles_9() {
  // 9x9 (light blue)
  place_tile(9, 36, 0);
  place_tile(9, 36, 9);
  place_tile(9, 36, 18);
  place_tile(9, 36, 27);
  place_tile(9, 36, 36);
  place_tile(9, 27, 36);
  place_tile(9, 18, 36);

  // 8x8 (brown)
  place_tile(8, 28, 7);
  place_tile(8, 28, 15);
  place_tile(8, 28, 23);
  place_tile(8, 6, 0);
  place_tile(8, 6, 8);

  // 7x7 (yellow)
  place_tile(7, 29, 0);
  place_tile(7, 22, 0);
  place_tile(7, 21, 24);

  // 6x6 (medium blue)
  place_tile(6, 0, 0);
  place_tile(6, 0, 6);
  place_tile(6, 0, 12);

  // 5x5 (red)
  place_tile(5, 0, 18);
  place_tile(5, 31, 31);
  place_tile(5, 26, 31);
  place_tile(5, 21, 31);

  // 4x4 (dark blue)
  place_tile(4, 0, 23);
  place_tile(4, 24, 20);

  // 3x3 (orange)
  place_tile(3, 25, 7);
}



