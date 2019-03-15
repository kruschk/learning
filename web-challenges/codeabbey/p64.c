#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define WALL '0'
#define PATH '1'

/* get the offset of a 2D array stored as a 1D array, from the desired row and
 * column */
#define OFFSET(cols, r, c)\
	((r)*(cols) + (c))

enum direction {NONE = 'N', RIGHT = 'R', UP = 'U', LEFT = 'L', DOWN = 'D'};
enum boolean {FALSE, TRUE};

/* stack variables */
static enum direction *stack;
static enum direction *p;
static ptrdiff_t stack_size = 128;

/* push: push an element onto the stack */
void push(enum direction dir) {
	/* reallocate memory if the stack overflows */
	ptrdiff_t index = p - stack;
	if (index + 1 >= stack_size) {
		stack_size *= 2;
		stack = realloc(stack, stack_size*(sizeof *stack));
		p = stack + index;
	}
	/* add the element to the stack */
	*p = dir;
	/* point to the next element */
	p++;
	return;
}

/* pop: pop a value off the stack */
enum direction pop(void) {
	/* if there's anything on the stack */
	if (p > stack) {
		/* point to the next element */
		p--;
		/* return the element */
		return *p;
	}
	else {
		/* return NONE if there's nothing left */
		return NONE;
	}
}

/* print_board: print the board */
void print_board(char *board, unsigned short int rows,
		unsigned short int cols) {
	unsigned char r, c;
	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			putchar(board[OFFSET(cols, r, c)]);
		}
		putchar('\n');
	}
}

/* find_path: find a path from the starting point to the goal */
enum boolean find_path(char *board, unsigned short int rows, unsigned short int cols,
		unsigned short int r, unsigned short int c, enum direction last_dir) {
	/* goal reached */
	if (r == 0 && c == 0) {
		return TRUE;
	}
	/* go right if it's on the board, the point is a PATH, and the last
	 * direction wasn't right */
	if (c + 1 < cols && board[OFFSET(cols, r, c + 1)] == PATH
			&& last_dir != LEFT) {
		if (find_path(board, rows, cols, r, c + 1, RIGHT)) {
			push(RIGHT);
			return TRUE;
		}
	}
	/* go up if it's on the board, the point is a PATH, and the last direction
	 * wasn't right */
	if (r - 1 >= 0 && board[OFFSET(cols, r - 1, c)] == PATH
			&& last_dir != DOWN) {
		if (find_path(board, rows, cols, r - 1, c, UP)) {
			push(UP);
			return TRUE;
		}
	}
	/* go left if it's on the board, the point is a PATH, and the last
	 * direction wasn't right */
	if (c - 1 >= 0 && board[OFFSET(cols, r, c - 1)] == PATH
			&& last_dir != RIGHT) {
		if (find_path(board, rows, cols, r, c - 1, LEFT)) {
			push(LEFT);
			return TRUE;
		}
	}
	/* go down if it's on the board, the point is a PATH, and the last
	 * direction wasn't right */
	if (r + 1 < rows && board[OFFSET(cols, r + 1, c)] == PATH
			&& last_dir != UP) {
		if (find_path(board, rows, cols, r + 1, c, DOWN)) {
			push(DOWN);
			return TRUE;
		}
	}
	return FALSE;
}

/* print_directions: print the directions to the goal in the desired format */
void print_directions(void) {
	/* get the next value on the stack */
	enum direction next_dir = pop();
	size_t count = 0;
	/* while we haven't reached the end of the stack */
	while (next_dir != NONE) {
		/* save the last direction */
		enum direction last_dir = next_dir;
		/* while the next direction matches the next one, increment the count */
		while (next_dir == last_dir) {
			count++;
			next_dir = pop();
		}
		/* print the result */
		printf("%lu%c", count, last_dir);
		/* get the next value and set count to 1 */
		next_dir = pop();
		count = 1;
	}
	return;
}

int main(void) {
	unsigned short int rows = 0, cols = 0;
	unsigned short int c, r;
	char *board;
	/*enum direction dir;*/
	/* get the number of rows and columns */
	scanf("%hu %hu\n", &cols, &rows);
	/* allocate memory for the board */
	board = malloc(rows*cols*(sizeof *board));
	/* allocate memory for the stack */
	stack = malloc(stack_size*(sizeof *stack));
	p = stack;
	/* get the board */
	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			board[OFFSET(cols, r, c)] = getchar(); /* get the next character */
		}
		getchar(); /* discard newline */
	}
	/* print the board */
	print_board(board, rows, cols);
	/* top-right */
	find_path(board, rows, cols, 0, cols - 1, NONE);
	print_directions();
	putchar(' ');
	/* bottom-left */
	find_path(board, rows, cols, rows - 1, 0, NONE);
	print_directions();
	putchar(' ');
	/* bottom-right */
	find_path(board, rows, cols, rows - 1, cols - 1, NONE);
	print_directions();
	putchar('\n');
	/* free memory */
	free(board);
	free(stack);
	return 0;
}
