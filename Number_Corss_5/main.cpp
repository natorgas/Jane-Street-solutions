#include<iostream>
#include<cassert>
#include<cmath>
#include<vector>
#include<map>
#include<functional>
#include<unordered_set>
#include "Grid.h"

bool row0Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long root = (long long)(sqrt(num));
    if(root*root != num && (root+1)*(root+1) != num) return false;
  }
  return true;
}

bool row1Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long product = 1;
    while(num > 0){
      int digit = num % 10;
      product *= digit;
      num /= 10;
    }
    if(product != 20) return false;
  }
  return true;
}

bool row2Valid(std::vector<long long> nums){
  for(long long num : nums){
    if(num % 13 != 0) return false;
  }
  return true;
}

bool row3Valid(std::vector<long long> nums){
  for(long long num : nums){
    if(num % 32 != 0) return false;
  }
  return true;
}

bool row4Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long initial_num = num;
    while(num > 0){
      int digit = num%10;
      if(initial_num % digit != 0) return false;
      num /= 10;
    }
  }
  return true;
}

bool row5Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long product = 1;
    while(num > 0){
      int digit = num % 10;
      product *= digit;
      num /= 10;
    }
    if(product != 25) return false;
  }
  return true;
}

bool row6Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long initial_num = num;
    while(num > 0){
      int digit = num%10;
      if(initial_num % digit != 0) return false;
      num /= 10;
    }
  }
  return true;
}

bool row7Valid(std::vector<long long> nums){
  for(long long num : nums){
    if(num%2 == 0) return false;
    std::string s = std::to_string(num);
    int n = s.length();
    for (int i = 0; i < n / 2; ++i) {
      if (s[i] != s[n - 1 - i])
        return false;
    }
  }
  return true;
}

bool row8Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long x1 = 5 * num * num + 4;
    long long x2 = 5 * num * num - 4;

    long long s1 = (long long)(sqrt(x1));
    long long s2 = (long long)(sqrt(x2));

    if(!((s1 * s1 == x1) || (s2 * s2 == x2))) return false;
  }
  return true;
}

bool row9Valid(std::vector<long long> nums){
  for(long long num : nums){
    long long product = 1;
    while(num > 0){
      int digit = num % 10;
      product *= digit;
      num /= 10;
    }
    if(product != 2025) return false;
  }
  return true;
}

bool row10Valid(std::vector<long long> nums){
  for(long long num : nums){
    if(num <= 1) return false;
    if(num % 2 == 0 && num != 2) return false;
    for(int i = 3; i <= sqrt(num); i += 2){
      if(num % i == 0) return false;
    }
  }
  return true;
}

bool rowValid(int n, std::vector<long long> nums){
  if(n == 0) return row0Valid(nums);
  if(n == 1) return row1Valid(nums);
  if(n == 2) return row2Valid(nums);
  if(n == 3) return row3Valid(nums);
  if(n == 4) return row4Valid(nums);
  if(n == 5) return row5Valid(nums);
  if(n == 6) return row6Valid(nums);
  if(n == 7) return row7Valid(nums);
  if(n == 8) return row8Valid(nums);
  if(n == 9) return row9Valid(nums);
  if(n == 10) return row10Valid(nums);
  else{
    std::cout << "Tried to check if row " << n << " is valid \n";
    assert(false);
    return false;
  }
}


std::vector<std::vector<int>> getCombinations(int n, int k) {
  std::vector<std::vector<int>> result;
  std::vector<int> current;

  std::function<void(int, int)> backtrack = [&](int remaining, int depth) {
    if (depth == 0) {
      if (remaining == 0) {
        result.push_back(current);
      }
      return;
    }
    for (int i = 0; i <= remaining; ++i) {
      current.push_back(i);
      backtrack(remaining - i, depth - 1);
      current.pop_back();
    }
  };
  backtrack(n, k);
  return result;
}

void placeTiles(Grid& g, int row, int col, int& max_correct_row){
  // Early pruning: check numbers to the left in row above if they satisfy condition of row-1
  if(row > 0 && g.grid[row-1][col].tile){
    auto nums = g.numberInRowFromIndex(row-1, col);
    if(!rowValid(row-1, nums)) return;
  }
  
  // Final check whenever we reach bottom of grid
  if(row > 10){
    for(int i = 0; i < 11; ++i){
      if(!g.rowValid(i)) return;
    }
    std::cout << "Found solution: \n";
    g.printGrid();
    exit(0);
  }

  // If we come to the end of a row:
  if (col >= 11){                 
    std::vector<long long> numbers_in_valid_row = g.numberInRow(row-1);

    if (row-1 >= 0 && !g.rowValid(row - 1)) return; // return if the row with newly locked in numbers is invalid
                                                    
    // check for duplicates...
    else if(row-1 >= 0 && g.rowValid(row - 1)){
      // ...within the new row
      std::unordered_set<long long> curr(numbers_in_valid_row.begin(), numbers_in_valid_row.end());
      if(curr.size() != numbers_in_valid_row.size()) return;

      // ...considering other rows
      for(long long n : numbers_in_valid_row){
        if(g.seen_in_grid.count(n)) return;
      }

      // No duplicates -> insert valid row's numbers
      for(long long n : numbers_in_valid_row) g.seen_in_grid.insert(n);
      max_correct_row = std::max(row-1, max_correct_row);
    }

    // Go to next row
    placeTiles(g, row + 1, 0, max_correct_row);

    // In case tiling does not work -> remove numbers from seen set
    for(long long n : numbers_in_valid_row){
      g.seen_in_grid.erase(n);
    }
    return;
  }

  // If no tile can be placed, skip and go to the next cell
  if(!g.tilePlacable(row, col)){
    placeTiles(g, row, col+1, max_correct_row);
    return;
  }

  if(g.tilePlacable(row, col)){ // if tile can be placed
    g.placeTile(row, col);     // place tile

    int val = g.grid[row][col].val;

    std::vector<std::pair<int, int>> valid_neighbors;
    std::vector<int> original_values;

    // Get valid neighbors (not constant, not out of bounds, etc)
    for(auto& [dr, dc] : g.directions){
      int nr = row + dr;
      int nc = col + dc;
      if(nr>= 0 && nc >= 0 && nr < 11 && nc < 11){
        Node& neighbor = g.grid[nr][nc];
        if(!neighbor.is_constant && neighbor.val < 9){
          valid_neighbors.push_back({nr, nc});
          original_values.push_back(neighbor.val);
        }
      }
    }

    int increasable_cells = valid_neighbors.size(); // number of cells that can be increased (<= 4)
    auto combinations = getCombinations(val, increasable_cells); // combinations of <increasable_cells> summands that equal <val>
    
    for(const auto& combination : combinations){
      // check if this combination leads to an overflow...
      bool overflow = false;
      for(int i = 0; i < valid_neighbors.size(); ++i){
        int neighbor_row = valid_neighbors[i].first;
        int neighbor_col = valid_neighbors[i].second;
        if (g.grid[neighbor_row][neighbor_col].val + combination[i] > 9){
          overflow = true;
          break;
        }
      }
      if(overflow) continue; // ...if yes then skip it

      // else apply the increments
      for(int j = 0; j < increasable_cells; ++j){
        int nr = valid_neighbors[j].first;
        int nc = valid_neighbors[j].second;
        g.grid[nr][nc].val += combination[j];
      }

      // and go to the next col
      placeTiles(g, row, col+1, max_correct_row);

      // In case tiling does not work -> reset the neighbor's values to original
      for(int i = 0; i < valid_neighbors.size(); ++i){ 
        int neighbor_row = valid_neighbors[i].first;
        int neighbor_col = valid_neighbors[i].second;
        g.grid[neighbor_row][neighbor_col].val = original_values[i];
      }
    }

    // no combination is good -> remove the placed tile
    g.removeTile(row, col);

    // undo any increments
    for(int i = 0; i < valid_neighbors.size(); ++i){ // reset to original
      int neighbor_row = valid_neighbors[i].first;
      int neighbor_col = valid_neighbors[i].second;
      g.grid[neighbor_row][neighbor_col].val = original_values[i];
    }

    // and go to the next cell without placing anything here
    placeTiles(g, row, col+1, max_correct_row);
  }

}

void findInitialPlacement(Grid& g, int area, Grid& last_grid, int& last_max_row){
  if(area > 9){ // Found an initial tiling
    // check if there is any difference between new and old grid from row 0 to last max row + 2
    bool all_same = true;
    for(int i = 0; i <= last_max_row+2; ++i){  
      if(i > 10) break;
      if(last_grid.numberInRow(i).size() == 0){
        last_grid = g;
        continue;
      }
      long long last_row_num = last_grid.numberInRow(i).at(0);
      long long curr_row_num = g.numberInRow(i).at(0);
      if(last_row_num != curr_row_num){
        all_same = false; // something relevant has changed
        break;
      }
    }
    // If all relevant rows are the same as in the grid that did not work, neglect this grid
    if(all_same) return;

    last_max_row = -1;
    placeTiles(g, 0, 0, last_max_row); // else try to find tiling

    // In case this initial placement did not work -> set last grid to said grid
    last_grid = g;                     

    g.printGrid();
    std::cout << "This grid did not work \n"; 
    std::cout << "The max correct row was " << last_max_row << "\n";

    return; 
  } 

  if(!g.areaEmpty(area)){ 
    findInitialPlacement(g, 1+area, last_grid, last_max_row); //Area is not empty
    return;
  }

  // set area value, check if boorders ok, go to next 
  int row = g.access_area[area].first;
  int col = g.access_area[area].second;

  for(int value = 1; value <= 9; ++value){
    g.setValueArea(row, col, value); // Set the area value to i
    if(!g.bordersOk(row, col)){ // if borders are not ok
      g.setValueArea(row, col, 0); // reset the area
    }
    else{
      findInitialPlacement(g, area+1, last_grid, last_max_row);
    }
  }
  g.setValueArea(row, col, 0); // backtrack
}

//------------------------------------------------------

int main(){

  Grid g;

  Grid last;

  int max_row = -1;

  findInitialPlacement(g, 1, last, max_row);

  std::cout << "Nothing found" << std::endl;

  return 0;
}
