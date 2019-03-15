#include <stdio.h>
#define MAX_LINE 8
#define MAX_ROWS 32
#define MAX_COLS 32
#define INITIAL_ROWS 5
#define INITIAL_COLS 7
#define ALIVE 'X'
#define DEAD '-'

/* count_neighbours: count the number of neighbors that the cell at board[j][i]
 * has */
size_t count_neighbours(char board[MAX_ROWS][MAX_COLS], size_t i, size_t j) {
	size_t count = 0;
	/* up-left */
	if (board[j+1][i-1] == ALIVE) {
		count++;
	}
	/* up */
	if (board[j+1][i] == ALIVE) {
		count++;
	}
	/* up-right */
	if (board[j+1][i+1] == ALIVE) {
		count++;
	}
	/* left */
	if (board[j][i-1] == ALIVE) {
		count++;
	}
	/* right */
	if (board[j][i+1] == ALIVE) {
		count++;
	}
	/* down-left */
	if (board[j-1][i-1] == ALIVE) {
		count++;
	}
	/* down */
	if (board[j-1][i] == ALIVE) {
		count++;
	}
	/* down-right */
	if (board[j-1][i+1] == ALIVE) {
		count++;
	}
	return count;
}

int main(void) {
	/* declare variables */
	char board[MAX_ROWS][MAX_COLS], new_board[MAX_ROWS][MAX_COLS];
	size_t i, j, k, n_generations;
	/* initialize the boards such that there are no live cells */
	for (j = 0; j < MAX_ROWS; j++) {
		for (i = 0; i < MAX_COLS; i++) {
			board[j][i] = DEAD;
			new_board[j][i] = DEAD;
		}
	}
	/* get the initial board layout from stdin and place it in the center-ish
	 * of board */
	for (j = (MAX_ROWS - INITIAL_ROWS)/2; j < (MAX_ROWS + INITIAL_ROWS)/2; j++) {
		for (i = (MAX_COLS - INITIAL_COLS)/2; i < (MAX_COLS + INITIAL_COLS)/2;
				i++) {
			board[j][i] = getchar();
		}
		/* discard newline or '\0' */
		getchar();
	}
	/* simulate n_generations */
	n_generations = 5;
	for (k = 0; k < n_generations; k++) {
		/* declare variable */
		size_t n_alive = 0;
		/* determine which cells live and die based on game of life rules */
		for (j = 1; j < MAX_ROWS - 1; j++) {
			for (i = 1; i < MAX_COLS - 1; i++) {
				/* declare variable */
				size_t count = count_neighbours(board, i, j);
				if (board[j][i] == ALIVE) {
					if (count < 2 || 3 < count) {
						/* kill the cell */
						new_board[j][i] = DEAD;
					}
					else {
						/* cell stays alive */
						new_board[j][i] = ALIVE;
					}
				}
				else {
					if (count == 3) {
						/* new cell is born */
						new_board[j][i] = ALIVE;
					}
					/* don't need to set new_board[j][i] to DEAD since that is
					 * the default */
				}
			}
		}
		/* count the number of cells that are alive */
		for (j = 0; j < MAX_ROWS; j++) {
			for (i = 0; i < MAX_COLS; i++) {
				if (new_board[j][i] == ALIVE) {
					n_alive++;
				}
			}
		}
		/* copy the new board to the old board and set the new board to DEAD */
		for (j = 0; j < MAX_ROWS; j++) {
			for (i = 0; i < MAX_COLS; i++) {
				board[j][i] = new_board[j][i];
				new_board[j][i] = DEAD;
			}
		}
		/* print the number of cells that are alive */
		printf((k == n_generations - 1) ? "%lu\n" : "%lu ", n_alive);
	}
	return 0;
}
