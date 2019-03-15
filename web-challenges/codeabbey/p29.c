#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_ENTRIES 1024

struct entry {
	long int value;
	size_t original_index;
};

/* swap two values */
#define SWAP(array, i, j)\
	struct entry temp = array[i];\
	array[i] = array[j];\
	array[j] = temp

/* bubble_sort: sort an array of struct entry based on value members using
 * bubble sort */
void bubble_sort(struct entry *entry_array, size_t length) {
	size_t new_swaps, i;
	do {
		/* this loop performs one iteration of bubble sort */
		new_swaps = 0;
		for (i = 0; i < length - 1; i++) {
			if (entry_array[i].value > entry_array[i + 1].value) {
				/* swap values */
				SWAP(entry_array, i, i+1);
				/* increment swap count */
				new_swaps++;
			}
		}
	}
	while (new_swaps != 0);
	return;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE], *input_position;
	size_t n_entries, i;
	struct entry entry_array[MAX_ENTRIES];
	/* get number of entries from first line */
	fgets(input, MAX_LINE, stdin);
	n_entries = strtoul(input, NULL, 10);
	/* get second line, which contains entry values */
	fgets(input, MAX_LINE, stdin);
	input_position = input;
	/* populate array */
	for (i = 0; i < n_entries; i++) {
		entry_array[i].value = strtol(input_position, &input_position, 10);
		entry_array[i].original_index = i + 1;
	}
	/* sort array based on value members */
	bubble_sort(entry_array, n_entries);
	/* print original indices of sorted array */
	for (i = 0; i < n_entries; i++) {
		printf((i == n_entries - 1) ? "%lu\n" : "%lu ",
				entry_array[i].original_index);
	}
	return 0;
}
