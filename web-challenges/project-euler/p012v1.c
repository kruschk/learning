#include <stdio.h>
#include <math.h>

unsigned int compute_nth_triangle(unsigned int n) {
	unsigned int sum = 0;
	while (n > 0) {
		sum += n;
		n--;
	}
	return sum;
}

unsigned int count_divisors(const unsigned int n) {
	unsigned int i = 1;
	unsigned int stop = sqrt(n);
	unsigned int count = 2; /* 1 and the number itself are both divisors */
	for (i = 2; i <= stop; i++) {
		if ((n % i) == 0) {
			count += 2;
		}
	}
	return count;
}

int main(void) {
	unsigned int i = 1;
	unsigned int value;
	unsigned int count = 0;
	do {
		i++;
		value = compute_nth_triangle(i);
		count = count_divisors(value);
		/*printf("i: %u, value: %u, count: %u\n", i, value, count);*/
	}
	while (count < 500);
	printf("i: %u, value: %u, count: %u\n", i, value, count);

	return 0;
}
