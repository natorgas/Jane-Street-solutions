#include<iostream>
#include<cassert>
#include<cmath>
#include<vector>
#include<map>
#include<functional>
#include<unordered_set>
#include "Grid.h"

void Grid::printGrid(){
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 11; j++){
      if(grid[i][j].tile){
        std::cout << " " << " ";
      }
      else{
        std::cout << grid[i][j].val << " ";
      }
    }
    std::cout << std::endl;
  }
}

void Grid::updateAreaValues(int val, int area){
  for(int i = 0; i < 11; ++i){
    for(int j = 0; j < 11; ++j){
      if(grid[i][j].area == area){
        grid[i][j].val = val;
      }
    }
  }
}

void Grid::setValueArea(int row, int col, int val){
  grid[row][col].val = val;
  updateAreaValues(val, grid[row][col].area);
}

void Grid::setValue(int row, int col, int val){
  grid[row][col].val = val;
}

std::vector<long long> Grid::numberInRow(int row){
  assert(row < 11);
  std::vector<long long> nums;
  long long num = 0;
  long long coeff = 1;
  int index = 10;
  while(grid[row][index].tile && index >= 0){
    --index;
  }
  for(int i = index; i >= 0; --i){
    if(!grid[row][i].tile){
      num += grid[row][i].val*coeff;
      coeff *= 10;
    }
    else{
      nums.push_back(num);
      coeff = 1;
      num = 0;
    }
  }
  if(num != 0){
    nums.push_back(num);
  }
  return nums;
}

std::vector<long long> Grid::numberInRowFromIndex(int row, int right){
  assert(row < 11);
  assert(grid[row][right].tile);
  std::vector<long long> nums;
  long long num = 0;
  long long coeff = 1;
  int index = right;
  while(grid[row][index].tile && index >= 0){
    --index;
  }
  for(int i = index; i >= 0; --i){
    if(!grid[row][i].tile){
      num += grid[row][i].val*coeff;
      coeff *= 10;
    }
    else{
      assert(num/10 != 0); // must be at least two digits long;
      nums.push_back(num);
      coeff = 1;
      num = 0;
    }
  }
  if(num != 0){
    assert(num/10 != 0);
    nums.push_back(num);
  }
  return nums;
}

bool Grid::row0Valid(){
  std::vector<long long> nums = numberInRow(0);
  for(long long num : nums){
    long long root = (long long)(sqrt(num));
    if(root*root != num && (root+1)*(root+1) != num) return false;
  }
  return true;
}

bool Grid::row1Valid(){
  std::vector<long long> nums = numberInRow(1);
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

bool Grid::row2Valid(){
  std::vector<long long> nums = numberInRow(2);
  for(long long num : nums){
    if(num % 13 != 0) return false;
  }
  return true;
}

bool Grid::row3Valid(){
  std::vector<long long> nums = numberInRow(3);
  for(long long num : nums){
    if(num % 32 != 0) return false;
  }
  return true;
}

bool Grid::row4Valid(){
  std::vector<long long> nums = numberInRow(4);
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

bool Grid::row5Valid(){
  std::vector<long long> nums = numberInRow(5);
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

bool Grid::row6Valid(){
  std::vector<long long> nums = numberInRow(6);
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

bool Grid::row7Valid(){
  std::vector<long long> nums = numberInRow(7);
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

bool Grid::row8Valid(){
  std::vector<long long> nums = numberInRow(8);
  for(long long num : nums){
    long long x1 = 5 * num * num + 4;
    long long x2 = 5 * num * num - 4;

    long long s1 = (long long)(sqrt(x1));
    long long s2 = (long long)(sqrt(x2));

    if(!((s1 * s1 == x1) || (s2 * s2 == x2))) return false;
  }
  return true;
}

bool Grid::row9Valid(){
  std::vector<long long> nums = numberInRow(9);
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

bool Grid::row10Valid(){
  std::vector<long long> nums = numberInRow(10);
  for(long long num : nums){
    if(num <= 1) return false;
    if(num == 2) return true;
    if(num % 2 == 0) return false;
    for(int i = 3; i <= sqrt(num); i += 2){
      if(num % i == 0) return false;
    }
  }
  return true;
}

bool Grid::tilePlacable(int row, int col){ 
  if(grid[row][col].is_constant) return false;
  for(auto& [d_row, d_col] : directions){
    int n_row = row + d_row;
    int n_col = col + d_col;
    if(n_row < 0 || n_col < 0 || n_row >= 11 || n_col >= 11) continue;
    if(grid[n_row][n_col].tile) return false;
  }
  if(col == 1 || col == 9) return false; // would be only one number at the edge
  if(col-2 >= 0 && grid[row][col-2].tile) return false;
  if(col+2 < 11 && grid[row][col+2].tile) return false;
  return true;
}

bool Grid::bordersOk(int row, int col){
  // new value has been placed in (row, col)
  assert(grid[row][col].val > 0 && grid[row][col].val < 10);
  int value = grid[row][col].val;
  int area = grid[row][col].area;
  for(int i = 0; i < 11; ++i){
    for(int j = 0; j < 11; ++j){
      if(grid[i][j].area == area){  // this is a node in our area
        for(auto& [d_row, d_col] : directions){
          int n_row = i + d_row;
          int n_col = j + d_col;
          if(n_row < 0 || n_col < 0 || n_row >= 11 || n_col >= 11) continue; // out of bounds
          if(grid[n_row][n_col].area != area && grid[n_row][n_col].val == value) return false;
        }
      }
    }
  }
  return true;
}

bool Grid::gridCompleted(){
  for(int i = 0; i < 11; ++i){
    for(int j = 0; j < 11; ++j){
      if(grid[i][j].val == 0) return false;
    }
  }
  return true;
}

bool Grid::rowValid(int n){
  if(n == 0) return row0Valid();
  if(n == 1) return row1Valid();
  if(n == 2) return row2Valid();
  if(n == 3) return row3Valid();
  if(n == 4) return row4Valid();
  if(n == 5) return row5Valid();
  if(n == 6) return row6Valid();
  if(n == 7) return row7Valid();
  if(n == 8) return row8Valid();
  if(n == 9) return row9Valid();
  if(n == 10) return row10Valid();
  else{
    std::cout << "Tried to check if row " << n << " is valid \n";
    assert(false);
    return false;
  }
}

bool Grid::areaEmpty(int area){
  int row = access_area[area].first;
  int col = access_area[area].second;
  if(grid[row][col].val == 0) return true;
  return false;
}

void Grid::placeTile(int row, int col){ // Assumes tile is placable
  grid[row][col].tile = true;
}

void Grid::removeTile(int row, int col){
  grid[row][col].tile = false;
}

