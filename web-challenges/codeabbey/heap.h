/* In all cases, the compare function must return a negative integer if keyval
 * is less than datum, 0 if keyval is equal to datum, and a positive integer if
 * it is greater than datum. */
#ifndef HEAP_H
#define HEAP_H
/* macro to swap two elements */
#define HEAP_SWAP(a, b)\
	temp = a;\
	a = b;\
	b = temp

enum heap_error {HEAP_SUCCESS, HEAP_MEMORY, HEAP_UNRECOGNIZED, HEAP_EMPTY};
enum heap_type {HEAP_DEAD, HEAP_MIN, HEAP_MAX};
enum heap_boolean {HEAP_FALSE, HEAP_TRUE};

/* heap structure */
typedef struct {
	enum heap_type type;
	unsigned int size;
	unsigned int next_index;
	void **array;
} Heap;

/* heap_init: initialize a heap structure */
void heap_init(enum heap_error *error, Heap *h, const enum heap_type type,
		unsigned int initial_size);

/* heap_init_from_array: initialize a heap structure using a given
 * dynamically-allocated array of void * of size size, occupied by n_elements
 * elements. The array may not be fragmented. */
void heap_init_from_array(enum heap_error *error, Heap *heap,
		const enum heap_type type, unsigned int size, unsigned int n_elements,
		void **array, int (*compare)(const void *keyval, const void *datum));

/* heap_clear: clean up a heap structure */
void heap_clear(Heap *h);

/* heap_sift_up: starting from child_index, perform a series of swaps so that
 * the heap property is conserved after adding an element at that child index.
 * Useful in the heap_insert function. */
void heap_sift_up(enum heap_error *error, Heap *heap, unsigned int child_index,
		int (*compare)(const void *keyval, const void *datum));

/* heap_sift_down: starting from parent_index, go through the heap and rearrange
 * elements so the heap property is maintained. Useful after removing an
 * element, as in the heap_extract function. */
void heap_sift_down(enum heap_error *error, Heap *heap, unsigned int parent_index,
		int (*compare)(const void *keyval, const void *datum));

/* heap_heapify: sort an array in a given heap structure so that it obeys the
 * heap property */
void heap_heapify(enum heap_error *error, Heap *heap,
		int (*compare)(const void *keyval, const void *datum));

/* heap_insert: add an element onto the heap. The compare function must
 * return a negative integer if keyval is less than datum, 0 if keyval is equal
 * to datum, and a positive integer if it is greater than datum. */
void heap_insert(enum heap_error *error, Heap *h, void *new_element,
		int (*compare)(const void *keyval, const void *datum));

/* heap_extract: remove the root element from the heap, reorder the heap so it
 * maintains its heap property, and return the root element (minimum element
 * for a min heap and maximum value for a max heap). */
void *heap_extract(enum heap_error *error, Heap *h,
		int (*compare)(const void *keyval, const void *datum));

/* heap_is_heap: return HEAP_TRUE if the given heap has the heap property, and
 * HEAP_FALSE if it does not */
enum heap_boolean heap_is_heap(enum heap_error *error, const Heap *heap,
		int (*compare)(const void *keyval, const void *datum));
#endif
