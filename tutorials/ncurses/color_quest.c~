/* colour_quest.c from "Programming in Color with ncurses" by Jim Hall.
 * https://www.linuxjournal.com/content/programming-color-ncurses */

#include <curses.h>
#include <stdlib.h>

#define GRASS  	  ' '
#define EMPTY     '.'
#define WATER	  '~'
#define MOUNTAIN  '^'
#define PLAYER	  '*'

#define GRASS_PAIR 1
#define EMPTY_PAIR 1
#define WATER_PAIR 2
#define MOUNTAIN_PAIR 3
#define PLAYER_PAIR 4

int is_move_okay(int y, int x);
void draw_map(void);

int main(void) {
	int y, x;
	int ch;

	/* initialize curses */
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();

	/* initialize colours */
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(EXIT_FAILURE);
	}

	start_color();
	init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
	init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
	init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);
	init_pair(PLAYER_PAIR, COLOR_RED, COLOR_MAGENTA);

	clear();

	/* initialize the quest map */
	draw_map();

	/* start player at lower-left */
	y = LINES - 1;
	x = 0;

	do {
		/* by default, you get a blinking cursor - use it to indicate player */
		attron(COLOR_PAIR(PLAYER_PAIR));
		mvaddch(y, x, PLAYER);
		attroff(COLOR_PAIR(PLAYER_PAIR));
		move(y, x);
		refresh();

		ch = getch();

		/* test inputted key and determine direction */
		switch (ch) {
			case KEY_UP:
			case 'w':
			case 'W':
				if ((y > 0) && is_move_okay(y - 1, x)) {
					attron(COLOR_PAIR(EMPTY_PAIR));
					mvaddch(y, x, EMPTY);
					attroff(COLOR_PAIR(EMPTY_PAIR));
					y = y - 1;
				}
				break;
			case KEY_DOWN:
			case 's':
			case 'S':
				if ((y < LINES - 1) && is_move_okay(y + 1, x)) {
					attron(COLOR_PAIR(EMPTY_PAIR));
					mvaddch(y, x, EMPTY);
					attroff(COLOR_PAIR(EMPTY_PAIR));
					y = y + 1;
				}
				break;
			case KEY_LEFT:
			case 'a':
			case 'A':
				if ((x > 0) && is_move_okay(y, x - 1)) {
					attron(COLOR_PAIR(EMPTY_PAIR));
					mvaddch(y, x, EMPTY);
					attroff(COLOR_PAIR(EMPTY_PAIR));
					x = x - 1;
				}
				break;
			case KEY_RIGHT:
			case 'd':
			case 'D':
				if ((x < COLS - 1) && is_move_okay(y, x + 1)) {
					attron(COLOR_PAIR(EMPTY_PAIR));
					mvaddch(y, x, EMPTY);
					attroff(COLOR_PAIR(EMPTY_PAIR));
					x = x + 1;
				}
				break;
		}
	}
	while ((ch != 'q') && (ch != 'Q'));

	endwin();

	exit(EXIT_SUCCESS);
}

int is_move_okay(int y, int x) {
	/* return true if the space is okay to move into */
	chtype testch = mvinch(y, x) & A_CHARTEXT;
	return ((testch == GRASS) || (testch == EMPTY));
}

/* draw the quest map */
void draw_map(void) {
	int y, x;

	/* background */
	attron(COLOR_PAIR(GRASS_PAIR));
	for (y = 0; y < LINES; y++) {
		mvhline(y, 0, GRASS, COLS);
	}
	attroff(COLOR_PAIR(GRASS_PAIR));

	/* mountains */
	attron(COLOR_PAIR(MOUNTAIN_PAIR));
	for (x = COLS / 2; x < COLS * 3 / 4; x++) {
		mvvline(0, x, MOUNTAIN, LINES);
	}
	attroff(COLOR_PAIR(MOUNTAIN_PAIR));

	/* draw path through the mountains */
	attron(COLOR_PAIR(GRASS_PAIR));
	mvhline(LINES / 4, 0, GRASS, COLS);
	attroff(COLOR_PAIR(GRASS_PAIR));

	/* lake */
	attron(COLOR_PAIR(WATER_PAIR));
	for (y = 1; y < LINES / 2; y++) {
		mvhline(y, 1, WATER, COLS / 3);
	}
	attroff(COLOR_PAIR(WATER_PAIR));
}
