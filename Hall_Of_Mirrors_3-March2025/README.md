# How my code works

### You can find the puzzle [here](https://www.janestreet.com/puzzles/hall-of-mirrors-3-index/)

Just like my solution for January's puzzle, what I have implemented here is a decorated version of recursive
backtracking (this time the changes were quite a lot bigger than in January though). 

First of all a grid-like datastructure was implemented
which essentially was a 2D array of nodes. A node is either a laser or it is not. If it is one, then its member variable `value` holds the value which 
is assigned to it according to the puzzle's rules. For all non laser nodes we have `value = 0`. 

The naive way to solve this problem is to try out every legal configuration of mirrors and return the one which places the mirrors in such a way that the requirements
set by the puzzle are met. As this is very inefficient, I made use of the fact that if we want to find a valid configuration of mirrors, such that *one* of these lasers has
the desired value, the lengths of the segments along its path must be divisors of that value. This can be taken one step further by thinking about what happens when the laser beam
completes the first segment of its path. Let us call the desired value $x$, and assume the first segment of that path has length $l$ (which must be a divisor of $x$). We now know
that the lenght of the second segment must be a divisor of $\frac{x}{l}$. More generally, if the lengths of the segments of a path up to a certain point have been $l_1, l_2, ..., l_n$,
then the next length of the next segment will be a divisor of $\frac{x}{l_1 \cdot l_2 \cdot ... \cdot l_n}$. This means we can iterate over all of these divisors and try to place mirrors whenever possible. We 
do this recursively and remove mirrors that do not lead to a valid solution.
