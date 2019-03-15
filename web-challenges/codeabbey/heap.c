#include <math.h>
#include <stdlib.h>
#include "heap.h"
#define ROOT_INDEX 0

/* heap_init: initialize an empty heap structure */
void heap_init(enum heap_error *error, Heap *heap, const enum heap_type type,
		unsigned int initial_size) {
	heap->type = type;
	heap->size = initial_size;
	heap->next_index = ROOT_INDEX;
	heap->array = malloc(heap->size*sizeof *heap->array);
	if (NULL != error) {
		if (NULL == heap->array) {
			*error = HEAP_MEMORY;
		}
		else {
			*error = HEAP_SUCCESS;
		}
	}
	return;
}

/* heap_init_from_array: initialize a heap structure using a given
 * dynamically-allocated array of void * of size size, occupied by n_elements
 * elements. The array may not be fragmented. */
void heap_init_from_array(enum heap_error *error, Heap *heap,
		const enum heap_type type, unsigned int size, unsigned int n_elements,
		void **array, int (*compare)(const void *keyval, const void *datum)) {
	heap->type = type;
	heap->size = size;
	heap->next_index = n_elements;
	heap->array = array;
	heap_heapify(error, heap, compare);
	if (NULL != error) {
		if (NULL == heap->array) {
			*error = HEAP_MEMORY;
		}
		else {
			*error = HEAP_SUCCESS;
		}
	}
	return;
}

/* heap_clear: clean up a heap structure */
void heap_clear(Heap *heap) {
	heap->type = HEAP_DEAD;
	heap->size = 0;
	heap->next_index = 0;
	free(heap->array);
	heap->array = NULL;
	return;
}

/* heap_sift_up: starting from child_index, perform a series of swaps so that
 * the heap property is conserved after adding an element at that child index.
 * Useful in the heap_insert function. */
void heap_sift_up(enum heap_error *error, Heap *heap, unsigned int child_index,
		int (*compare)(const void *keyval, const void *datum)) {
	void **array = heap->array;
	/* for a min heap: */
	if (HEAP_MIN == heap->type) {
		/* enforce the heap property by reorganizing the heap, stop when the child
		 * element is the root */
		while (child_index > ROOT_INDEX) {
			/* get the child's parent index */
			unsigned int parent_index = floor((child_index - 1)/2);
			/* if the parent is larger than the child, swap the two elements */
			if (compare(array[parent_index], array[child_index]) > 0) {
				void *temp;
				HEAP_SWAP(array[parent_index], array[child_index]);
			}
			/* set the new child index to the current parent */
			child_index = parent_index;
		}
	}
	/* a max heap is almost identical, the only difference is the sense of the
	 * comparison */
	else if (HEAP_MAX == heap->type) {
		while (child_index > ROOT_INDEX) {
			unsigned int parent_index = floor((child_index - 1)/2);
			/* difference here */
			if (compare(array[parent_index], array[child_index]) < 0) {
				void *temp;
				HEAP_SWAP(array[parent_index], array[child_index]);
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

/* heap_sift_down: starting from parent_index, go through the heap and rearrange
 * elements so the heap property is maintained. Useful after removing an
 * element, as in the heap_extract function. */
void heap_sift_down(enum heap_error *error, Heap *heap, unsigned int parent_index,
		int (*compare)(const void *keyval, const void *datum)) {
	void **array = heap->array;
	if (HEAP_MIN == heap->type) {
		/* heap property may be violated, need to reorganize the heap */
		while (parent_index < heap->next_index) {
			unsigned int temp_index = parent_index;
			unsigned int left_child_index = parent_index*2 + 1;
			unsigned int right_child_index = parent_index*2 + 2;
			/* left child element exists and its value is less than the value at
			 * temp_index */
			if (left_child_index < heap->next_index &&
					compare(array[left_child_index], array[temp_index]) < 0) {
				/* set the temp index to this child index */
				temp_index = left_child_index;
			}
			/* right child element exists and its value is less than the value at
			 * temp_index */
			if (right_child_index < heap->next_index &&
					compare(array[right_child_index], array[temp_index]) < 0) {
				/* set the temp index to this child index */
				temp_index = right_child_index;
			}
			/* if the temporary index has changed from its initial value (parent
			 * index), swap these two values and set the new parent index to the
			 * temporary index */
			if (temp_index != parent_index) {
				void *temp;
				HEAP_SWAP(array[temp_index], array[parent_index]);
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
	else if (HEAP_MAX == heap->type) {
		while (parent_index < heap->next_index) {
			unsigned int temp_index = parent_index;
			unsigned int left_child_index = parent_index*2 + 1;
			unsigned int right_child_index = parent_index*2 + 2;
			/* difference here */
			if (left_child_index < heap->next_index &&
					compare(array[left_child_index], array[temp_index]) > 0) {
				temp_index = left_child_index;
			}
			/* difference here */
			if (right_child_index < heap->next_index &&
					compare(array[right_child_index], array[temp_index]) > 0) {
				temp_index = right_child_index;
			}
			if (temp_index != parent_index) {
				void *temp;
				HEAP_SWAP(array[temp_index], array[parent_index]);
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
			return;
		}
	}
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	return;
}

/* heap_heapify: sort an array in a given heap structure so that it obeys the
 * heap property */
void heap_heapify(enum heap_error *error, Heap *heap,
		int (*compare)(const void *keyval, const void *datum)) {
	unsigned int i = heap->next_index/2;
	while (i-- > ROOT_INDEX) {
		heap_sift_down(error, heap, i, compare);
	}
	return;
}

/* heap_insert: add an element onto the heap. The compare function must
 * return a negative integer if keyval is less than datum, 0 if keyval is equal
 * to datum, and a positive integer if it is greater than datum. */
void heap_insert(enum heap_error *error, Heap *heap, void *new_element,
		int (*compare)(const void *keyval, const void *datum)) {
	void **array = heap->array;
	unsigned int child_index;
	/* if the heap has grown too large, reallocate memory */
	if (heap->next_index >= heap->size) {
		heap->size *= 2;
		array = realloc(array, heap->size*sizeof *array);
		if (NULL != error) {
			if (NULL == array) {
				*error = HEAP_MEMORY;
				return;
			}
		}
	}
	/* add the new element to the heap, save its index as child_index, and
	 * increment the heap index */
	array[heap->next_index] = new_element;
	child_index = heap->next_index;
	(heap->next_index)++;
	heap_sift_up(error, heap, child_index, compare);
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	return;
}

/* heap_extract: remove the root element from the heap, reorder the heap so it
 * maintains its heap property, and return the root element (minimum element
 * for a min heap and maximum value for a max heap). */
void *heap_extract(enum heap_error *error, Heap *heap,
		int (*compare)(const void *keyval, const void *datum)) {
	void **array = heap->array;
	/* save the root element */
	void *root = array[ROOT_INDEX];
	if (ROOT_INDEX == heap->next_index) {
		if (NULL != error) {
			*error = HEAP_EMPTY;
			return root;
		}
	}
	/* next_index points one past the end; decrement it first, then... */
	(heap->next_index)--;
	/* replace root with the last element, which effectively deletes the root
	 * and moves the last element to the root */
	array[ROOT_INDEX] = array[heap->next_index];
	/* for a min heap: */
	heap_sift_down(error, heap, ROOT_INDEX, compare);
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	/* return the root element */
	return root;
}

/* heap_is_heap: return HEAP_TRUE if the given heap has the heap property, and
 * HEAP_FALSE if it does not */
enum heap_boolean heap_is_heap(enum heap_error *error, const Heap *heap,
		int (*compare)(const void *keyval, const void *datum)) {
	if (HEAP_MIN == heap->type) {
		void **array = heap->array;
		unsigned int parent_index = heap->next_index/2;
		while (parent_index-- > ROOT_INDEX) {
			unsigned int left_index = parent_index*2 + 1;
			unsigned int right_index = parent_index*2 + 2;
			if (compare(array[parent_index], array[left_index]) > 0 ||
					compare(array[parent_index], array[right_index]) > 0) {
				return HEAP_FALSE;
			}
		}
	}
	else if (HEAP_MAX == heap->type) {
		void **array = heap->array;
		unsigned int parent_index = heap->next_index/2;
		while (parent_index-- > ROOT_INDEX) {
			unsigned int left_index = parent_index*2 + 1;
			unsigned int right_index = parent_index*2 + 2;
			if (compare(array[parent_index], array[left_index]) < 0 ||
					compare(array[parent_index], array[right_index]) < 0) {
				return HEAP_FALSE;
			}
		}

	}
	else {
		if (NULL != error) {
			*error = HEAP_UNRECOGNIZED;
			return HEAP_FALSE;
		}
	}
	if (NULL != error) {
		*error = HEAP_SUCCESS;
	}
	return HEAP_TRUE;
}
