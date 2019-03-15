#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t n_cases, i;
	/* get the number of cases from the first line */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* find the root for each case */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		char *input_position;
		double s, r, p;
		size_t year;
		/* get required parameters */
		fgets(input, MAX_LINE, stdin);
		s = strtod(input, &input_position);
		r = strtod(input_position, &input_position);
		p = strtod(input_position, NULL);
		/* determine how long it will take for s to grow beyond r */
		year = 0;
		while (s < r) {
			/* wait a year */
			year++;
			/* calculate the new value of s with compounding interest */
			s = s*(1+p/100);
			/* truncate to nearest cent */
			s *= 100;
			s = floor(s);
			s /= 100;
			/*printf("%lu, %f", year, s);*/
		}
		/* print result */
		printf((i == n_cases - 1) ? "%lu\n" : "%lu ", year);
	}
	return 0;
}
