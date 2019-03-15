#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8
#define MAX_LINE 1024

/* boolean values */
enum boolean {FALSE, TRUE};

/* allowable chess pieces */
enum pieces {NA = '-', /* empty */
	WP = 'P', WR = 'R', WN = 'N', WB = 'B', WQ = 'Q', WK = 'K',
	BP = 'p', BR = 'r', BN = 'n', BB = 'b', BQ = 'q', BK = 'k'};

/* point on the board */
struct coords {
	short int x;
	short int y;
};

/* print_board: print the chess board passed in as input */
void print_board(enum pieces board[BOARD_HEIGHT][BOARD_WIDTH]) {
	unsigned short int i = BOARD_HEIGHT;
	unsigned short int j = 0;
	printf(" +--------+\n");
	for (i = BOARD_HEIGHT; i > 0; i--) {
		printf("%hu|", i);
		for (j = 0; j < BOARD_WIDTH; j++) {
			printf("%c", board[i-1][j]);
		}
		printf("|\n");
	}
	printf(" +--------+\n  abcdefgh\n");
	return;
}

/* is_legal_move: checks if a given move, from start to end, is legal */
enum boolean is_legal_move(enum pieces board[BOARD_HEIGHT][BOARD_WIDTH],
		const struct coords *start, const struct coords *end) {
	/* only need to check pawn moves, so assume any other pieces will be moved
	 * legally */
	enum pieces moving_piece = board[start->y][start->x];
	enum pieces target_piece = board[end->y][end->x];
	/* if the move doesn't start on the board or it doesn't end on the board */
	if (       BOARD_WIDTH <= start->x || BOARD_HEIGHT <= start->y
			|| BOARD_WIDTH <= end->x   || BOARD_HEIGHT <= end->y) {
		return FALSE;
	}
	/* the moving piece can't be empty */
	else if (NA == moving_piece) {
		return FALSE;
	}
	/* if the moving piece isn't a pawn, assume the move is valid */
	else if (WP != moving_piece && BP != moving_piece) {
		return TRUE;
	}
	/* normal move, destination is empty and pawn moves up or down and stays in
	 * the same column */
	else if (NA == target_piece && end->x == start->x) {
		/* for a white piece: */
		if (WP == moving_piece) {
			/* a white piece may always move up one cell, given that it's empty */
			if (end->y == start->y + 1) {
				return TRUE;
			}
			/* a white piece in the starting row (row 2, but index 2-1 = 1) can
			 * skip over a space and land on the second... */
			else if (end->y == start->y + 2 && start->y == 2 - 1) {
				/* as long as the skipped space is empty */
				if (board[start->y + 1][start->x] == NA) {
					return TRUE;
				}
			}
		}
		else if (BP == moving_piece) {
			/* a black piece may always move down one cell, given that it's empty */
			if (end->y == start->y - 1) {
				return TRUE;
			}
			/* a black piece in the starting row (row 7, but index 7-1 = 6) can
			 * skip over a space and land on the second... */
			else if (end->y == start->y - 2 && start->y == 7 - 1) {
				/* as long as the skipped space is empty */
				if (board[start->y - 1][start->x] == NA) {
					return TRUE;
				}
			}
		}
	}
	/* capture, pawn must move diagonally */
	else if (end->x == start->x - 1 || end->x == start->x + 1) {
		/* a white piece must move upward */
		if (WP == moving_piece && end->y == start->y + 1) {
			/* a white piece can only capture a black piece, and the target
			 * space cannot be empty */
			switch (target_piece) {
				case BP:
				case BR:
				case BN:
				case BB:
				case BQ:
				case BK:
					return TRUE;
					break;
				default:
					break;
			}
		}
		/* a black piece must move downward */
		else if (BP == moving_piece && end->y == start->y - 1) {
			/* a black piece can only capture a white piece, and the target
			 * space cannot be empty */
			switch (target_piece) {
				case WP:
				case WR:
				case WN:
				case WB:
				case WQ:
				case WK:
					return TRUE;
					break;
				default:
					break;
			}
		}
	}
	return FALSE;
}

/* update_position: update the position of a piece on the board. May only be
 * used when is_legal_move returns true for the same parameters. */
void update_position(enum pieces board[BOARD_HEIGHT][BOARD_WIDTH],
		const struct coords *start, const struct coords *end) {
	board[end->y][end->x] = board[start->y][start->x];
	board[start->y][start->x] = NA;
	return;
}


int main(void) {
	unsigned short int cases, i, *bad_moves;
	enum pieces starting_board[BOARD_HEIGHT][BOARD_WIDTH] = {
		{WR, WN, WB, WQ, WK, WB, WN, WR},
		{WP, WP, WP, WP, WP, WP, WP, WP},
		{NA, NA, NA, NA, NA, NA, NA, NA},
		{NA, NA, NA, NA, NA, NA, NA, NA},
		{NA, NA, NA, NA, NA, NA, NA, NA},
		{NA, NA, NA, NA, NA, NA, NA, NA},
		{BP, BP, BP, BP, BP, BP, BP, BP},
		{BR, BN, BB, BQ, BK, BB, BN, BR}
	};
	/* get the number of cases from input */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error reading the number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memory to store the results; 0 bad moves for a case indicates
	 * the game was played with no illegal moves, while a number indicates
	 * which move in a given game was illegal */
	bad_moves = malloc(cases*sizeof *bad_moves);
	/* play the game for each case */
	for (i = 0; i < cases; i++) {
		enum pieces board[BOARD_HEIGHT][BOARD_WIDTH];
		char line[MAX_LINE];
		unsigned short j, move;
		/* get next line, which contains the list of moves */
		if (NULL == fgets(line, MAX_LINE, stdin) && 0 != feof(stdin)) {
			fprintf(stderr, "error reading line %hu/%hu", i + 1, cases);
			exit(EXIT_FAILURE);
		}
		/* copy the original board so we're always starting fresh */
		memcpy(board, starting_board, sizeof starting_board);
		/* make the moves listed in each line */
		for (j = 0, move = 1; '\n' != line[j] && '\0' != line[j]; j++, move++) {
			struct coords start, end;
			/* print the board if we want to watch the magic happen */
			/*print_board(board);*/
			/* get the next move from the line buffer */
			while (isspace(line[j])) {
				j++;
			}
			start.x = line[j++] - 'a';
			start.y = line[j++] - '1';
			end.x = line[j++] - 'a';
			end.y = line[j++] - '1';
			/* print out each move as it's about to be made */
			/*printf("(%c, %c)->(%c, %c)\n", start.x + 'a', start.y + '1',
					end.x + 'a', end.y + '1');*/
			/* check if the move is allowable */
			bad_moves[i] = 0; /* assume the move is good */
			if (is_legal_move(board, &start, &end)) {
				/* update the position if it is good */
				update_position(board, &start, &end);
			}
			else {
				/* this move was bad, save it and go to the next case */
				bad_moves[i] = move;
				break;
			}
		}
	}
	/* print the results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%hu\n" : "%hu ", bad_moves[i]);
	}
	/* free memory */
	free(bad_moves);
	return 0;
}
