#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_VALUES 300
#define MAX_LINE 4096

int main(void) {
	/* declare/initialize variables */
	size_t i;
	char input[MAX_LINE];
	char *input_position;
	long max = LONG_MIN;
	long min = LONG_MAX;
	long temp;
	/* collect input string (all values are on one line) */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* iterate through input string, setting max and min values */
	for (i = 0; i < NUM_VALUES; i++) {
		temp = strtol(input_position, &input_position, 10);
		if (temp > max) {
			max = temp;
		}
		if (temp < min) {
			min = temp;
		}
	}
	/* print results */
	printf("%ld %ld\n", max, min);
	return 0;
}
