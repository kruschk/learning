/* quest.c from "Creating an Adventure Game in the Terminal with ncurses" by Jim
 * Hall.
https://www.linuxjournal.com/content/creating-adventure-game-terminal-ncurses */

#include <curses.h>
#include <stdlib.h>

#define GRASS  	  ' '
#define EMPTY     '.'
#define WATER	  '~'
#define MOUNTAIN  '^'
#define PLAYER	  '*'

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

	/*clear();*/

	/* initialize the quest map */
	draw_map();

	/* start player at lower-left */
	y = LINES - 1;
	x = 0;

	do {
		/* by default, you get a blinking cursor - use it to indicate player */
		mvaddch(y, x, PLAYER);
		move(y, x);
		refresh();

		ch = getch();

		/* test inputted key and determine direction */
		switch (ch) {
			case KEY_UP:
			case 'w':
			case 'W':
				if ((y > 0) && is_move_okay(y - 1, x)) {
					mvaddch(y, x, EMPTY);
					y = y - 1;
				}
				break;
			case KEY_DOWN:
			case 's':
			case 'S':
				if ((y < LINES - 1) && is_move_okay(y + 1, x)) {
					mvaddch(y, x, EMPTY);
					y = y + 1;
				}
				break;
			case KEY_LEFT:
			case 'a':
			case 'A':
				if ((x > 0) && is_move_okay(y, x - 1)) {
					mvaddch(y, x, EMPTY);
					x = x - 1;
				}
				break;
			case KEY_RIGHT:
			case 'd':
			case 'D':
				if ((x < COLS - 1) && is_move_okay(y, x + 1)) {
					mvaddch(y, x, EMPTY);
					x = x + 1;
				}
				break;
		}
	}
	while ((ch != 'q') && (ch != 'Q'));

	endwin();

	exit(0);
}

int is_move_okay(int y, int x) {
	/* return true if the space is okay to move into */
	chtype testch = mvinch(y, x);
	return ((testch == GRASS) || (testch == EMPTY));
}

/* draw the quest map */
void draw_map(void) {
	int y, x;


	/* background */
	for (y = 0; y < LINES; y++) {
		mvhline(y, 0, GRASS, COLS);
	}

	/* mountains, and mountain path */
	for (x = COLS / 2; x < COLS * 3 / 4; x++) {
		mvvline(0, x, MOUNTAIN, LINES);
	}

	mvhline(LINES / 4, 0, GRASS, COLS);

	/* lake */
	for (y = 1; y < LINES / 2; y++) {
		mvhline(y, 1, WATER, COLS / 3);
	}
}
