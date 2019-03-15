#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define HEAP_INITIAL_SIZE 16

int main(void) {
	unsigned int cases, i;
	Heap h;
	if (1 != scanf("%u ", &cases)) {
		fprintf(stderr, "error reading number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	heap_init(NULL, &h, HEAP_MAX, HEAP_INITIAL_SIZE);
	for (i = 0; i < cases; i++) {
		int new;
		if (1 != scanf("%d ", &new)) {
			fprintf(stderr, "error reading input number %u on line 2\n",
					i + 1);
			heap_clear(&h);
			exit(EXIT_FAILURE);
		}
		if (0 == new) {
			heap_extract(NULL, &h);
		}
		else {
			heap_insert(NULL, &h, new);
		}
	}
	for (i = 0; i < h.next_index; i++) {
		printf((i == h.next_index - 1) ? "%d\n" : "%d ", h.elements[i]);
	}
	heap_clear(&h);
	return 0;
}
