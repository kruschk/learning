#include <stdio.h>
#include <stdlib.h>
#include "checksum.h"
#define MAX_LINE 1024

/* swap two values */
#define SWAP(array, i, j)\
	long int temp = array[i];\
	array[i] = array[j];\
	array[j] = temp

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	long int array[MAX_LINE] = {0}, num;
	size_t i, count, swaps;
	/* get the string in input */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* loop through until the array terminator is reached */
	for (i = 0; (num = strtol(input_position, &input_position, 10)) != -1; i++) {
		array[i] = num;
	}
	count = i;
	/* perform one iteration of bubble sort */
	for (i = 0, swaps = 0; i < count - 1; i++) {
		if (array[i] > array[i + 1]) {
			/* swap values */
			SWAP(array, i, i+1);
			/* increment swap count */
			swaps++;
		}
	}
	/* print results */
	printf("%lu %lu\n", swaps, checksum(113, 10000007, array, count));
	return 0;
}
