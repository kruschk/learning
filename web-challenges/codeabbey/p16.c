#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 4096
#define MAX_NUMS 1024

int main(void) {
	/* declare/initialize variables */
	size_t i, n_tests, count;
	char input[MAX_LINE], *input_position;
	long num, average;
	/* determine number of test cases from first line */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	/* iterate through each line, determining the average for each */
	for (i = 0; i < n_tests; i++) {
		/* put line into input and set input_position to point to input */
		fgets(input, MAX_LINE, stdin);
		input_position = input;
		/* start building the average by adding each number from the line
		 * (note: it's okay to add the trailing zero since that won't affect
		 * the sum) */
		num = strtol(input_position, &input_position, 10);
		for (count = 0, average = 0; num != 0; count++) {
			average += num;
			num = strtol(input_position, &input_position, 10);
		}
		/* the average is the above sum divided by the count */
		average = custom_round((double)average/(double)count);
		/* print results */
		(i == n_tests - 1)
			? printf("%ld\n", average)
			: printf("%ld ", average);
	}
	return 0;
}
