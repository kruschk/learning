#include <stdio.h>
#include <stdlib.h>
#define NUM_DICE 5
#define NUM_SIDES 6

/* enumerate the possible scores */
enum score {NONE, PAIR, TWO_PAIR, THREE, FOUR, YACHT, FULL_HOUSE,
	SMALL_STRAIGHT, BIG_STRAIGHT};

/* boolean values */
enum boolean {FALSE, TRUE};

/* interpret_histogram: takes a histogram which counts each dice side in a roll
 * with length (corresponding with the number of possible sides) and translates
 * the counts into a score */
enum score interpret_histogram(unsigned short int histogram[],
		unsigned short int length) {
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

/* print_score: takes a score in and prints its name */
void print_score(enum score score) {
	switch (score) {
		case NONE:
			printf("none");
			break;
		case PAIR:
			printf("pair");
			break;
		case TWO_PAIR:
			printf("two-pairs");
			break;
		case THREE:
			printf("three");
			break;
		case FOUR:
			printf("four");
			break;
		case YACHT:
			printf("yacht");
			break;
		case FULL_HOUSE:
			printf("full-house");
			break;
		case SMALL_STRAIGHT:
			printf("small-straight");
			break;
		case BIG_STRAIGHT:
			printf("big-straight");
			break;
		default:
			printf("none");
			break;
	}
	return;
}

int main(void) {
	int scan_status;
	unsigned short int cases, i;
	/* get the number of cases (each corresponding to a roll of the 5 die) */
	scan_status = scanf("%hu\n", &cases);
	if (scan_status != 1) {
		fprintf(stderr, "error reading the number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* tally the score for each roll */
	for (i = 0; i < cases; i++) {
		unsigned short int roll[NUM_DICE];
		unsigned short int histogram[NUM_SIDES];
		unsigned short int j;
		enum score score = NONE;
		/* make sure the counts in the histogram or all 0 to start */
		for (j = 0; j < NUM_SIDES; j++) {
			histogram[j] = 0;
		}
		/* get the value of each die from the roll */
		for (j = 0; j < NUM_DICE; j++) {
			scan_status = scanf("%hu", &roll[j]);
			if (scan_status != 1) {
				fprintf(stderr, "error reading dice #%hu of roll #%hu\n",
						i + 1, j + 1);
				exit(EXIT_FAILURE);
			}
		}
		/* increment the each dice value in the histogram when that value is
		 * encountered (roll[j]-1 accounts for 0-indexing of the histogram, so
		 * histogram[0] represents a dice roll of 0+1=1, histogram[1] is for a
		 * roll of 1+1=2, etc.) */
		for (j = 0; j < NUM_DICE; j++) {
			histogram[roll[j] - 1]++;
		}
		/* interpret the histogram */
		score = interpret_histogram(histogram, NUM_SIDES);
		/* print result */
		print_score(score);
		putchar((i == cases - 1) ? '\n' : ' ');
	}
	return 0;
}
