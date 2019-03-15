#include <stdio.h>

int main(void) {
	int lim = 1024;
	int i = 0;
	int c = 0;

	/* original: */
	for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i) {
		printf("original\n");
	}

	/* alternate form using while */
	i = 0;
	while (i < lim - 1) {
		if ((c = getchar()) != '\n') {
			if (c != EOF) {
				/* do something */
				printf("while\n");
			}
			else {
				break;
			}
		}
		else {
			break;
		}
		++i;
	}

	/* alternate form using for */
	for (i = 0; i < lim - 1; ++i) {
		if ((c = getchar()) != '\n') {
			if (c != EOF) {
				printf("for\n");
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	return 0;
}
