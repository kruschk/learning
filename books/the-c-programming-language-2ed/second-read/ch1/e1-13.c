#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

#define WORD_LENGTH_MAX 32

/* This program prints a histogram of the lengths of words in its input.
 *
 * It currently uses a fixed size for the maximum word length; this could be
 * improved by using dynamic memory allocation (malloc()).
 *
 * The histogram that is printed does not adjust the horizontal axis for
 * different maximum word lengths, it is always the same horizontal size. 
 *
 * The vertical axis labels are a little sloppy, but probably clear enough.
 * The horizontal axis labels are not bins, as histograms normally are, but
 * this isn't the end of the world because the word length counts are integer
 * values.
 */
int main(void) {
	/* count lengths of words in the input and store in an array */
	int c;
	int state = OUT;
	int num_chars[WORD_LENGTH_MAX] = {};
	int word_length = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			++num_chars[word_length];
			word_length = 0;
		}
		else if (state == OUT) {
			state = IN;
			++word_length;
		}
		else {
			++word_length;
		}
	}

	/* print the histogram (horizontal version) */
	/*
	for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
		printf("%3d | ", i);
		for (int j = 0; j < num_chars[i]; ++j) {
			putchar('-');
		}
		putchar('\n');
	}
	*/

	/* print the histogram (vertical version) */
	/* determine which word length had the highest number of
	 * occurences */
	int highest_frequency = 0;
	for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
		if (num_chars[i] > highest_frequency) {
			highest_frequency = num_chars[i];
		}
	}

	/* print the vertical axis and data */
	putchar('\n');
	for (int i = highest_frequency; i > 0; --i) {
		printf("%3d |", i);
		for (int j = 0; j < WORD_LENGTH_MAX; ++j) {
			if (num_chars[j] >= i) {
				printf("  |");
			}
			else {
				printf("   ");
			}
		}
		putchar('\n');
	}

	/* print the horizontal axis */
	printf("    -");
	for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
		printf("---");
	}
	printf("\n     ");
	for (int i = 0; i < WORD_LENGTH_MAX; ++i) {
		printf("%3d", i);
	}
	putchar('\n');

	return 0;
}
