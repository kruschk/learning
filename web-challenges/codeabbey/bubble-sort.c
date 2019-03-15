#include <stdio.h>

/* swap two values */
#define SWAP(array, i, j)\
	long int temp = array[i];\
	array[i] = array[j];\
	array[j] = temp

/* bubble_sort: sort an array of long int using bubble sort */
size_t bubble_sort(long int *array, size_t length) {
	size_t new_swaps, passes = 0;
	do {
		/* this loop performs one iteration of bubble sort */
		new_swaps = 0;
		for (i = 0; i < length - 1; i++) {
			if (array[i] > array[i + 1]) {
				/* swap values */
				SWAP(array, i, i+1);
				/* increment swap count */
				new_swaps++;
			}
		}
		/* keep track of the total number of passes */
		passes++;
	}
	while (new_swaps != 0);
	return passes;
}
