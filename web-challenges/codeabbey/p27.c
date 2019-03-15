#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_NUMS 1024

/* swap two values */
#define SWAP(array, i, j)\
	long int temp = array[i];\
	array[i] = array[j];\
	array[j] = temp

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t i, n_entries, passes = 0, new_swaps, swaps = 0;
	unsigned long int array[MAX_NUMS];
	/* get the string in input */
	fgets(input, MAX_LINE, stdin);
	n_entries = strtoul(input, NULL, 10);
	/* get the second string, which contains the array entries */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* populate the array */
	for (i = 0; i < n_entries; i++) {
		array[i] = strtoul(input_position, &input_position, 10);
	}
	/* Sort the array with bubble sort. When no new swaps are performed, the
	 * sort is finished. */
	do {
		/* this loop performs one iteration of bubble sort */
		new_swaps = 0;
		for (i = 0; i < n_entries - 1; i++) {
			if (array[i] > array[i + 1]) {
				/* swap values */
				SWAP(array, i, i+1);
				/* increment swap count */
				new_swaps++;
			}
		}
		/* keep track of the total number of swaps and passes */
		swaps += new_swaps;
		passes++;
	}
	while (new_swaps != 0);
	/* print results */
	printf("%lu %lu\n", passes, swaps);
	return 0;
}
