#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"

#define BOARD_HEIGHT 4
#define BOARD_WIDTH 4

#define SWAP(a, b)\
	temp = a;\
	a = b;\
	b = temp;

/* the game board */
static unsigned short int board[BOARD_HEIGHT][BOARD_WIDTH];

/* print_board: prints the board to stdout */
void print_board(void) {
	unsigned short int r, c;
	for (r = 0; r < BOARD_HEIGHT; r++) {
		for (c = 0; c < BOARD_WIDTH; c++) {
			printf((c == BOARD_WIDTH - 1) ? "%2hu\n" : "%2hu ", board[r][c]);
		}
	}
}

/* shift_row_right: shift row r to the right, starting from column c (we
 * usually don't need to shift the whole row) */
void shift_row_right(const unsigned short int r, unsigned short int c) {
	/* start from c, and go through each column */
	for (; c > 0; c--) {
		/* if this element of the row is 0, we need to shift */
		if (0 == board[r][c]) {
			/* starting at column c - 1, find the first nonzero element to the
			 * left */
			unsigned short int k = c;
			while (k-- > 0) {
				if (0 != board[r][k]) {
					/* if a nonzero element is found, we swap it with the
					 * zero element we found before */
					unsigned short int temp;
					SWAP(board[r][c], board[r][k]);
					break;
				}
			}
		}
	}
}

/* shift_column_up: shift column c up, starting from row r */
void shift_column_up(unsigned short int r, const unsigned short int c) {
	for (; r < BOARD_HEIGHT - 1; r++) {
		if (0 == board[r][c]) {
			unsigned short int k;
			for (k = r + 1; k < BOARD_HEIGHT; k++) {
				if (0 != board[k][c]) {
					unsigned short int temp;
					SWAP(board[r][c], board[k][c]);
					break;
				}
			}
		}
	}
}

/* shift_row_left: shift row r to the left, starting from column c */
void shift_row_left(const unsigned short int r, unsigned short int c) {
	unsigned short int k, temp;
	for (; c < BOARD_WIDTH - 1; c++) {
		if (0 == board[r][c]) {
			for (k = c + 1; k < BOARD_WIDTH; k++) {
				if (0 != board[r][k]) {
					SWAP(board[r][c], board[r][k]);
					break;
				}
			}
		}
	}
}

/* shift_column_down: shift column c down, starting from row r */
void shift_column_down(unsigned short int r, const unsigned short int c) {
	for (; r > 0; r--) {
		if (0 == board[r][c]) {
			unsigned short int k = r;
			while (k-- > 0) {
				if (0 != board[k][c]) {
					unsigned short int temp;
					SWAP(board[r][c], board[k][c]);
					break;
				}
			}
		}
	}
}

void make_move(char move) {
	unsigned short int r, c;
	switch (move) {
		case 'R':
			/* go through each row */
			r = BOARD_HEIGHT;
			while (r-- > 0) {
				/* shift current row right, starting at the rightmost column */
				shift_row_right(r, BOARD_WIDTH - 1);
				/* go through each element of this column, and combine elements
				 * that are pushed into each other */
				for (c = BOARD_WIDTH - 1; c > 0; c--) {
					if (board[r][c] == board[r][c - 1]) {
						/* add the left element to the right (equivalent to
						 * multiplying right by 2 since they are equal) */
						board[r][c] *= 2;
						/* set the right element to 0 */
						board[r][c - 1] = 0;
						/* shift row right, starting from the next column */
						shift_row_right(r, c - 1);
					}
				}
			}
			break;
		case 'U':
			/* go through each column */
			for (c = 0; c < BOARD_WIDTH; c++) {
				/* shift current column up, starting at the top row */
				shift_column_up(0, c);
				/* go through each element of this row, and combine elements
				 * that are pushed into each other */
				for (r = 0; r < BOARD_HEIGHT - 1; r++) {
					if (board[r][c] == board[r + 1][c]) {
						/* add the lower element to the upper (equivalent to
						 * multiplying upper by 2 since they are equal) */
						board[r][c] *= 2;
						/* set the lower element to 0 */
						board[r + 1][c] = 0;
						/* shift column up, starting from the next row */
						shift_column_up(r + 1, c);
					}
				}
			}
			break;
		case 'L':
			/* go through each row */
			for (r = 0; r < BOARD_HEIGHT; r++) {
				/* shift current row left, starting at the leftmost column */
				shift_row_left(r, 0);
				/* go through each element of this column, and combine elements
				 * that are pushed into each other */
				for (c = 0; c < BOARD_WIDTH - 1; c++) {
					if (board[r][c] == board[r][c + 1]) {
						/* add the right element to the left (equivalent to
						 * multiplying left by 2 since they are equal) */
						board[r][c] *= 2;
						/* set the right element to 0 */
						board[r][c + 1] = 0;
						/* shift row left, starting from the next column */
						shift_row_left(r, c + 1);
					}
				}
			}
			break;
		case 'D':
			/* go through each column */
			c = BOARD_WIDTH;
			while (c-- > 0) {
				/* shift current column down, starting at the bottom row */
				shift_column_down(BOARD_HEIGHT - 1, c);
				/* go through each element of this row, and combine elements
				 * that are pushed into each other */
				for (r = BOARD_HEIGHT - 1; r > 0; r--) {
					if (board[r][c] == board[r - 1][c]) {
						/* add the upper element to the lower (equivalent to
						 * multiplying lower by 2 since they are equal) */
						board[r][c] *= 2;
						/* set the lower element to 0 */
						board[r - 1][c] = 0;
						/* shift column down, starting from the next row */
						shift_column_down(r - 1, c);
					}
				}
			}
			break;
		default:
			/* if the move doesn't match, do nothing */
			break;
	}
}

int main(void) {
	unsigned short int r, c, max, *results, results_length;
	char move;
	/* populate the board with the initial numbers */
	for (r = 0; r < BOARD_HEIGHT; r++) {
		for (c = 0; c < BOARD_WIDTH; c++) {
			if (1 != scanf("%hu ", &board[r][c])) {
				fprintf(stderr, "error reading element %hu on line %hu", c + 1,
						r + 1);
				exit(EXIT_FAILURE);
			}
		}
	}
	/* print the initial board */
	print_board();
	/* simulate each move */
	while (1 == scanf("%c ", &move)) {
		printf("%c\n", move);
		make_move(move);
		print_board();
	}
	/* determine the maximum value on the board after the final move */
	for (max = 0, r = 0; r < BOARD_HEIGHT; r++) {
		for (c = 0; c < BOARD_HEIGHT; c++) {
			if (board[r][c] > max) {
				max = board[r][c];
			}
		}
	}
	/* generate a histogram of the elements that are in the range
	 * [0, log2(max)] */
	results_length = custom_round(log2(max));
	results = malloc((results_length + 1)*sizeof *results);
	for (r = 0; r < BOARD_HEIGHT; r++) {
		for (c = 0; c < BOARD_HEIGHT; c++) {
			results[custom_round(log2(board[r][c]))]++;
		}
	}
	/* print the results */
	for (c = 1; c <= results_length; c++) {
			printf((c == results_length) ? "%hu\n" : "%hu ", results[c]);
	}
	/* clean up */
	free(results);
	return 0;
}
