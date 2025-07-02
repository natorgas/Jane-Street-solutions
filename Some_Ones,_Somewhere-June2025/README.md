# How my code works

### You can find the puzzle [here](https://www.janestreet.com/puzzles/some-ones-somewhere-index/)

By staring at the provided picture for long enough, one might notice the words "tiling" and "partridge" formed
by the letters on the left and on the top of the grid. Googling this term explains what the 9 grids are about:
We need to fill them with one 1x1, two 2x2, three 3x3,..., nine 9x9 tiles, such that the whole 45x45 area is covered by tiles.
This is what the code in this folder was written for, it is simply a solver for the provided, partially completed, partridge tilings.
Next we notice that the distance between letters on the edges of the grid, measured in 1x1 tiles, corresponds to the distance of those letters
in the alphabet. We fill out the remaining letters and interpret this as a coordinate system. Judging by the name of the puzzle, the location of the 1x1
tiles might be interesting. And in fact, if we map their location for every grid to the corresponding pair of letters, and also take into consideration
the strings "a" and "the", which are visible next to the grid, we finally get the answer to this puzzle:

THE SUM OF CUBES IS A SQUARE

