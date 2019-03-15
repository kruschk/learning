#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

/* macro to print a string, using a newline if we're at the last iteration in
 * the main for loop */
#define PRINT_STR(str) printf((i == n_tests - 1) ? str "\n" : str " ");

int main(void) {
	/* declare variables */
	char input[MAX_LINE];
	size_t i, n_tests;
	/* get the first string with the number of test cases in input */
	fgets(input, MAX_LINE, stdin);
	n_tests = strtoul(input, NULL, 10);
	/* compute the bmi and print the appropriate status string for each test */
	for (i = 0; i < n_tests; i++) {
		char *input_position;
		unsigned long int weight;
		double height, bmi;
		/* get the next line, which contains the weight and height */
		fgets(input, MAX_LINE, stdin);
		weight = strtoul(input, &input_position, 10);
		height = strtod(input_position, NULL);
		/* calculate BMI and print the appropriate word */
		bmi = (double)weight/(height*height);
		if (0 <= bmi && bmi < 18.5) {
			PRINT_STR("under");
		}
		else if (18.5 <= bmi && bmi < 25.0) {
			PRINT_STR("normal");
		}
		else if (25.0 <= bmi && bmi < 30.0) {
			PRINT_STR("over");
		}
		else {
			PRINT_STR("obese");
		}
	}
	return 0;
}
