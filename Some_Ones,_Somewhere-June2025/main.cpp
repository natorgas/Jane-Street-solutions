#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Grid.h"

void find_placement(Grid& g, int row, int col){
  // board is full
  if(row >= 45){
    g.print_grid();
    g.print_pink_coordinates();
    exit(0);
  }

  // row is full -> go to next
  if(col >= 45){
    find_placement(g, row+1, 0);
    return;
  }

  if(g.cell_covered(row, col)){
    find_placement(g, row, col+1);
    return;
  }

  for(auto& [size, n_available] : g.n_available_tiles){
    if(n_available <= 0) continue;          // no more available tiles of this size
    if(g.place_tile(size, row, col)){       // if tile can be placed
      find_placement(g, row, col+1);        // try to go on
      g.remove_tile(size, row, col);        // if we return then remove tile
    }
  }
}

int main(){

  int grid_n;

  std::cout << "Which grid to solve? (1-9)? \n";
  
  std::cin >> grid_n;

  Grid g(grid_n);

  //Grid g = Grid();

  g.print_grid();

  find_placement(g, 0, 0);

  return 0;
}
