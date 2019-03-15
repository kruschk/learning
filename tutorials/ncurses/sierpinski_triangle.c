/* qsierpinski_triangle.c from "Getting Started with ncurses" by Jim Hall.
 * https://www.linuxjournal.com/content/getting-started-ncurses
 * gcc -std=c89 -pedantic -Wall -Wextra -Werror -o sierpinski_triangle \
 *     sierpinski_triangle.c -lcurses */

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/random.h>

#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define ITERMAX 10000

unsigned int getrandom_int(void) {
	unsigned int buf = 0;
	size_t buflen = sizeof buf;
	syscall(SYS_getrandom, &buf, buflen, 0);
	return buf;
}

int main(void) {
	long iter;
	int yi, xi;
	int y[3], x[3];
	int index;
	int maxlines, maxcols;

	/* initialize curses */
	initscr();
	cbreak();
	noecho();

	clear();

	/* initialize triangle */
	maxlines = LINES - 1;
	maxcols = COLS - 1;

	y[0] = 0;
	x[0] = 0;

	y[1] = maxlines;
	x[1] = maxcols / 2; 

	y[2] = 0;
	x[2] = maxcols;

	mvaddch(y[0], x[0], '0');
	mvaddch(y[1], x[1], '1');
	mvaddch(y[2], x[2], '2');

	/* initialize yi, xi with random values */
	yi = getrandom_int() % maxlines;
	xi = getrandom_int() % maxcols;

	mvaddch(yi, xi, '.');

	/* iterate the triangle */
	for (iter = 0; iter < ITERMAX; iter++) {
		/* uncomment to watch the magic! */
		/*const struct timespec delay = {0, 250000000};
		nanosleep(&delay, NULL);*/
		index = getrandom_int() % 3;

		yi = (yi + y[index]) / 2;
		xi = (xi + x[index]) / 2;

		mvaddch(yi, xi, '*');
		refresh();
	}

	/* done */
	mvaddstr(maxlines, 0, "Press any key to quit");

	refresh();

	getch();
	endwin();

	exit(EXIT_SUCCESS);
}
