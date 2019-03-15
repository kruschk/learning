#include <stdio.h>

int main(void) {
	printf("Type ^D to exit.\n");
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			putchar('\n');
		}
		else {
			putchar(c);
		}
	}

	return 0;
}
