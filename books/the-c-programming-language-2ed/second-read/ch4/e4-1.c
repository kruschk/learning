#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024 /* maximum input line length */

int getline(char line[], int max);
int strrindex(char source[], char searchfor[]);


/* find all lines matching pattern */
int main(void) {
	char line[MAX_LINE];
	char pattern[] = "test"; /* pattern to search for */
	int found = 0;
	int match_pos = 0;

	while (getline(line, MAX_LINE) > 0) {
		if ((match_pos = strrindex(line, pattern)) >= 0) {
			printf("Position: %d\nString: %s", match_pos, line);
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
		s[i++] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

/* strrindex: return index of rightmost occurrence of t in s, -1 if none */
int strrindex(char s[], char t[]) {
	size_t i = strlen(s);
	size_t t_end_pos = strlen(t) - 1;

	while (i != 0) {
		size_t j, k;

		i--;
		for (j = i, k = t_end_pos; j != 0 && k != 0 && s[j] == t[k];) {
			j--;
			k--;
		}
		if (k == 0 && s[j] == t[k]) {
			return i - t_end_pos;
		}
	}

	return -1;
}
