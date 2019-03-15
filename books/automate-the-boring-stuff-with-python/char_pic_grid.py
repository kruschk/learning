#!/usr/bin/python3

grid = [['.', '.', '.', '.', '.', '.'],
        ['.', 'O', 'O', '.', '.', '.'],
        ['O', 'O', 'O', 'O', '.', '.'],
        ['O', 'O', 'O', 'O', 'O', '.'],
        ['.', 'O', 'O', 'O', 'O', 'O'],
        ['O', 'O', 'O', 'O', 'O', '.'],
        ['O', 'O', 'O', 'O', '.', '.'],
        ['.', 'O', 'O', '.', '.', '.'],
        ['.', '.', '.', '.', '.', '.']]

# this would be way better, but grid is stored funny, so it prints the
# transpose of the desired grid
def draw_grid(grid):
    for arr in grid:
        for elem in arr:
            print(elem, end="")
        print()

# this works as desired
def draw_grid2(grid):
    for x in range(len(grid[0])):
        for y in range(len(grid)):
            print(grid[y][x], end="");
        print()

draw_grid2(grid)
