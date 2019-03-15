#include <stdio.h>
#define DIGITS 4

int main(void) {
	unsigned short int i, n_guess;
	char ans[DIGITS+1];
	/* collect the answer */
	scanf("%s %hu", ans, &n_guess);
	for (i = 0; i < n_guess; i++) {
		/* declare/initialize variables */
		char guess[DIGITS+1];
		unsigned short int j;
		unsigned short int correct = 0;
		unsigned short int correct_wrong_pos = 0;
		scanf("%s ", guess);
		/* count correct characters in the correct positions and correct
		 * characters in the wrong positions */
		for (j = 0; j < DIGITS; j++) {
			if (guess[j] == ans[j]) {
				/* count correct characters in correct positions */
				correct++;
			}
			else {
				/* count correct characters that are in the wrong position */
				unsigned short int k;
				for (k = 0; k < DIGITS; k++) {
					if (guess[k] == ans[j] && k != j) {
						correct_wrong_pos++;
					}
				}
			}
		}
		/* print results */
		printf((i == n_guess - 1) ? "%hu-%hu\n" : "%hu-%hu ", correct,
				correct_wrong_pos);
	}
	return 0;
}
