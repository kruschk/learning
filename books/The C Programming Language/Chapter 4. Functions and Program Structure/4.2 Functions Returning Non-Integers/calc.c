#include <stdio.h>
#include <C:\Users\Jonah Kruschke\Documents\Programming\C\The C Programming Language\Chapter 4. Functions and Program Structure\4.2 Functions Returning Non-Integers\4-2.c>

#define	MAXLINE	100
int getline(char line[], int max);
double atof(char num[]);

/* rudimentary calculator */
int main(void) {
	double sum;
	char line[MAXLINE];

	sum = 0;
	while (getline(line, MAXLINE) > 0) {
		printf("\t%.20f\n", atof(line));
	}

	return 0;
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