#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 64
#define BOARD_ROWS 8
#define BOARD_COLS 8

enum piece {EMPTY = ' ', KING = 'K', QUEEN = 'Q'};
enum yesno {YES = 'Y', NO = 'N'};

/* queen_kills_king: check if the queen is placed such that she can kill the
 * king by moving horizontally, vertically, or diagonally */
enum yesno queen_kills_king(enum piece board[BOARD_ROWS][BOARD_COLS],
		int q_x, int q_y) {
	/* declare positional variables */
	int x, y;
	/* check left-to-right */
	y = q_y;
	for (x = 0; x < BOARD_COLS; x++) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* check bottom-to-top */
	x = q_x;
	for (y = 0; y < BOARD_ROWS; y++) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* check up-right from the queen */
	for (x = q_x+1, y = q_y+1; x < BOARD_COLS && y < BOARD_ROWS; x++, y++) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* check up-left from the queen */
	for (x = q_x - 1, y = q_y + 1; x >= 0 && y < BOARD_ROWS; x--, y++) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* check down-left from the queen */
	for (x = q_x - 1, y = q_y - 1; x >= 0 && y >= 0; x--, y--) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* check down-right from the queen */
	for (x = q_x + 1, y = q_y - 1; x < BOARD_COLS && y >= 0; x++, y--) {
		if (board[y][x] == KING) {
			return YES;
		}
	}
	/* queen can't kill the king */
	return NO;
}

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get the number of cases from the first line */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		enum piece board[BOARD_ROWS][BOARD_COLS], answer;
		int king_x, king_y, queen_x, queen_y;
		size_t j, k;
		/* get the position of the king and queen */
		fgets(line, MAX_LINE, stdin);
		king_x = line[0] - 'a';
		king_y = line[1] - '1';
		queen_x = line[3] - 'a';
		queen_y = line[4] - '1';
		/* clear the board */
		for (j = 0; j < BOARD_ROWS; j++) {
			for (k = 0; k < BOARD_COLS; k++) {
				board[j][k] = EMPTY;
			}
		}
		/* place the king and queen */
		board[king_y][king_x] = KING;
		board[queen_y][queen_x] = QUEEN;
		/* determine the answer */
		answer = queen_kills_king(board, queen_x, queen_y);
		/* print result */
		printf((i == n_cases - 1) ? "%c\n" : "%c ", answer);
	}
	return 0;
}
