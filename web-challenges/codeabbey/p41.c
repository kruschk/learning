#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

/* median: determine the middle value of 3 numbers */
int median(int a, int b, int c) {
	if (a < b) {
		if (a >= c) {
			/* a is median */
			return a;
		}
		/* a is min */
		else if (b < c) {
			return b;
		}
	}
	/* a >= b */
	else {
		if (a < c) {
			/* a is median */
			return a;
		}
		/* a is max */
		else if (b >= c) {
			return b;
		}
	}
	return c;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_pos;
	size_t n_cases, i;
	/* get number of cases */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* determine median in each case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		int a, b, c;
		/* get the three values */
		fgets(input, MAX_LINE, stdin);
		a = strtol(input, &input_pos, 10);
		b = strtol(input_pos, &input_pos, 10);
		c = strtol(input_pos, &input_pos, 10);
		/* print the median */
		printf ((i == n_cases - 1) ? "%d\n" : "%d ", median(a, b, c));
	}
	return 0;
}
