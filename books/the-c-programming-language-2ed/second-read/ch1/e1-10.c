#include <stdio.h>

int main(void) {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			printf("\\t");
		}
		else if (c == '\b') {
			/* backspaces won't work because they never actually
			 * reach the program, bash doesn't allow that. */
			printf("\\b");
		}
		else if (c == '\\') {
			printf("\\\\");
		}
		else {
			putchar(c);
		}
	}

	return 0;
}
