#include <stdio.h>
#include <limits.h>

#define HISTOGRAM_BAR '*'

int main(void) {
	printf("Note: the vertical histogram requires an extremely wide ");
	printf("terminal window or very small text to display properly.\n");

	int ascii[CHAR_MAX+1] = {};

	int c;
	while ((c = getchar()) != EOF) {
		++ascii[c];
	}

	/* print the histogram (horizontal version) */
	/*
	for (int i = ' '; i < '~'; ++i) {
		printf("%3c | ", i);
		for (int j = 0; j < ascii[i]; ++j) {
			putchar('-');
		}
		putchar('\n');
	}
	*/

	/* print the histogram (vertical version) */
	/* determine which character had the greatest number of occurences */
	int highest_frequency = 0;
	for (int i = ' '; i <= '~'; ++i) {
		if (ascii[i] > highest_frequency) {
			highest_frequency = ascii[i];
		}
	}

	/* print the vertical axis and data */
	putchar('\n');
	for (int i = highest_frequency; i > 0; --i) {
		printf("%3d |", i);
		for (int j = ' '; j <= '~'; ++j) {
			if (ascii[j] >= i) {
				//printf(" |");
				putchar(' ');
				putchar(HISTOGRAM_BAR);
			}
			else {
				printf("  ");
			}
		}
		putchar('\n');
	}

	/* print the horizontal axis */
	printf("    -");
	for (int i = ' '; i <= '~'; ++i) {
		printf("--");
	}
	printf("\n     ");
	for (int i = ' '; i <= '~'; ++i) {
		printf("%2c", i);
	}
	putchar('\n');

	return 0;
}
