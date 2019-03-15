/* Solution to CodeAbbey problem 19. The program must parse a string and ensure
 * the brackets are balanced. Below is a grammar for balancing brackets,
 * although I'm not sure if it's 100% correct.
 * balanced-brackets:
 *   non-bracket-chars
 *   non-bracket-chars balanced-brackets
 *   balanced-brackets non-bracket-chars
 *   '(' balanced-brackets ')'
 *   '[' balanced-brackets ']'
 *   '{' balanced-brackets '}'
 *   '<' balanced-brackets '>'
 *   balanced-brackets balanced-brackets
 * non-bracket-chars:
 *   epsilon
 *   non-bracket non-bracket-chars
 * non-bracket:
 *   !bracket
 * bracket:
 *   '(' | ')'
 *   '[' | ']'
 *   '{' | '}'
 *   '<' | '>'
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 4096
enum bool {FALSE, TRUE};

/* is_opening_bracket: check if a bracket is opening */
int is_opening_bracket(char c) {
	switch (c) {
		case '(':
		case '[':
		case '{':
		case '<':
			return TRUE;
			break;
		default:
			return FALSE;
			break;
	}
}

/* is_closing_bracket: check if a bracket is closing */
int is_closing_bracket(char c) {
	switch (c) {
		case ')':
		case ']':
		case '}':
		case '>':
			return TRUE;
			break;
		default:
			return FALSE;
			break;
	}
}

/* check_brackets_recursive: check brackets recursively */
int check_brackets_recursive(char **str_pos_p) {
	/* whenever this function is called, it's because we found an opening
	 * bracket, so save it */
	const char opening_bracket = **str_pos_p;
	/* save the next character in the string as well */
	char c;
	/* loop while we haven't reached the end of the string */
	while ((c = *(++(*str_pos_p))) != '\0') {
		/* if we run into an opening bracket, call this function again, and we
		 * can short-circuit be returning FALSE if the call returns FALSE, but
		 * not if it returns TRUE */
		if (is_opening_bracket(c)) {
			if (check_brackets_recursive(str_pos_p) == FALSE) {
				return FALSE;
			}
		}
		/* if we come across a closing bracket, and that bracket matches with
		 * the opening bracket in this call frame, then the two brackets match,
		 * and we can return TRUE. Otherwise, return FALSE. */
		else if (is_closing_bracket(c)) {
			switch (opening_bracket) {
				case '(':
					if (c == ')') {
						return TRUE;
					}
					else {
						return FALSE;
					}
					break;
				case '[':
					if (c == ']') {
						return TRUE;
					}
					else {
						return FALSE;
					}
					break;
				case '{':
					if (c == '}') {
						return TRUE;
					}
					else {
						return FALSE;
					}
					break;
				case '<':
					if (c == '>') {
						return TRUE;
					}
					else {
						return FALSE;
					}
					break;
				default:
					break;
			}
		}
	}
	/* if we run into the end of the string in this function, brackets can't be
	 * matching, so return FALSE */
	if (c == '\0') {
		return FALSE;
	}
	/* this shouldn't happen */
	return FALSE;
}

/* check_brackets:  */
int check_brackets(char **str_pos_p) {
	char c;
	while ((c = *(*str_pos_p)) != '\0') {
		/* skip leading characters that aren't brackets or '\0' */
		while (!is_opening_bracket(c) && !is_closing_bracket(c) && c != '\0') {
			c = *(++(*str_pos_p));
		}
		/* if we've reached a null terminator, there were no brackets, so
		 * brackets are balanced */
		if (c == '\0') {
			return TRUE;
		}
		/* if we're starting on a closing bracket, brackets can't be balanced,
		 * so just exit */
		if (is_closing_bracket(c)) {
			return FALSE;
		}
		/* check brackets by recursively descending into the brackets */
		if (check_brackets_recursive(str_pos_p) == FALSE) {
			return FALSE;
		}
		(*str_pos_p)++;
	}
	/* this shouldn't happen, it's just here to make the compiler happy */
	return FALSE;
}

int main(void) {
	/* declare/initialize variables */
	size_t i, n_tests;
	char input[MAX_LINE], *input_position;
	int okay;
	/* determine number of test cases from first line */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	for (i = 0; i < n_tests; i++) {
		/* get the next line */
		fgets(input, MAX_LINE, stdin);
		input_position = input;
		/* check the brackets */
		okay = check_brackets(&input_position);
		/* print results */
		(i == n_tests - 1) ? printf("%d\n", okay) : printf("%d ", okay);
	}
	return 0;
}
