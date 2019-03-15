#include <stdio.h>

void qsort(int v[], int left, int right);
void print_array(int v[], size_t size);

int main(void) {
	int array[] = {7, 3, 8, 9, 0, 5, 1, 2, 4, 6 };
	size_t array_size = sizeof(array)/sizeof(array[0]);

	printf("Original:\n");
	print_array(array, array_size);

	qsort(array, 0, array_size-1);

	printf("Sorted:\n");
	print_array(array, array_size);

	return 0;
}

/* print_array: print an array of integers */
void print_array(int v[], size_t size) {
	size_t i;
	printf("array:");
	for (i = 0; i < size; i++) {
		printf("%3d", v[i]);
	}
	printf("\nindex:");
	for (i = 0; i < size; i++) {
		printf("%3lu", i);
	}
	putchar('\n');
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right) {
	int i, last;
	void swap(int v[], int i, int j);

	if (left >= right) {
		return;
	}
	swap(v, left, (left + right)/2);
	/*printf("first swap\n");
	print_array(v, 10);*/
	last = left;
	/*printf("last: %d\n", last);*/
	for (i = left + 1; i <= right; i++) {
		if (v[i] < v[left]) {
			swap(v, ++last, i);
			/*printf("compare swap, last: %d\n", last);
			print_array(v, 10);*/
		}
	}
	swap(v, left, last);
	/*printf("final swap\n");
	print_array(v, 10);*/
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
