#include <stdio.h>
#include <stdlib.h>
#define NUM_DICE 5
#define NUM_SIDES 6

enum score {NONE, PAIR, TWO_PAIR, THREE, FOUR, YACHT, FULL_HOUSE,
	SMALL_STRAIGHT, BIG_STRAIGHT};

enum boolean {FALSE, TRUE};

enum score interpret_histogram(unsigned short int histogram[], unsigned short int length) {
	unsigned short int i, pairs, threes;
	enum boolean flag;
	/* check for a big straight (sequence from 2 to 6) */
	flag = TRUE;
	for (i = 1; i < length; i++) {
		if (!histogram[i]) {
			flag = FALSE;
			break;
		}
	}
	if (flag) {
		return BIG_STRAIGHT;
	}
	/* check for a small straight (sequence from 1 to 5) */
	flag = TRUE;
	for (i = 0; i < length - 1; i++) {
		if (!histogram[i]) {
			flag = FALSE;
			break;
		}
	}
	if (flag) {
		return SMALL_STRAIGHT;
	}
	/* check for a yacht, full-house, four, three, two-pair, or pair */
	pairs = 0;
	threes = 0;
	for (i = 0; i < length; i++) {
		if (histogram[i] == 5) {
			/* must be a yacht */
			return YACHT;
		}
		else if (histogram[i] == 4) {
			/* must be a four */
			return FOUR;
		}
		else if (histogram[i] == 3) {
			/* could be a full-house or a three */
			threes++;
		}
		else if (histogram[i] == 2) {
			/* could be a full-house, a pair, or a two-pair */
			pairs++;
		}
	}
	if (pairs && threes) {
		return FULL_HOUSE;
	}
	else if (pairs == 2) {
		return TWO_PAIR;
	}
	else if (threes) {
		return THREE;
	}
	else if (pairs) {
		return PAIR;
	}
	/* default to NONE */
	return NONE;
}

int main(void) {
	int scan_status;
	unsigned short int cases, i;
	scan_status = scanf("%hu\n", &cases);
	if (scan_status != 1) {
		fprintf(stderr, "error reading the number of cases\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < cases; i++) {
		unsigned short int roll[NUM_DICE];
		unsigned short int histogram[NUM_SIDES];
		unsigned short int j;
		enum score score = NONE;
		for (j = 0; j < NUM_SIDES; j++) {
			histogram[j] = 0;
		}
		for (j = 0; j < NUM_DICE; j++) {
			scan_status = scanf("%hu", &roll[j]);
			if (scan_status != 1) {
				fprintf(stderr, "error reading dice #%hu of roll #%hu\n",
						i + 1, j + 1);
				exit(EXIT_FAILURE);
			}
		}
		for (j = 0; j < NUM_DICE; j++) {
			histogram[roll[j] - 1]++;
		}
		for (j = 0; j < NUM_SIDES; j++) {
			printf("%hu ", histogram[j]);
		}
		/* interpret the histogram */
		score = interpret_histogram(histogram, NUM_SIDES);
		/* print result */
		print_score(score);
		putchar('\n');
	}
	return 0;
}
