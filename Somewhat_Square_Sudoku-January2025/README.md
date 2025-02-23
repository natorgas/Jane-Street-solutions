# How my code works
### You can find the Puzzle [here](https://www.janestreet.com/puzzles/somewhat-square-sudoku-index/)
My code implements an extended version of the regular recursive backtracking algorithm used for solving regular Sudokus. The idea can be described as follows:\
After finding a valid solution, the corresponding gcd
is saved. Instead of stopping when a valid solution is found, as one would want it for a regular Sudoku, my code keeps running until it has checked all solutions for their gcd. In the end the solution with
the largest gcd is returned. This is
the naive approach which turns out to work fairly well when optimized a little.

In order to make this more efficient I did the follwing:\
Each time a new row of the Sudoku had been filled out, the gcd of all currently completed rows is calculated and compared to the current max gcd.
If the calculated gcd is smaller or equal to the current max gcd, the rest of this possible solution can be disregarded, as the addition of more numbers
(more rows are going to be completed) can only decrease the gcd.

