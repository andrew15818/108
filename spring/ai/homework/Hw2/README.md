# Introduction To Artificial Intelligence Homework 2
Author: Andres Ponce 彭思安
## Main Objective

This assignment's objective is to impelement a backtracking algorithm that 
can solve a minesweeper board. We have an empty board with some squares filled
in with hints, or the amount of adjacent cells in the array with a bomb. Using this,
we are to find a solution for this board.

### Methods

As mentioned, we are to use a backtracking search algorithm to implement this assignment.
According to [this resource](https://en.wikipedia.org/wiki/Backtracking), we need some
basic functions:

1. **root**: Since we interpret the game as a tree, we need a root from which we start. 
For this assignment we use an empty node, since we don't start from any node in specific.

2. **reject**: Function that returns **true** if there is **no way** to solve the board using
this node. I think that this happens when a hint node has too many mines that are adjacent to it. 
If a node is rejected, we have to undo whatever changes we did to the other node's values, and 
remove it from the queue of possible nodes to explore. 

3. **accept**: Returns **true** if assigning a mine to the current node solves the board. I think
this happens when the node is a valid assignment(doesn't make its neighbors have too many mines), and
we run out of mines to assign.

4. **first**: Have to find some sort of ordering so that we can iterate through the descendant nodes in 
some order.  Maybe using the Manhattan Distance to find the closest available nodes?

5. **next**: Similar to 4, just need a way to iterate through the available descendant nodes.

Then, we need a main driver function that recurses through the descendant nodes until we either find 
a solution or run out of nodes.
