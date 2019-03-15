/* CodeAbbey problem 36
 * THIS PROGRAM DOESN'T WORK YET, and it's a monstrosity. I ended up solving the
 * problem by hand, and the algorithm I came up with could be implemented with
 * some more effort. It's on a piece of paper with CodeAbbery Problem 36
 * written near the middle of the page (holes are on the right side, so back of
 * the sheet).
 * An attempt at a description of the procedure:
 * You start each iteration by crossing off all the numbers that have 0 as an
 * answer (position is important). Then you add up the probability of a number
 * being in a position, where the probability for each digit is
 * answer/(num_digits - count(digits_known_to_be_wrong)). So, if we have 4
 * digits, and 9 in the most significant digit position is crossed off, and 3
 * in the least significant digit position is crossed off, and the answer was
 * 1, then we add a probability of 1/(4 - (1+1)) = 1/2 to the other two digits.
 * When one of the numbers in a digit position has a probability greater than 1
 * of being correct, we assign it to the appropriate position in the result and
 * cross off that row, reducing the number of digits that we are dealing with
 * by 1. Then, we subtract one from all the answers that contained that digit
 * in that position. This procedure is repeated until all digits are known. The
 * remaining probabilities must be reset to zero on each iteration. */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024 /* arbitrary maximum line length */
#define MAX_CASES 128 /* arbitrary max num of test cases (i.e. num guesses) */
#define NUM_DIGITS 4 /* number of digits in the secret number */
#define NUM_SYMBOLS 10 /* num of symbols that we're working with [0, 9] here */

enum bool {FALSE, TRUE};
enum possible_states {UNKNOWN = 0, NO, MAYBE, YES};

/* answer_is_incomplete: returns TRUE if any of the entries in answer are
 * unchanged from their initial values */
enum bool answer_is_incomplete(char answer[]) {
	size_t i;
	for (i = 0; i < NUM_DIGITS; i++) {
		if (answer[i] == -1) {
			return TRUE;
		}
	}
	return FALSE;
}

int main(void) {
	/* declare variables */
	char input[MAX_LINE]; /* for collecting a line of input */
	size_t n_cases, i, j;
	unsigned char input_matrix[MAX_CASES][NUM_DIGITS + 1]; /* organizes all the input into a matrix */
	enum possible_states helper_matrix[NUM_DIGITS][NUM_SYMBOLS] = {{UNKNOWN}};
	char answer[NUM_DIGITS];
	/* initialize the answer array to -1 */
	for (i = 0; i < NUM_DIGITS; i++) {
		answer[i] = -1;
	}
	/* get the number of cases from the first line */
	fgets(input, MAX_LINE, stdin);
	n_cases = strtoul(input, NULL, 10);
	/* populate the input matrix. The last column contains the number of
	 * correct values in that row, and the other columns contain the entries
	 * themselves */
	for (i = 0; i < n_cases; i++) {
		fgets(input, MAX_LINE, stdin);
		for (j = 0; j < NUM_DIGITS + 1; j++) {
			if (j == NUM_DIGITS) {
				input_matrix[i][j] = input[j+1] - '0';
			}
			else {
				input_matrix[i][j] = input[j] - '0';
			}
		}
	}
	/*  */
	i = 0;
	while (answer_is_incomplete(answer)) {
		/* declare variables */
		char n_correct;
		size_t k, count;
		i++;
		i %= n_cases;
		n_correct = input_matrix[i][NUM_DIGITS];
		/* if no correct values in the guess, we can set those to NO */
		if (n_correct == 0) {
			for (j = 0; j < NUM_DIGITS; j++) {
				/* skip if we already have the answer */
				if (answer[j] != -1) {
					continue;
				}
				helper_matrix[j][(int)input_matrix[i][j]] = NO;
			}
		}
		else {
			for (j = 0; j < NUM_DIGITS; j++) {
				/* skip if we already have the answer */
				if (answer[j] != -1) {
					continue;
				}
				helper_matrix[j][(int)input_matrix[i][j]] = MAYBE;
			}
		}
		count = 0;
		for (j = 0; j < NUM_DIGITS; j++) {
			/* skip if we already have the answer */
			if (answer[j] != -1) {
				continue;
			}
			/* count the number of MAYBEs in this row */
			for (k = 0; k < NUM_SYMBOLS; k++) {
				if (helper_matrix[j][k] == MAYBE) {
					count++;
				}
			}
			/* if there was exactly one MAYBE, that value was correct */
			if (count == 1) {
				/* find the lone MAYBE */
				k = 0;
				for (k = 0; k < NUM_SYMBOLS; k++) {
					/* replace it with a YES and add the value to answer in the
					 * appropriate location */
					if (helper_matrix[j][k] == MAYBE) {
						size_t i;
						helper_matrix[j][k] = YES;
						answer[j] = k;
						/* subtract 1 from the last column of input_matrix for
						 * all rows in which the value at the current column
						 * matches k */
						for (i = 0; i < n_cases; i++) {
							if (input_matrix[i][j] == k && input_matrix[i][NUM_DIGITS] > 0) {
								input_matrix[i][NUM_DIGITS]--;
							}
						}
					}
					/* all other values in the row become NOs */
					else {
						helper_matrix[j][k] = NO;
					}
				}
			}
		}
	}
	/* print the column indices of helper_matrix */
	for (i = 0; i < NUM_SYMBOLS; i++) {
		printf("%2lu ", i);
	}
	putchar('\n');
	/* print the final helper_matrix */
	for (i = 0; i < 3; i++) {
		size_t j;
		for (j = 0; j < NUM_SYMBOLS; j++) {
			printf("%2hd ", helper_matrix[i][j]);
		}
		putchar('\n');
	}
	/* print result */
	for (i = 0; i < NUM_DIGITS; i++) {
		printf("%hd", answer[i]);
	}
	putchar('\n');
	return 0;
}
