#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_round.h"
#define MAX_LINE 2048
#define N_CASES 3
#define N_NUMS 100
#define MAX_POSSIBLE_ROLL (12*5 + 1)

/* minmax: finds the minimum and maximum elements of an array and stores them
 * in *min and *max */
void minmax(unsigned int array[], size_t n, unsigned int *min,
		unsigned int *max) {
	size_t i;
	*min = UINT_MAX;
	*max = 0;
	for (i = 0; i < n; i++) {
		if (array[i] < *min) {
			*min = array[i];
		}
		if (array[i] > *max) {
			*max = array[i];
		}
	}
}

/* average: computes the average of an array of unsigned ints */
/*double average(unsigned int array[], size_t n) {
	unsigned int sum = 0;
	size_t i;
	for (i = 0; i < n; i++) {
		sum += array[i];
	}
	return sum/n;
}*/

/* count_frequencies: count the number of occurrences of each value in array
 * and store the counts in freq at the appropriate index. freq must be large
 * enough to store a count for the maximum value in array */
/*void count_frequencies(unsigned int array[], size_t n, unsigned int freq[]) {
	size_t i;
	for (i = 0; i < n; i++) {
		freq[array[i]]++;
	}
	return;
}*/

/* draw_histogram: draw a simple histogram with bins on the y-axis and counts
 * on the x-axis. This is reversed from the normal convention for histograms,
 * but drawing it properly is a pain in the ass. */
/*void draw_histogram(unsigned int freq[], size_t n) {
	size_t i;
	for (i = 0; i < n; i++) {
		printf("%3lu|", i);
		while (freq[i] != 0) {
			putchar('-');
			freq[i]--;
		}
		putchar('\n');
	}
}*/

int main(void) {
	/* declare iteration variable */
	size_t i;
	/* determine the likely number of dice and number of sides for each set of
	 * rolls */
	for (i = 0; i < N_CASES; i++) {
		/* declare variables */
		char line[MAX_LINE], *line_p;
		unsigned int rolls[N_NUMS], min, max, n_dies, n_sides;
		size_t j;
		/* get the next line, with all the rolls */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* put the roll sums into the rolls array */
		for (j = 0; j < N_NUMS; j++) {
			rolls[j] = strtoul(line_p, &line_p, 10);
		}
		/* determine the min and max values of rolls */
		minmax(rolls, N_NUMS, &min, &max);
		/* guesstimate the number of dies and sides from known information */
		n_dies = custom_round(min);
		n_sides = custom_round(max/n_dies);
		/* print results, formatted as desired */
		printf((i == N_CASES - 1) ? "%ud%u\n" : "%ud%u ", n_dies, n_sides);
	}
	return 0;
}
