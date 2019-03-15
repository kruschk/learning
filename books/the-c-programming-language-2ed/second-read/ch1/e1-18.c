#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int getline2(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = getline2(line, MAXLINE)) > 0) {
		int i;
		for (i = len-2; i >= 0 && (line[i] == ' ' || line[i] == '\t'); --i) {
			;
		}
		if (i > 0) {
			line[++i] = '\n';
			line[++i] = '\0'; /* truncate */
			printf("%s", line);
		}
	}

	/*
	max = 0;
	while ((len = getline2(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) {
		printf("Line length: %d characters. Line:\n", max);
		printf("%s", longest);
	}
	*/

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
