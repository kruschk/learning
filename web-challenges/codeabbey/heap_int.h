#ifndef HEAP_INT_H
#define HEAP_INT_H
/* macro to swap two elements */
#define HEAP_SWAP(a, b)\
	temp = a;\
	a = b;\
	b = temp

#define ELEMENT_TYPE()\


enum heap_error {HEAP_SUCCESS, HEAP_MEMORY, HEAP_UNRECOGNIZED, HEAP_EMPTY};
enum heap_type {HEAP_DEAD, HEAP_MIN, HEAP_MAX};

/* heap structure */
typedef struct {
	enum heap_type type;
	unsigned int size;
	unsigned int next_index;
	int *elements;
	/*void **elements*/
} Heap;

/* heap_init: initialize a heap structure */
void heap_init(enum heap_error *error, Heap *h, const enum heap_type type,
		unsigned int initial_size);

/* heap_clear: clean up a heap structure */
void heap_clear(Heap *h);

/* heap_insert: add an element onto the heap */
void heap_insert(enum heap_error *error, Heap *h, const int new_element);

/* heap_extract: remove the root element from the heap, reorder the heap so it
 * maintains its heap property, and return the root element (minimum element
 * for a min heap and maximum value for a max heap) */
int heap_extract(enum heap_error *error, Heap *h);
#endif
