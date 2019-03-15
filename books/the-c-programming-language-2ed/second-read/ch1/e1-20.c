/* detab program: replaces tabs in its input with the appropriate number of
 * blanks to space to the next tab stop.
 */

#include <stdio.h>

#define MAX_LINE 1024
#define TAB_STOP 8

int detab(char out[], char in[], const int ncol, int lim);
int getline2(char s[], int lim);

int main(void) {
	char in_line[MAX_LINE];
	char out_line[MAX_LINE];

	while (getline2(in_line, MAX_LINE) > 0) {
		detab(out_line, in_line, TAB_STOP, MAX_LINE);
		printf("%s", out_line);
	}



	return 0;
}

int detab(char out[], char in[], const int tab_stop, int lim) {
	/* parse the input string for tabs */
	int out_pos = 0;
	for (int in_pos = 0; (in_pos < lim-1) && (in[in_pos] != '\0'); ++in_pos) {
		if (in[in_pos] == '\t') {
			do {
				out[out_pos] = ' ';
				++out_pos;
			}
			while (out_pos % tab_stop);
		}
		else {
			out[out_pos] = in[in_pos];
			++out_pos;
		}
	}
	out[out_pos] = '\0';

	return out_pos;
}

/* getline2: read a line into s, return length */
int getline2(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
