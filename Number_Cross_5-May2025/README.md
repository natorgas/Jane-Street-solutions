# How my code works

### You can find the puzzle [here](https://www.janestreet.com/puzzles/number-cross-5-index/)

My algorithm uses nested backtracking in order to find the solution. In a nutshell, the first backtracking searches for valid placements of
numbers within the grid. Once it has found one, that grid is passed to another function which then tries to find a tile placement for which all
conditions are satisfied. I made two major optimizations, one makes sure that we do not try to place tiles onto valid grids for which we already know
that there is no way we can make a certain row valid, this can be seen as some kind of memoisation. The second optimization was immplemented in order
to recognize the invalidity of a row earlier, not only once it is completed.

It takes about 10 minutes to find the solution when explicitly using compiler optimizations.
