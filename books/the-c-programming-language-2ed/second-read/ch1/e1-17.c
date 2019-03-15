#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int getline2(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main(void) {
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = getline2(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
		if (len > 80) {
			printf("Greater than 80 characters:\n%s\n", line);
		}
	}
	if (max > 0) {
		printf("Maximum line length: %d characters. Line:\n", max); /* This comment is here so this line ends up being longer than 80 characters. */
		printf("%s", longest);
	}
	return 0;
}

/* getline2: read a line into s, return length */
int getline2(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) { /* This comment is here so this line ends up being longer than 80 characters. */
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
