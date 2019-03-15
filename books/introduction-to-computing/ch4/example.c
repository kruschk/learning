#include <stdio.h>

int g(int n);

int main(void) {
	int n = 100000;
	printf("%d\n", g(n));

	return 0;
}

int g(int n) {
	if (n == 0) {
		return 1;
	}
	else {
		return g(n - 1);
	}
}
