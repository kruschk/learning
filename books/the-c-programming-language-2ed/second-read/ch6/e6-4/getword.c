#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

static int getch(void);
static void ungetch(int c);

/* get next word or character from input */
int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (isspace(c = getch())) {
		;
	}
	if (c != EOF) {
		*w++ = c;
	}
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

/* get a (possibly pushed back) character */
static int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
static void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
