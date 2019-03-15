/* This program doesn't work yet. */

#include <stdio.h>

enum token_types {NORMAL = 1, COMMENT_OPEN, COMMENT_CLOSE, DOUBLE_QUOTE,
                  ESCAPED_CHARACTER};

struct token get_token(void);
int call_function(struct token token);
int comment2(void);
int quoted_string2(void);

struct token {
	int character;
	int type;
};

int main(void) {
	struct token token;
	while ((token = get_token()).character >= 0) {
		call_function(token);
	}

	return 0;
}

/******************************************************************************
 * get_token: get a token from STDIN. A token may be a comment, a double quote,
 * or an escaped character.
 *****************************************************************************/
struct token get_token(void) {
	struct token token;
	int current;
	int next;
	while ((current = getchar()) != EOF) {
		switch (current) {
			case '/':
				next = getchar();
				if (next == EOF) {
					token.character = next; /* the '/' won't get printed */
					token.type = NORMAL;
					return token;
				}
				else if (next == '*') {
					token.type = COMMENT_OPEN;
				}
				else {
					token.type = NORMAL;
				}
				token.character = next;
				break;
			case '\"':
				token.character = next;
				token.type = DOUBLE_QUOTE;
				break;
			case '\\':
				next = getchar();
				if (next == EOF) {
					token.character = next; /* the '\' won't get printed */
					token.type = NORMAL;
					return token;
				}
				else if (next == '\"') {
					token.type = ESCAPED_CHARACTER;
				}
				else {
					token.type = NORMAL;
				}
				token.character = next;
				break;
			default:
				token.character = current;
				token.type = NORMAL;
				break;
		}
	}
	
	return token;
}


/******************************************************************************
 * call_function: takes a token and decides which function to call
 *****************************************************************************/
int call_function(struct token token) {
	if (token.type == NORMAL) {
		putchar(token.character);
	}
	else if (token.type == COMMENT_OPEN) {
		comment2();
	}
	else if (token.type == DOUBLE_QUOTE) {
		quoted_string2();
	}
	else if (token.type == ESCAPED_CHARACTER) {
		putchar(token.character);
	}
	else {
		printf("something's odd in call_function");
	}

	return 0;
}

/******************************************************************************
 * comment2: ignore all characters until the end pattern is reached
 *****************************************************************************/
int comment2(void) {
	struct token token;
	while ((token = get_token()).character != EOF) {
		if (token.type == COMMENT_CLOSE) {
			break;
		}
		else if (token.type == COMMENT_OPEN) {
			comment2();
		}
		else {
			putchar(token.character);
		}
	}

	return 0;
}

/******************************************************************************
 * quoted_string2: handle quoted strings, in which comments are allowed to
 * appear
 *****************************************************************************/
int quoted_string2(void) {
	/*
	int current = character;
	putchar(current);
	while (((current = getchar()) != EOF) && (current != character)) {
		putchar(current);
	}
	if (current == character) {
		putchar(current);
	}
	*/
	return 0;
}
