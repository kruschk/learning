#include "keyword_count.h"
#include <ctype.h>
#include <stdio.h>

/* get next word or character from input */
int getword(char *word, int lim) {
	int c;
	int getch(void);
	void ungetch(int c);
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
