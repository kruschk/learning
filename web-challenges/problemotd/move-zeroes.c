#include <stdio.h>
#define ARRAY_LENGTH (sizeof in/sizeof in[0])

/* move-zeroes: move the 0s in an array of integers to the end of the array.
 * The two arrays must be of equal len, and the out array must be initialized
 * to zero. */
void move_zeros(int in[], int out[], size_t len) {
	size_t i, j;
	for (i = 0, j = 0; i < len; i++) {
		if (in[i] != 0) {
			out[j] = in[i];
			j++;
		}
	}
}

int main(void) {
	/*initialize arrays */
	int in[] = {1, 3, 9, 0, 5, 4, 0, 0, 6, 6, 0, 2, 4, 1, 0, 4, 9, 7, 0, 0, 1,
		2, 0};
	int out[ARRAY_LENGTH] = {0};
	/* print length */
	printf("ARRAY_LENGTH: %lu\n", ARRAY_LENGTH);
	/* print input */
	printf("in:  ");
	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		printf("%d", in[i]);
	}
	putchar('\n');
	/* perform transfomation */
	move_zeros(in, out, ARRAY_LENGTH);
	/* print output */
	printf("out: ");
	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		printf("%d", out[i]);
	}
	putchar('\n');
	return 0;
}
