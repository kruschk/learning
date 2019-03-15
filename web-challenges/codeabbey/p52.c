#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_cases, i;
	/* get the number of test cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* determine if each triangle is acute, obtuse, or right */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		char *line_p, answer;
		unsigned int a, b, c;
		/* get lengths of the three sides */
		fgets(line, MAX_LINE, stdin);
		a = strtoul(line, &line_p, 10);
		b = strtoul(line_p, &line_p, 10);
		c = strtoul(line_p, NULL, 10);
		/* square each value */
		a *= a;
		b *= b;
		c *= c;
		/* determine if the triangle is acute, obtuse, or right */
		if (c < a + b) {
			answer = 'A';
		}
		else if (c > a + b) {
			answer = 'O';
		}
		else {
			answer = 'R';
		}
		/* print result */
		printf((i == n_cases - 1) ? "%c\n" : "%c ", answer);
	}
	return 0;
}
