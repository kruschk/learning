#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE], *line_p;
	size_t n_cases, i;
	/* get number of test cases */
	fgets(line, MAX_LINE, stdin);
	n_cases = strtoul(line, NULL, 10);
	/* calculate a score for each test case */
	for (i = 0; i < n_cases; i++) {
		/* declare/initialize variables */
		char c;
		size_t a_count = 0;
		size_t score = 0;
		/* get the next line */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* add scores for all the cards with fixed values, and count aces */
		while ((c = *(line_p++)) != '\0') {
			/* skip whitespace */
			if (isspace(c)) {
				continue;
			}
			/* aces are special, we'll handle them later */
			if (c == 'A') {
				a_count++;
			}
			/* these cards all count for 10 points */
			else if (c == 'T' || c == 'J' || c == 'Q' || c == 'K') {
				score += 10;
			}
			/* all other characters will be digits in the range [2, 9]) */
			else {
				score += c - '0';
			}
		}
		/* first calculate score as though all aces are 11, since we want the
		 * highest possible score */
		score += 11*a_count;
		/* while the score is higher than 21 and we have aces */
		while (score > 21 && a_count != 0) {
			a_count--;
			/* trade out that ace for a score of 1 instead of 11 */
			score -= 11;
			score += 1;
		}
		/* print result */
		if (score > 21) {
			printf((i == n_cases - 1) ? "Bust\n" : "Bust ");
		}
		else {
			printf((i == n_cases - 1) ? "%lu\n" : "%lu ", score);
		}
	}
	return 0;
}
