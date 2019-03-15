/******************************************************************************
 * This program strips away comments from a source file. It works fairly well.
 * 
 * Input:
 * -A C source code file.
 *
 * Output:
 * -The same source file, stripped of comments.
 *
 * Features:
 * -Strips comments, unless they're enclosed by double quotes (desired
 *  behaviour).
 * -Handles nested comments, which technically aren't allowed by the standard.
 *
 * Known bugs:
 * -Doesn't handle escaped quote characters within double quotes, which it
 *  should. This is most likely because quoted_string() doesn't recognize
 *  escaped characters.
 *****************************************************************************/
#include <stdio.h>

int parse(void);
int comment(void);
int quoted_string(int character);

int main(void) {
	while (parse() >= 0) {
		;
	}

	return 0;
}

/******************************************************************************
 * parse: copy characters over until a token pattern is reached
 *****************************************************************************/
int parse(void) {
	int current;
	int next;
	while ((current = getchar()) != EOF) {
		switch (current) {
			case '/':
				if ((next = getchar()) == EOF) {
					current = next;
				}
				else if (next == '*') {
					comment();
				}
				else {
					putchar(current);
					putchar(next);
				}
				break;
			case '\"':
				quoted_string(current);
				break;
			case '\\':
				if ((next = getchar()) == EOF) {
					current = next;
				}
				else if (next == '\"') {
					putchar(current);
					putchar(next);
				}
				else {
					putchar(current);
					putchar(next);
				}			
				break;
			default:
				putchar(current);
				break;
		}
	}

	/*
	while ((current = getchar()) != EOF) {
		if (current == '/') {
			if ((next = getchar()) == EOF) {
				current = next;
				break;
			}
			else if (next == '*') {
				comment();
				break;
			}
			else {
				putchar(current);
				putchar(next);
			}
		}
		else if (current == '\"') {
			quoted_string(current);
		}
		else if (current == '\\') {
			if ((next = getchar()) == EOF) {
				current = next;
				break;
			}
			else if (next == '\"') {
				putchar(current);
				putchar(next);
				break;
			}
			else {
				putchar(current);
				putchar(next);
			}
		}
		else {
			putchar(current);
		}
	}
	*/
	
	return current;
}

/******************************************************************************
 * comment: ignore all characters until the end pattern is reached
 *****************************************************************************/
int comment(void) {
	int current;
	int next;
	while ((current = getchar()) != EOF) {
		/* do nothing until end of comment is reached */
		if (current == '*') {
			if ((next = getchar()) == EOF) {
				current = next;
				break;
			}
			else if (next == '/') {
				break;
			}
		}

		/* allow for nested comments */
		if (current == '/') {
			if ((next = getchar()) == EOF) {
				current = next;
				break;
			}
			else if (next == '*') {
				comment();
			}
		}
	}

	return current;
}

/******************************************************************************
 * quoted_string: handle quoted strings, in which comments are allowed to
 * appear
 *****************************************************************************/
int quoted_string(const int character) {
	int current = character;
	putchar(current);
	while (((current = getchar()) != EOF) && (current != character)) {
		putchar(current);
	}
	if (current == character) {
		putchar(current);
	}

	return current;
}
