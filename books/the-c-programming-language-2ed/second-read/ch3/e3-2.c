#include <stdio.h>

#define MAX_LINE 1024

int escape(char s[], const char t[]);
int unescape(char s[], const char t[]);

int main(void) {
	char from[] = "\tthis\tis\na very\tmessy\nstring!\n";
	char to[MAX_LINE];

	int status = escape(to, from);

	/*from[0] = '\0';
	to[0] = '\0';*/

	printf("Original:\n%s", from);
	
	if (status >= 0) {
		printf("\nescape()'d:\n%s", to);
	}

	status = unescape(to, from);
	if (status >= 0) {
		printf("\n\nunescape()'d:\n%s", to);
	}

	return 0;
}

/******************************************************************************
 * escape: replace any escaped character in a string with it's escaped
 * representation (e.g. '\n' becomes "\n").
 *
 * Input:
 *     A string containing escaped characters.
 *
 * Output:
 *     The same string with the escaped characters with replaced escape
 *     sequences.
 *
 * Known bugs:
 *     None.
 *****************************************************************************/
int escape(char s[], const char t[]) {
	int i, j;
	char c;
	j = 0;
	for (i = 0; (c = t[i]) != '\0'; ++i) {
		switch (c) {
			case '\a':
				s[j++] = '\\';
				s[j] = 'a';
				break;
			case '\b':
				s[j++] = '\\';
				s[j] = 'b';
				break;
			case '\f':
				s[j++] = '\\';
				s[j] = 'f';
				break;
			case '\n':
				s[j++] = '\\';
				s[j] = 'n';
				break;
			case '\r':
				s[j++] = '\\';
				s[j] = 'r';
				break;
			case '\t':
				s[j++] = '\\';
				s[j] = 't';
				break;
			case '\v':
				s[j++] = '\\';
				s[j] = 'v';
				break;
			case '\\':
				s[j++] = '\\';
				s[j] = '\\';
				break;
			case '\?':
				s[j++] = '\\';
				s[j] = '\?';
				break;
			case '\'':
				s[j++] = '\\';
				s[j] = '\'';
				break;
			case '\"':
				s[j++] = '\\';
				s[j] = '\"';
				break;
			default:
				s[j] = c;
				break;
		}
		++j;
	}
	s[j] = '\0';

	return 0;
}

/******************************************************************************
 * unescape: replace an escape sequence in a string with its actual escape
 * character (e.g. "\n" becomes '\n').
 *
 * Input:
 *     A string containing one or more escape sequences.
 *
 * Output:
 *     The same string with the escape sequences replaced with escaped
 *     characters replaced with "\n".
 *
 * Known bugs:
 *     None.
 *****************************************************************************/
int unescape(char s[], const char t[]) {
	int i;
	int j = 0;
	char c;
	for (i = 0; (c = t[i]) != 0; ++i) {
		if (t[i] == '\\') {
			int nextc = t[i+1];
			switch (nextc) {
				case 'a':
					s[j] = '\a';
					++i;
					break;
				case 'b':
					s[j] = '\b';
					++i;
					break;
				case 'f':
					s[j] = '\f';
					++i;
					break;
				case 'n':
					s[j] = '\n';
					++i;
					break;
				case 'r':
					s[j] = '\r';
					++i;
					break;
				case 't':
					s[j] = '\t';
					++i;
					break;
				case 'v':
					s[j] = '\v';
					++i;
					break;
				case '\\':
					s[j] = '\\';
					++i;
					break;
				case '\?':
					s[j] = '\?';
					++i;
					break;
				case '\'':
					s[j] = '\'';
					++i;
					break;
				case '\"':
					s[j] = '\"';
					++i;
					break;
				default:
					s[j] = c;
					break;
			}
		}
		else {
			s[j] = c;
		}
		++j;
	}
	s[j] = '\0';

	return 0;
}
