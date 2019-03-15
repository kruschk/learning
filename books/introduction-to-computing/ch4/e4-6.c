#include <stdio.h>

int gauss_sum(int n);

int main(void) {
	printf("gauss_sum: %d\n", gauss_sum(100));
	return 0;
}

int gauss_sum(int n) {
	if (n == 1) {
		return n;
	}
	else {
		return n + gauss_sum(n - 1);
	}
}
