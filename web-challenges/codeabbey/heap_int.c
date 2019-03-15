#include <math.h>
#include <stdlib.h>
#include "heap.h"
#define ROOT_INDEX 0

/* heap_init: initialize a heap structure */
void heap_init(enum heap_error *error, Heap *h, const enum heap_type type,
		unsigned int initial_size) {
	h->type = type;
	h->size = initial_size;
	h->next_index = ROOT_INDEX;
	h->elements = malloc(h->size*sizeof *h->elements);
	if (NULL != error) {
		if (NULL == h->elements) {
			*error = HEAP_MEMORY;
		}
		else {
			*error = HEAP_SUCCESS;
		}
	}
	return;
}

/* heap_clear: clean up a heap structure */
void heap_clear(Heap *h) {
	h->type = HEAP_DEAD;
	h->size = 0;
	h->next_index = 0;
	free(h->elements);
	h->elements = NULL;
	return;
}

/* heap_insert: add an element onto the heap */
void heap_insert(enum heap_error *error, Heap *h, const int new_element) {
	unsigned int child_index;
	/* if the heap has grown too large, reallocate memory */
	if (h->next_index >= h->size) {
		h->size *= 2;
		h->elements = realloc(h->elements, h->size*sizeof *h->elements);
		if (NULL != error) {
			if (NULL == h->elements) {
				*error = HEAP_MEMORY;
				return;
			}
		}
	}
	/* add the new element to the heap, save its index as child_index, and
	 * increment the heap index */
	h->elements[h->next_index] = new_element;
	child_index = h->next_index;
	(h->next_index)++;
	/* for a min heap: */
	if (HEAP_MIN == h->type) {
		/* enforce the heap property by reorganizing the heap, stop when the child
		 * element is the root */
		while (child_index > ROOT_INDEX) {
			/* get the child's parent index */
			unsigned int parent_index = floor((child_index - 1)/2);
			/* if the parent is larger than the child, swap the two elements */
			if (h->elements[parent_index] > h->elements[child_index]) {
				int temp;
				HEAP_SWAP(h->elements[parent_index], h->elements[child_index]);
			}
			/* set the new child index to the current parent */
			child_index = parent_index;
		}
	}
	/* a max heap is almost identical, the only difference is the sense of the
	 * comparison */
	else if (HEAP_MAX == h->type) {
		while (child_index > ROOT_INDEX) {
			unsigned int parent_index = floor((child_index - 1)/2);
			/* difference here */
			if (h->elements[parent_index] < h->elements[child_index]) {
				int temp;
				HEAP_SWAP(h->elements[parent_index], h->elements[child_index]);
			}
			child_index = parent_index;
		}
	}
	else {
		if (NULL != error) {
			*error = HEAP_UNRECOGNIZED;
			return;
		}
	}
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	return;
}

/* heap_extract: remove the root element from the heap, reorder the heap so it
 * maintains its heap property, and return the root element (minimum element
 * for a min heap and maximum value for a max heap) */
int heap_extract(enum heap_error *error, Heap *h) {
	unsigned int parent_index;
	/* save the root element */
	int root = h->elements[ROOT_INDEX];
	if (0 == h->next_index) {
		if (NULL != error) {
			*error = HEAP_EMPTY;
			return root;
		}
	}
	/* next_index points one past the end; decrement it first, then... */
	(h->next_index)--;
	/* replace root with the last element, which effectively deletes the root
	 * and moves the last element to the root */
	h->elements[ROOT_INDEX] = h->elements[h->next_index];
	/* for a min heap: */
	if (HEAP_MIN == h->type) {
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
				HEAP_SWAP(h->elements[temp_index], h->elements[parent_index]);
				parent_index = temp_index;
			}
			/* otherwise, stop */
			else {
				break;
			}
		}
	}
	/* a max heap is almost identical, the only difference is the sense of two
	 * comparisons */
	else if (HEAP_MAX == h->type) {
		for (parent_index = ROOT_INDEX; parent_index < h->next_index;) {
			unsigned int temp_index = parent_index;
			unsigned int left_child_index = parent_index*2 + 1;
			unsigned int right_child_index = parent_index*2 + 2;
			/* difference here */
			if (left_child_index < h->next_index
					&& h->elements[left_child_index] > h->elements[temp_index]) {
				temp_index = left_child_index;
			}
			/* difference here */
			if (right_child_index < h->next_index
					&& h->elements[right_child_index] > h->elements[temp_index]) {
				temp_index = right_child_index;
			}
			if (temp_index != parent_index) {
				int temp;
				HEAP_SWAP(h->elements[temp_index], h->elements[parent_index]);
				parent_index = temp_index;
			}
			else {
				break;
			}
		}
	}
	else {
		if (NULL != error) {
			*error = HEAP_UNRECOGNIZED;
			return root;
		}
	}
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	/* return the root element */
	return root;
}
