#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 1024

int main(void) {
    /* initialize/declare variables */
    size_t i, number_of_pairs;
	long result;
    double a, b;
    char input[MAX_LINE];
    char *input_position;
    /* get the first line and convert the number to long */
    fgets(input, MAX_LINE, stdin);
    number_of_pairs = strtol(input, NULL, 10);
    /* perform the rounding on each pair */
    for (i = 0; i < number_of_pairs; i++) {
        /* gather input pairs */
        fgets(input, MAX_LINE, stdin);
        a = strtol(input, &input_position, 10);
        b = strtol(input_position, NULL, 10);
        /* divide two numbers */
		result = custom_round(a/b);
        /* format printing so there's no trailing space */
        (i != number_of_pairs - 1) ? printf("%ld ", result) :
            printf("%ld\n", result);
    }
    return 0;
}
