#include <stdio.h>

unsigned int produce_Collatz_sequence(unsigned int n) {
	size_t i = 1;
	while (n > 1) {
		if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = 3*n + 1;
		}
		i++;
	}
	return i;
}

int main(void) {
	unsigned int start;
	unsigned int maxstart = 0;
	unsigned int length = 0;
	unsigned int maxlength = 0;

	for (start = 0; start < 1000000; start++) {
		length = produce_Collatz_sequence(start);
		if (length > maxlength) {
			maxstart = start;
			maxlength = length;
		}
	}
	printf("maxstart: %u, maxlength: %u\n", maxstart, maxlength);

	return 0;
}
