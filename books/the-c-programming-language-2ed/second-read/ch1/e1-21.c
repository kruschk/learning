/* entab: replace strings of blanks with the requisite number of tabs and
 * blanks to achieve the same spacing. */

#include <stdio.h>

#define MAX_LINE 1024
#define TAB_STOP 8

int entab(char out_line[], char in_line[], int tab_stop, int lim);
int getline2(char s[], int lim);

int main(void) {
	char in_line[MAX_LINE];
	char out_line[MAX_LINE];

	while (getline2(in_line, MAX_LINE) > 0) {
		entab(out_line, in_line, TAB_STOP, MAX_LINE);
		printf("%s", out_line);
	}
	putchar('\n');

	return 0;
}

/* entab: replace a string of blanks by the requisite number of tabs and
 * blanks to achieve the same spacing. For example, for 4-column tab stops:
 *
 * ----------------------------------------------------------
 * |' '|'h'|'i'|' '|' '|' '|' '|' '|' '|' '|'y'|'o'|'u'|'\0'| <- in[]
 * ----------------------------------------------------------
 *   0   1   2   3   4*  5   6   7   8*  9  10  11  12*  13   <- in_pos
 *
 * ------------------------------------------------
 * |' '|'h'|'i'|'\t'|'\t'|' '|' '|'y'|'o'|'u'|'\0'| <- out[]
 * ------------------------------------------------
 *   0   1   2    3    4   5   6   7   8   9   10   <- out_pos */
int entab(char out[], char in[], int tab_stop, int lim) {
	int out_pos = 0;
	for (int in_pos = 0; (in_pos < lim-1) && (in[in_pos] != 0); ++in_pos) {
		/* need to take special action when we hit a space */
		if (in[in_pos] == ' ') {
			/* using the position in the in_array, replace spaces
			 * with a tab stop whenever possible */
			int blank_count = 0;
			while (in[in_pos] == ' ') {
				++blank_count;
				if (!((in_pos+1) % tab_stop)) {
					out[out_pos] = '\t';
					++out_pos;
					blank_count = 0;
				}
				++in_pos;
			}
			--in_pos;

			/* pad the remaining space with blanks */
			while (blank_count > 0) {
				out[out_pos] = ' ';
				++out_pos;
				--blank_count;
			}
		}
		/* if current character is not a space, just copy the character
		 * to out[] */
		else {
			out[out_pos] = in[in_pos];
			++out_pos;
		}
	}
	out[out_pos] = '\0';

	/* return out_pos, which corresponds to the length of out[] */
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
