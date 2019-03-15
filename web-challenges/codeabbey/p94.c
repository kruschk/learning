/* the answer is the sum of each element squared (i.e. 1*1 + 2*2 = 5,
 * 1*1 + 2*2 + 3*3 = 14, ...) */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	unsigned short int cases, i;
	unsigned int *sum_of_squares;
	/* get the number of test cases */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error reading the number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	sum_of_squares = malloc(cases*sizeof *sum_of_squares);
	/* for each case, compute the sum of the squares of each line */
	for (i = 0; i < cases; i++) {
		char line[MAX_LINE], *line_p;
		unsigned short int number;
		fgets(line, MAX_LINE, stdin);
		/* for each number, add its square to the sum of squares variable */
		for (line_p = line, sum_of_squares[i] = 0;
				*line_p != '\0' && *line_p != '\0'; line_p++) {
			number = strtoul(line_p, &line_p, 10);
			sum_of_squares[i] += number*number;
		}
	}
	/* print the results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%u\n" : "%u ", sum_of_squares[i]);
	}
	/* clean up */
	free(sum_of_squares);
	return 0;
}
