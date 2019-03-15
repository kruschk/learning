#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* initialize/declare variables */
	char input[MAX_LINE];
	char *input_position;
	size_t i, number_of_tests;
	long t_1[4], t_2[4], time_1, time_2, t_diff, res[4];
	/* get the first number and convert it to unsigned long */
	fgets(input, MAX_LINE, stdin);
	number_of_tests = strtoul(input, NULL, 10);
	/* get two times, compute the difference, and print it */
	for (i = 0; i < number_of_tests; i++) {
		/* gather input */
		fgets(input, MAX_LINE, stdin);
		t_1[0] = strtol(input, &input_position, 10);
		t_1[1] = strtol(input_position, &input_position, 10);
		t_1[2] = strtol(input_position, &input_position, 10);
		t_1[3] = strtol(input_position, &input_position, 10);
		t_2[0] = strtol(input_position, &input_position, 10);
		t_2[1] = strtol(input_position, &input_position, 10);
		t_2[2] = strtol(input_position, &input_position, 10);
		t_2[3] = strtol(input_position, NULL, 10);
		/* convert days, hours, minutes, seconds to seconds */
		time_1 = (24*60*60)*t_1[0] + (60*60)*t_1[1] + 60*t_1[2] + t_1[3];
		time_2 = (24*60*60)*t_2[0] + (60*60)*t_2[1] + 60*t_2[2] + t_2[3];
		/* take the difference (in seconds) */
		t_diff = time_2 - time_1;
		/* convert difference back from seconds to days, hours, minutes,
		 * seconds */
		res[0] = t_diff/(24*60*60);
		t_diff %= (24*60*60);
		res[1] = t_diff/(60*60);
		t_diff %= (60*60);
		res[2] = t_diff/60;
		t_diff %= 60;
		res[3] = t_diff;
		/* format printing so there's no trailing space */
		(i == number_of_tests-1) ?
			printf("(%ld %ld %ld %ld)\n", res[0], res[1], res[2], res[3]) :
			printf("(%ld %ld %ld %ld) ", res[0], res[1], res[2], res[3]);
	}
	return 0;
}
