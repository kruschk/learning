#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define BOARD_ROWS 13
#define BOARD_COLS 21

enum board_contents {EMPTY = '-', SNAKE = 'X', FOOD = '$'};
enum direction {NONE, RIGHT = 'R', UP = 'U', LEFT = 'L', DOWN = 'D'};
enum game_status {GAME_OVER, GAME_CONTINUE};

static char board[BOARD_ROWS][BOARD_COLS];

/* The head is the head of the snake, and will connect to the next body part
 * behind it. The tail is the last element of the snake, and will connect to
 * the next body part ahead of it. */
static struct {
	unsigned int length;
	enum direction dir;
	struct linked_coord *head;
	struct linked_coord *tail;
} snake;

/* The linked coordinates represent the body of the snake. Each body part will
 * point to the body part ahead and behind it. In the case of the head and
 * tail, the ahead pointer will be NULL and the behind pointer will be NULL,
 * respectively. */
struct linked_coord {
	unsigned int x;
	unsigned int y;
	struct linked_coord *ahead;
	struct linked_coord *behind;
};

/* print the board */
void print_board(void) {
	unsigned int i, j;
	putchar('+');
	for (j = 0; j < BOARD_COLS; j++) {
		putchar('-');
	}
	putchar('+');
	putchar('\n');
	for (i = 0; i < BOARD_ROWS; i++) {
		putchar('|');
		for (j = 0; j < BOARD_COLS; j++) {
			putchar(board[i][j]);
		}
		putchar('|');
		putchar('\n');
	}
	putchar('+');
	for (j = 0; j < BOARD_COLS; j++) {
		putchar('-');
	}
	putchar('+');
	putchar('\n');
	return;
}

/* move the snake to the new coordinates by placing the tail there and marking
 * it as the new head */
void move_snake(unsigned int new_x, unsigned int new_y) {
	struct linked_coord *old_head = snake.head;
	struct linked_coord *old_tail = snake.tail;
	struct linked_coord *new_head = snake.tail;
	struct linked_coord *new_tail = snake.tail->ahead;
	/* update the links between body parts */
	new_head->behind = old_head;
	new_head->ahead = NULL;
	old_head->ahead = new_head;
	new_tail->behind = NULL;
	/* update the board at the old tail position */
	board[old_tail->y][old_tail->x] = EMPTY;
	/* update the coordinates of the new head (the only part that moves) */
	new_head->y = new_y;
	new_head->x = new_x;
	/* update the board with the new head position */
	board[new_head->y][new_head->x] = SNAKE;
	/* update the snake's head and tail */
	snake.head = new_head;
	snake.tail = new_tail;
	return;
}

/* snake grows by adding a new head to the new coordinates and marking it as
 * the new head */
void grow_snake(unsigned int new_x, unsigned int new_y) {
	/* save the old head and allocate memory for a new one */
	struct linked_coord *old_head = snake.head;
	struct linked_coord *new_head = malloc(sizeof *new_head);
	/* link the old head to the new one */
	old_head->ahead = new_head;
	/* initialize the new head */
	new_head->x = new_x;
	new_head->y = new_y;
	new_head->ahead = NULL;
	new_head->behind = old_head;
	/* update the board */
	board[new_head->y][new_head->x] = SNAKE;
	/* update the snake */
	snake.head = new_head;
	snake.length++;
	return;
}

/* advance the snake one unit in whichever direction it is headed */
enum game_status advance_snake(void) {
	enum board_contents contents;
	unsigned int new_x;
	unsigned int new_y;
	unsigned int s_x = snake.head->x;
	unsigned int s_y = snake.head->y;
	enum game_status gs = GAME_CONTINUE; /* assume game continues */
	switch (snake.dir) {
		case RIGHT:
			/* %BOARD_COLS because right edge of board wraps to the left */
			new_x = (s_x + 1)%BOARD_COLS;
			contents = board[s_y][new_x];
			/* snake moves freely to an empty cell */
			if (EMPTY == contents) {
				move_snake(new_x, s_y);
			}
			/* snake dies if it collides with itself */
			else if (SNAKE == contents) {
				/* snake dies */
				move_snake(new_x, s_y);
				gs = GAME_OVER;
			}
			/* snake grows one unit if it eats some food */
			else if (FOOD == contents) {
				grow_snake(new_x, s_y);
			}
			break;
		case UP:
			if (s_y == 0) {
				/* upper edge of board wraps to bottom */
				new_y = BOARD_ROWS - 1;
			}
			else {
				new_y = s_y - 1;
			}
			contents = board[new_y][s_x];
			if (EMPTY == contents) {
				move_snake(s_x, new_y);
			}
			else if (SNAKE == contents) {
				/* snake dies */
				move_snake(s_x, new_y);
				gs = GAME_OVER;
			}
			else if (FOOD == contents) {
				grow_snake(s_x, new_y);
			}
			break;
		case LEFT:
			if (s_x == 0) {
				/* left edge of board wraps to right */
				new_x = BOARD_COLS - 1;
			}
			else {
				new_x = s_x - 1;
			}
			contents = board[s_y][new_x];
			if (EMPTY == contents) {
				move_snake(new_x, s_y);
			}
			else if (SNAKE == contents) {
				/* snake dies */
				move_snake(new_x, s_y);
				gs = GAME_OVER;
			}
			else if (FOOD == contents) {
				grow_snake(new_x, s_y);
			}
			break;
		case DOWN:
			/* %BOARD_ROWS because bottom edge of board wraps to the top */
			new_y = (s_y + 1)%BOARD_ROWS;
			contents = board[new_y][s_x];
			if (EMPTY == contents) {
				move_snake(s_x, new_y);
			}
			else if (SNAKE == contents) {
				/* snake dies */
				move_snake(s_x, new_y);
				gs = GAME_OVER;
			}
			else if (FOOD == contents) {
				grow_snake(s_x, new_y);
			}
			break;
		default:
			gs = GAME_OVER;
			break;
	}
	return gs;
}

/* initialize the snake */
void snake_init(void) {
	/* initialize each of the snake's body parts */
	struct linked_coord *head, *mid, *tail;
	/* allocate memory */
	head = malloc(sizeof *head);
	mid = malloc(sizeof *mid);
	tail = malloc(sizeof *tail);
	/* head */
	head->x = 2;
	head->y = 0;
	head->ahead = NULL;
	head->behind = mid;
	/* midsection */
	mid->x = 1;
	mid->y = 0;
	mid->ahead = head;
	mid->behind = tail;
	/* tail */
	tail->x = 0;
	tail->y = 0;
	tail->ahead = mid;
	tail->behind = NULL;
	/* the initial snake */
	snake.length = 3;
	snake.dir = RIGHT;
	snake.head = head;
	snake.tail = tail;
	return;
}

/* clean up all the malloc'd body parts of the snake */
void snake_clear(void) {
	struct linked_coord *current_body_part = snake.head;
	struct linked_coord *next_body_part = NULL;
	unsigned int i;
	for (i = 0; i < snake.length; i++) {
		next_body_part = current_body_part->behind;
		free(current_body_part);
		current_body_part = next_body_part;
	}
	return;
}

int main(void) {
	int c;
	char direction;
	unsigned int i, j, repetitions, clock = 0;
	enum game_status gs = GAME_CONTINUE;
	/* populate the initial board */
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			while (isspace(c = getchar())) {
				;
			}
			if (EOF == c) {
				fprintf(stderr, "error reading the initial board\n");
				exit(EXIT_FAILURE);
			}
			board[i][j] = c;
		}
	}
	/* print the initial board */
	print_board();
	/* initialize the snake (hard-coded to reflect the initial board
	 * positioning (top-left, 3 units long, initially headed right)) */
	snake_init();
	/* get the number of repetitions */
	if (1 != scanf("%u ", &repetitions)) {
		fprintf(stderr, "error reading the first number of repetitions\n");
		exit(EXIT_FAILURE);
	}
	/* advance the game one clock tick for each repetition */
	while (repetitions-- > 0 && gs != GAME_OVER) {
		gs = advance_snake();
		clock++;
		print_board();
	}
	/* get the new directions and repetitions from input */
	while (2 == scanf("%c %u ", &direction, &repetitions) && gs != GAME_OVER) {
		/* set the snake's new direction */
		snake.dir = direction;
		/* advance the game one clock tick for each repetition */
		while (repetitions-- > 0 && gs != GAME_OVER) {
			gs = advance_snake();
			clock++;
			print_board();
		}
	}
	/* print the results */
	printf("%u %u %u\n", snake.head->x, snake.head->y, clock);
	/* clean up */
	snake_clear();
	return 0;
}
