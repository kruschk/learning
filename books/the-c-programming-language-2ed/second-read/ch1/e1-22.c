/* Exercise 1-22: Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 * 
 * If there is no place to put a newline in (i.e. a really long string of
 * characters), a dash will be inserted and then a new line begun. */

#include <stdio.h>
#define MAX_LINE 1024
#define LINE_LEN 80

int fold(char out[], const char in[], const int max_len, const int lim);
int getline2(char s[], int lim);
void copy(char to[], char from[]);

int main(void) {
	char in_line[MAX_LINE];
	char out_line[MAX_LINE];

	while ((getline2(in_line, MAX_LINE)) > 0) {
		fold(out_line, in_line, LINE_LEN, MAX_LINE);
		printf("%s", out_line);
	}

	return 0;
}

/******************************************************************************
 * Algorithm:
 * 
 *****************************************************************************/
int fold(char out[], const char in[], const int max_len, const int lim) {
	int out_pos = 0;
	for (int in_pos = 0; (in_pos < lim-1) && (in[in_pos]) != '\0'; ++in_pos) {
		int column = 1;
		/* copy the first characters up to max_len to out */
		while (column < max_len) {
			out[out_pos] = in[in_pos];
			if (in[in_pos] == '\0') {
				return 0;
			}
			++in_pos;
			++out_pos;
			++column;
		}

		/* scan backward, looking for "x " (any char and then a space) */
		int out_pos_sav = out_pos;
		int in_pos_sav = in_pos;
		while (column > 1) {
			if ((in[in_pos] == ' ') && (in[in_pos-1] != ' ')) {
				out[out_pos] = '\n';
				++out_pos;
				break;
			}
			--in_pos;
			--out_pos;
			--column;
		}

		/* if column reached 1, there was nowhere to insert a newline, so
		 * insert one */
		if (column == 1) {
			out_pos = out_pos_sav;
			in_pos = in_pos_sav-1;
			out[out_pos] = '\n';
			++out_pos;
		}
		else {
			column = 1;
		}
	}

	return 0;
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

/* copy: copy from into to; assume to is big enough */
void copy(char to[], char from[]) {
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0') {
		++i;
	}
}
