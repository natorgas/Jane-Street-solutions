#include <iostream>
#include <cassert>
#include <set>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int ROWS = 12;
const int COLS = 12;

struct Node
{
  Node *left;
  Node *up;
  Node *right;
  Node *down;
  int value;
  bool is_laser;
  char mirror;
  Node() : left(nullptr), up(nullptr), right(nullptr), down(nullptr), is_laser(false), value(0), mirror('0') {}
};

void initializeGrid(Node grid[ROWS][COLS]){
  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLS; j++){
      if (j > 0)
        grid[i][j].left = &grid[i][j - 1];
      if (j < COLS - 1)
        grid[i][j].right = &grid[i][j + 1];
      if (i > 0)
        grid[i][j].up = &grid[i - 1][j];
      if (i < ROWS - 1)
        grid[i][j].down = &grid[i + 1][j];
      grid[i][j].is_laser = (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1);
    }
  }
}

bool is_corner_node(Node *node){
  int nullCount = 0;
  if (node->left == nullptr)
    nullCount++;
  if (node->up == nullptr)
    nullCount++;
  if (node->right == nullptr)
    nullCount++;
  if (node->down == nullptr)
    nullCount++;
  return nullCount > 1;
}

int multiply_vector_elements(vector<int> vec){
  int product = 1;
  for (int i = 0; i < int(vec.size()); ++i){
    product *= vec[i];
  }
  return product;
}

int trace_beam(Node* node, int count, vector<int> segments, const string& from) {
  if (node->is_laser) {
    segments.push_back(count);
    node->value = multiply_vector_elements(segments);
    return node->value;
  }

  if (node->mirror == '0') {
    if (from == "top")    return trace_beam(node->down, count + 1, segments, "top");
    if (from == "right")  return trace_beam(node->left, count + 1, segments, "right");
    if (from == "left")   return trace_beam(node->right, count + 1, segments, "left");
    if (from == "bottom") return trace_beam(node->up, count + 1, segments, "bottom");
  }

  segments.push_back(count);

  if (node->mirror == '/') {
    if (from == "top")    return trace_beam(node->left, 1, segments, "right");
    if (from == "right")  return trace_beam(node->down, 1, segments, "top");
    if (from == "left")   return trace_beam(node->up, 1, segments, "bottom");
    if (from == "bottom") return trace_beam(node->right, 1, segments, "left");
  }

  if (node->mirror == '\\') {
    if (from == "top")    return trace_beam(node->right, 1, segments, "left");
    if (from == "right")  return trace_beam(node->up, 1, segments, "bottom");
    if (from == "left")   return trace_beam(node->down, 1, segments, "top");
    if (from == "bottom") return trace_beam(node->left, 1, segments, "right");
  }

  cout << "Problem with trace_beam function" << endl;
  return -1;
}


int activate_laser(Node *laser_node){
  if (is_corner_node(laser_node)) return 0;
  vector<int> segments = {};

  if (laser_node->up == nullptr) return trace_beam(laser_node->down, 1, segments, "top");
  else if (laser_node->left == nullptr) return trace_beam(laser_node->right, 1, segments, "left");
  else if (laser_node->right == nullptr) return trace_beam(laser_node->left, 1, segments, "right");
  else if (laser_node->down == nullptr)  return trace_beam(laser_node->up, 1, segments, "bottom");

  else{
    cout << "Problem with laser activation: Probably tried to activate a node that is not a laser." << endl;
    return -1;
  }
}

void activate_lasers(Node grid[ROWS][COLS]){
  for (int i = 0; i < ROWS; ++i){
    for (int j = 0; j < COLS; ++j){
      if (grid[i][j].is_laser){
        activate_laser(&grid[i][j]);
      }
    }
  }
}

void printGrid(Node grid[ROWS][COLS]){
  activate_lasers(grid);
  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLS; j++){
      if (grid[i][j].is_laser){
        std::cout << std::setw(4) << grid[i][j].value << " ";
      }
      else{
        if (grid[i][j].mirror == '0'){
          std::cout << std::setw(5) << ". ";
        }
        else if (grid[i][j].mirror == '/'){
          std::cout << std::setw(5) << "/ ";
        }
        else if (grid[i][j].mirror == '\\'){
          std::cout << std::setw(5) << "\\ ";
        }
      }
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
}

bool mirror_placable(Node *node) {
  if (node->is_laser) return false;
  if ((node->up && node->up->mirror != '0') ||
      (node->down && node->down->mirror != '0') ||
      (node->left && node->left->mirror != '0') ||
      (node->right && node->right->mirror != '0')) {
    return false;
  }
  return true;
}

bool fixed_values_correct(Node grid[ROWS][COLS], vector<vector<int>> pairs){
  for (vector<int> v : pairs){
    if (activate_laser(&grid[v[0]][v[1]]) != v[2]){
      return false;
    }
  }
  return true;
}

vector<int> allowed_step_sizes(int n){
  vector<int> steps;
  for (int i = 1; i <= n; ++i){
    if (n % i == 0){
      steps.push_back(i);
    }
  }
  return steps;
}

void find_solution_one_laser(int pairs_index, Node grid[ROWS][COLS], int row, int col, int value, Node *initial_laser, int inital_value, string coming_from, vector<vector<int>> pairs){
  //cout << "searching for value " << inital_value << " in " << pairs[pairs_index][0] << "," << pairs[pairs_index][1] << endl;
  //cout << "currently at node " << row << ", " << col << ":" << endl;

  // IF CURRENT NODE IS LASER:

	if(grid[row][col].is_laser){
		vector<int> step_sizes = allowed_step_sizes(value);
		Node node = grid[row][col];
		if(node.up == nullptr){
      for(int step : step_sizes){
        if(row + step < 11 && mirror_placable(&grid[row+step][col])){
          if(grid[row+step][col].mirror == '0'){
            grid[row+step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
        }
      }
		}
		else if(node.left == nullptr){
			for(int step : step_sizes){
        if(col + step < 11 && mirror_placable(&grid[row][col+step])){
          if(grid[row][col+step].mirror == '0'){
            grid[row][col+step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
        }
      }
		}
		else if(node.down == nullptr){
			for(int step : step_sizes){
        if(row - step > 0 && mirror_placable(&grid[row-step][col])){
          if(grid[row-step][col].mirror == '0'){
            grid[row-step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
        }
      }
		}
		else if(node.right == nullptr){
			for(int step : step_sizes){
				if(col - step > 0 && mirror_placable(&grid[row][col-step])){
          if(grid[row][col-step].mirror == '0'){
            grid[row][col-step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
				}
			}
	  }
	}

  // END OF: IF INITIAL NODE IS LASER

  // CHECK IF THE ACTIVATED INITAL LASER HAS THE DESIRED VALUE

	if(activate_laser(initial_laser) == inital_value){
    for(int i = 0; i <= pairs_index; ++i){ // check for collisions
      //cout << "laser: " << pairs[i][0] << "," << pairs[i][1] << " has value " << activate_laser(&grid[pairs[i][0]][pairs[i][1]]) << ". Expected: " << pairs[i][2] << endl;
      if(activate_laser(&grid[pairs[i][0]][pairs[i][1]]) != pairs[i][2]) return;
    }
    if(fixed_values_correct(grid, pairs)){ // check if all values correct
      cout << "exiting" << endl;
      printGrid(grid);
      exit(0);
    }
    cout << "Found solution for value = " << inital_value << endl;
    printGrid(grid);
    ++pairs_index;
    find_solution_one_laser(pairs_index, grid, pairs[pairs_index][0], pairs[pairs_index][1], pairs[pairs_index][2], &grid[pairs[pairs_index][0]][pairs[pairs_index][1]], pairs[pairs_index][2], "", pairs);
	}

  // END OF: CHECK IF ACTIVATED INITIAL LASER HAS DESIRED VALUE

  vector<int> step_sizes = allowed_step_sizes(value);
  if(step_sizes.size() == 1) return;

  if(grid[row][col].mirror == '/'){
    if(coming_from == "top"){
      for(int step : step_sizes){
        if(col - step > 0 && mirror_placable(&grid[row][col-step])){
          if(grid[row][col-step].mirror == '0'){
            grid[row][col-step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
        }
      }
    }
    else if(coming_from == "right"){
      for(int step : step_sizes){
        if(row + step < 11 && mirror_placable(&grid[row+step][col])){
          if(grid[row+step][col].mirror == '0'){
            grid[row+step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row + step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row + step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row + step, col, value / step, initial_laser, inital_value, "top", pairs);
        }
      }
    }
    else if(coming_from == "bottom"){
      for(int step : step_sizes){
        if(col + step < 11 && mirror_placable(&grid[row][col+step])){
          if(grid[row][col+step].mirror == '0'){
            grid[row][col+step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '0';

          }
          else find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
        }
      }
    }
    else if(coming_from == "left"){
      for(int step : step_sizes){
        if(row - step > 0 && mirror_placable(&grid[row-step][col])){
          if(grid[row-step][col].mirror == '0'){
            grid[row-step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row-step, col, value / step, initial_laser, inital_value, "bottom", pairs);
        }
      }
    }
  }

  else if(grid[row][col].mirror == '\\'){
    if(coming_from == "top"){
      for(int step : step_sizes){
        if(col + step < 11 && mirror_placable(&grid[row][col+step])){
          if(grid[row][col+step].mirror == '0'){
            grid[row][col+step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
            grid[row][col+step].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row, col+step, value / step, initial_laser, inital_value, "left", pairs);
        }
      }
    }
    else if(coming_from == "right"){
      for(int step : step_sizes){
        if(row - step > 0 && mirror_placable(&grid[row-step][col])){
          if(grid[row-step][col].mirror == '0'){
            grid[row-step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row - step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row - step, col, value / step, initial_laser, inital_value, "bottom", pairs);
            grid[row-step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row - step, col, value / step, initial_laser, inital_value, "bottom", pairs);
        }
      }
    }
    else if(coming_from == "bottom"){
      for(int step : step_sizes){
        if(col - step > 0 && mirror_placable(&grid[row][col-step])){
          if(grid[row][col-step].mirror == '0'){
            grid[row][col-step].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
            grid[row][col-step].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row, col-step, value / step, initial_laser, inital_value, "right", pairs);
        }
      }
    }
    else if(coming_from == "left"){
      for(int step : step_sizes){
        if(row + step < 11 && mirror_placable(&grid[row+step][col])){
          if(grid[row+step][col].mirror == '0'){
            grid[row+step][col].mirror = '/';
            find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '\\';
            find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
            grid[row+step][col].mirror = '0';
          }
          else find_solution_one_laser(pairs_index, grid, row+step, col, value / step, initial_laser, inital_value, "top", pairs);
        }
      }
    }
  }
}

int main(){
  Node grid[ROWS][COLS];
  initializeGrid(grid);

  vector<vector<int>> pairs = {{0, 3, 112}, {0, 5, 48}, {0, 6, 3087}, {0, 7, 9}, {0, 10, 1}, {4, 0, 27}, {8, 0, 12}, {9, 0, 225}, {11, 1, 2025}, {11, 4, 12}, {11, 5, 64}, {11, 6, 5}, {11, 8, 405}, {2, 11, 4}, {3, 11, 27}, {7, 11, 16}};

  find_solution_one_laser(0, grid, 0, 3, 112, &grid[0][3], 112, "", pairs);

  return 0;
}
