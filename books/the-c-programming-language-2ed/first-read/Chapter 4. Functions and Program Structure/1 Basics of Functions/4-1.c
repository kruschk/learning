/* Exercise 4-1. Write the function strrindex(s,t), which returns the position
	of the rightmost occurence of t in s, or -1 if there is none. */
	
#include <stdio.h>
#define	MAXLINE	1000	/* maximum input line length */

int getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main(void) {
	int rindex;
	char line[MAXLINE];
	char pattern[] = "ow";		/* pattern to search for */
	int found = 0;

	while (getline(line, MAXLINE) > 0) {
		if ((rindex = strrindex(line, pattern)) >= 0) {
			printf("%d\n", rindex);
			found++;
		}
	}
	return found;
}

/* getline: get line into s, return length */
int getline(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = (char)c;
	}
	if (c == '\n') {
		s[i++] = (char)c;
	}
	s[i] = '\0';
	return i;
}

/* strrindex: return index of t in s from the right, -1 if none */
int strrindex(char s[], char t[]) {
	int i, j, k, rindex;

	rindex	= -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
			;
		}
		if (k > 0 && t[k] == '\0') {
			rindex = i;
		}
	}
	return rindex;
}