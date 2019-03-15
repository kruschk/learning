#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define ROOT_INDEX 0
#define HEAP_INITIAL_SIZE 16

/* macro to swap two elements */
#define SWAP(a, b)\
	temp = a;\
	a = b;\
	b = temp;

/* heap structure */
typedef struct {
	unsigned int size;
	unsigned int next_index;
	int *elements;
} Heap;

/* heap_init: initialize a heap structure */
void heap_init(Heap *h, unsigned int initial_size) {
	h->size = initial_size;
	h->next_index = ROOT_INDEX;
	h->elements = malloc(h->size*sizeof *h->elements);
	return;
}

/* heap_clear: clean up a heap structure */
void heap_clear(Heap *h) {
	h->size = 0;
	h->next_index = 0;
	free(h->elements);
	h->elements = NULL;
	return;
}

/* heap_insert: add an element onto the heap */
void heap_insert(Heap *h, int new) {
	unsigned int child_index;
	/* if the heap has grown too large, reallocate memory */
	if (h->next_index >= h->size) {
		h->size *= 2;
		h->elements = realloc(h->elements, h->size*sizeof *h->elements);
	}
	/* add the new element to the heap, save its index as child_index, and
	 * increment the heap index */
	h->elements[h->next_index] = new;
	child_index = h->next_index;
	(h->next_index)++;
	/* enforce the heap property by reorganizing the heap, stop when the child
	 * element is the root */
	while (child_index > ROOT_INDEX) {
		/* get the child's parent index */
		unsigned int parent_index = floor((child_index - 1)/2);
		/* if the parent is larger than the child, swap the two elements */
		if (h->elements[parent_index] > h->elements[child_index]) {
			int temp;
			SWAP(h->elements[parent_index], h->elements[child_index]);
		}
		/* set the new child index to the current parent */
		child_index = parent_index;
	}
	return;
}

/* heap_delete_root: delete the root element from the heap */
void heap_delete_root(Heap *h) {
	unsigned int parent_index;
	/* replace the root element with the final element in the heap, and delete
	 * the final element */
	/* next_index points one past the end; decrement it first */
	(h->next_index)--;
	/* replace root with the last element, which effectively deletes the root
	 * and moves the last element to the root */
	h->elements[ROOT_INDEX] = h->elements[h->next_index];
	/* heap property may be violated, need to reorganize the heap */
	for (parent_index = ROOT_INDEX; parent_index < h->next_index;) {
		unsigned int temp_index = parent_index;
		unsigned int left_child_index = parent_index*2 + 1;
		unsigned int right_child_index = parent_index*2 + 2;
		/* left child element exists and its value is less than the value at
		 * temp_index */
		if (left_child_index < h->next_index
				&& h->elements[left_child_index] < h->elements[temp_index]) {
			/* set the temp index to this child index */
			temp_index = left_child_index;
		}
		/* right child element exists and its value is less than the value at
		 * temp_index */
		if (right_child_index < h->next_index
				&& h->elements[right_child_index] < h->elements[temp_index]) {
			/* set the temp index to this child index */
			temp_index = right_child_index;
		}
		/* if the temporary index has changed from its initial value (parent
		 * index), swap these two values and set the new parent index to the
		 * temporary index */
		if (temp_index != parent_index) {
			int temp;
			SWAP(h->elements[temp_index], h->elements[parent_index]);
			parent_index = temp_index;
		}
		/* otherwise, stop */
		else {
			break;
		}
	}
	return;
}

int main(void) {
	unsigned int cases, i;
	Heap h;
	/* get the number of cases from stdin */
	if (1 != scanf("%u ", &cases)) {
		fprintf(stderr, "error reading number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* initialize our heap */
	heap_init(&h, HEAP_INITIAL_SIZE);
	/* each case modifies our heap */
	for (i = 0; i < cases; i++) {
		/* get the new value */
		int new;
		if (1 != scanf("%d ", &new)) {
			fprintf(stderr, "error reading input number %u on line 2\n",
					i + 1);
			heap_clear(&h);
			exit(EXIT_FAILURE);
		}
		/* delete the root value when we encounter a 0 */
		if (0 == new) {
			heap_delete_root(&h);
		}
		/* otherwise, insert the new value into the heap */
		else {
			heap_insert(&h, new);
		}
	}
	/* print the resulting heap */
	for (i = 0; i < h.next_index; i++) {
		printf((i == h.next_index - 1) ? "%d\n" : "%d ", h.elements[i]);
	}
	/* clean up */
	heap_clear(&h);
	return 0;
}
