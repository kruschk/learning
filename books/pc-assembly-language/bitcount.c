#include <stdio.h>

int count_bits(unsigned int data) {
	int cnt = 0;

	while(data != 0) {
		data = data & (data - 1);
		cnt++;
	}

	return cnt;
}

int main(void) {
	unsigned int ndata = 5;
	int result = count_bits(ndata);
	printf("%d\n", result);
	return 0;
}
