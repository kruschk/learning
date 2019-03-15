#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define ROWS 3
#define COLUMNS 3

enum boolean {TRUE, FALSE};

/* draw_board: draws board to terminal */
/*
void draw_board(char board[]) {
	size_t i;
	printf("---\n");
	for (i = 1; i < 10; i++) {
		putchar(board[i]);
		if (i % 3 == 0) {
			putchar('\n');
		}
	}
	return;
}
*/

/* game_over: check the board to see if character xo won */
enum boolean game_over(char board[], char xo) {
	/* rows */
	if ((board[1] == xo && board[2] == xo && board[3] == xo)
			|| (board[4] == xo && board[5] == xo && board[6] == xo)
			|| (board[7] == xo && board[8] == xo && board[9] == xo)) {
		return TRUE;
	}
	/* columns */
	else if ((board[1] == xo && board[4] == xo && board[7] == xo)
			|| (board[2] == xo && board[5] == xo && board[8] == xo)
			|| (board[3] == xo && board[6] == xo && board[9] == xo)) {
		return TRUE;
	}
	/* diagonals */
	else if ((board[1] == xo && board[5] == xo && board[9] == xo)
			|| (board[3] == xo && board[5] == xo && board[7] == xo)) {
		return TRUE;
	}
	/* if none of the above are true, game isn't over yet */
	else {
		return FALSE;
	}
}

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get number of tests */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* for each test case, simulate the game and determine on which move
	 * someone wins */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		/* board index/position mapping (0 is unused):
		 * 1|2|3
		 * -+-+-
		 * 4|5|6
		 * -+-+-
		 * 7|8|9
		 */
		char board[10] = {0}, player, *line_p;
		size_t j, move_number, move;
		/* set the board to blank */
		for (j = 1; j < 10; j++) {
			board[j] = ' ';
		}
		/* get the moves from stdin */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* play the game */
		player = 'o';
		move_number = 0;
		do {
			/* toggle player */
			if (player == 'o') {
				player = 'x';
			}
			else {
				player = 'o';
			}
			/* make next move */
			move = strtoul(line_p, &line_p, 10);
			board[move] = player;
			/* increment the move number */
			move_number++;
		}
		while (game_over(board, player) == FALSE && move_number <= 9);
		/* print a zero if there's no winner */
		if (move_number > 9) {
			printf((i == n_cases - 1) ? "0\n" : "0 ");
		}
		/* print the ending move number */
		else {
			printf((i == n_cases - 1) ? "%lu\n" : "%lu ", move_number);
		}
	}
	return 0;
}
