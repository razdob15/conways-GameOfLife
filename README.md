# conways-GameOfLife

This repo is an implementation of [Conway's Game Of Life.](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

### Game Description
1. The game is a one-player game and it's occured on a 2D grid.
1. Each cell in the grid can be live or dead.
1. At the beginning of the game, the player chooses what are the live cells.
1. Then, the game starts - every turn the cells' pupolation changes according to the current grid state (also called generation). These changes are occur according these rules:
    - Any live cell with two or three live neighbours survives.
    - Any dead cell with three live neighbours becomes a live cell.
    - All other live cells die in the next generation. Similarly, all other dead cells stay dead.
1. From this point, the generations are created automatically and Infinitely.
