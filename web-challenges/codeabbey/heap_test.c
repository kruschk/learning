#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define HEAP_INITIAL_SIZE 16

int heap_compare(const void *keyval, const void *datum) {
	return *(int *)keyval - *(int *)datum;
}

int main(void) {
	unsigned int cases, i;
	int container[128];
	Heap h;
	if (1 != scanf("%u ", &cases)) {
		fprintf(stderr, "error reading number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	heap_init(NULL, &h, HEAP_MAX, HEAP_INITIAL_SIZE);
	for (i = 0; i < cases; i++) {
		if (1 != scanf("%d ", &container[i])) {
			fprintf(stderr, "error reading input number %u on line 2\n",
					i + 1);
			heap_clear(&h);
			exit(EXIT_FAILURE);
		}
		if (0 == container[i]) {
			heap_extract(NULL, &h, heap_compare);
		}
		else {
			heap_insert(NULL, &h, &container[i], heap_compare);
		}
	}
	for (i = 0; i < h.next_index; i++) {
		printf((i == h.next_index - 1) ? "%d\n" : "%d ", *(int *)h.array[i]);
	}
	if (HEAP_TRUE == heap_is_heap(NULL, &h, heap_compare)) {
		printf("I am a heap\n");
	}
	heap_clear(&h);
	return 0;
}
