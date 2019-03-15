#include <stdio.h>
#include <ctype.h>

int getint(int *pn);
int getch(void);
void ungetch(int c);

int main(void) {
	int i, n;
	while ((i = getint(&n)) != EOF && i != 0) {
		printf("%d\n", n);
	}

	return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch())) { /* skip white space */
		;
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		char temp = c;
		if (!isdigit(c = getch())) {
			ungetch(c);
			ungetch(temp);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * (*pn) + (c - '0');
	}
	*pn *= sign;
	if (c != EOF) {
		ungetch(c);
	}

	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
