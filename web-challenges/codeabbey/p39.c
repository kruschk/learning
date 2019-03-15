#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define N_VALUES 14
#define NAME_LENGTH 4

/* average: returns the average of an array of ints of size n */
double average(const int array[], const size_t n) {
	size_t i;
	int sum = 0;
	for (i = 0; i < n; i++) {
		sum += array[i];
	}
	return sum/n;
}

/* standard_deviation: returns the standard deviation of an array of ints of
 * size n */
double standard_deviation(const int array[], const size_t n) {
	size_t i;
	double sum_of_squares = 0;
	double avg = average(array, n);
	for (i = 0; i < n; i++) {
		sum_of_squares += (array[i]-avg)*(array[i]-avg);
	}
	return sqrt(sum_of_squares/(n-1));
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_cases, i;
	/* get the number of test cases */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* check if the each stock is worth investing in */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		char name[NAME_LENGTH + 1];
		size_t j;
		int array[N_VALUES];
		const double commission_rate = 1.0; 
		double avg, std_dev, commission_amount;
		/* get the next line */
		fgets(input, MAX_LINE, stdin);
		input_position = input;
		/* get the name of the stock */
		for (j = 0; isalpha(*input_position); j++) {
			name[j] = *input_position;
			input_position++;
		}
		name[j] = '\0';
		/* collect the stock prices for each day */
		for (j = 0; j < N_VALUES; j++) {
			array[j] = strtol(input_position, &input_position, 10);
		}
		/* compute the average and standard deviation */
		avg = average(array, N_VALUES);
		std_dev = standard_deviation(array, N_VALUES);
		/* compute the broker's commission */
		commission_amount = avg*commission_rate/100.0;
		/* if the standard deviation is greater than the commission, print the
		 * name of the stock */
		if (std_dev >= 4.0*commission_amount) {
			printf("%s ", name);
		}
	}
	putchar('\n');
	return 0;
}
