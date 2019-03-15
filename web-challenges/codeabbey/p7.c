#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 1024

double FtoC(double F) {
	return (F - 32.0)*5.0/9.0;
}

int main(void) {
    /* initialize/declare variables */
    size_t i, number_of_values;
	long F, C;
    char input[MAX_LINE];
    char *input_position;
    /* get the first number and convert it to long */
    fgets(input, MAX_LINE, stdin);
    number_of_values = strtol(input, &input_position, 10);
    /* perform the conversion on each number */
    for (i = 0; i < number_of_values; i++) {
        /* gather input */
        F = strtol(input_position, &input_position, 10);
        /* convert to Celsius */
		C = custom_round(FtoC(F));
        /* format printing so there's no trailing space */
        (i != number_of_values - 1) ? printf("%ld ", C) : printf("%ld\n", C);
    }
    return 0;
}
