#include "keyword_count.h"
#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int c);
void skip_whitespace(int *c);

/* get next word or character from input, doesn't handle escape sequences */
int getword(char *word, int lim) {
	int c;
	char *w = word;

	/* ignore whitespace */
	skip_whitespace(&c);
	/* ignore preprocessor directives (the entire line is ignored, doesn't
	 * support {'\','\n'} to continue a directive on the next line) */
	if (c == '#') {
		while ((c = getch()) != '\n' && c != EOF) {
			;
		}
		if (c == EOF) {
			return c;
		}
		else {
			*w = '\0';
			return word[0];
		}
	}
	/* ignore quoted strings (escape sequences won't be recognized) */
	if (c == '\"') {
		while ((c = getch()) != '\"' && c != EOF) {
			;
		}
		if (c == EOF) {
			return c;
		}
		else {
			*w = '\0';
			return word[0];
		}
	}
	/* ignore comments (doesn't support nested comments) */
	if (c == '/') {
		if ((c = getchar()) == '*') {
			while ((c = getchar()) != EOF) {
				if (c == '*') {
					if ((c = getchar()) == '/') {
						break;
					}
					else {
						ungetch(c);
					}
				}
			}
			if (c == EOF) {
				return c;
			}
			else {
				*w = '\0';
				return word[0];
			}
		}
		else {
			ungetch(c);
			c = '/';
		}
	}
	if (c != EOF) {
		*w++ = c;
	}
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	/* copy word to word[] */
	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && (*w != '_')) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

void skip_whitespace(int *c) {
	while (isspace(*c = getch())) {
		;
	}
}
