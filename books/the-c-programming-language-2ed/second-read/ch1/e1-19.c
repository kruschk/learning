#include <stdio.h>

#define MAX_LINE 1024

int reverse(char input[], char output[], int lim);
int getline2(char s[], int lim);

int main(void) {
	char string[MAX_LINE];
	char reversed[MAX_LINE];

	int len = 0;
	while ((len = getline2(string, MAX_LINE)) > 0) {
		reverse(string, reversed, MAX_LINE);
		printf("%s", reversed);
	}
}

/* reverse: takes an input string and reverses it */
int reverse(char input[], char output[], int lim) {
	int length = 0;
	while (length < lim-1 && input[length] != '\0') {
		++length;
	}

	for (int i = 0; i < length; ++i) {
		output[i] = input[length - i - 1];
	}
	output[length] = '\0';

	return length;
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
