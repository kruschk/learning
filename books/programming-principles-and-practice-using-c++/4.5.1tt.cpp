#include "std_lib_facilities.h"

int addition_square(int);

int main(void) {
	for (int i = 0; i < 1000; i++) {
		cout << "i: " << i << "\tsquare: " << addition_square(i) << '\n';
	}
	return 0;
}

int addition_square(int n) {
	if (n < 0) {
		n *= -1;
	}

	int square = 0;
	for (int i = 0; i < n; i++) {
		square += n;
	}
	return square;
}
