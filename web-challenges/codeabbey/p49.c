#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(void) {
	/* declare variables */
	char line[MAX_LINE];
	size_t n_games, i;
	/* get number of games */
	fgets(line, MAX_LINE, stdin);
	n_games = strtoul(line, NULL, 10);
	/* for each game, play all rounds and determine the winner */
	for (i = 0; i < n_games; i++) {
		/* declare variables */
		char *line_p;
		char a, b, winner;
		size_t a_wins, b_wins;
		/* get the next line */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* play the game by playing each round */
		a_wins = 0;
		b_wins = 0;
		while (*line_p != '\0') {
			/* a is the first player's throw */
			a = *line_p;
			line_p++;
			/* b is the second player's throw */
			b = *line_p;
			line_p++;
			/* determine who won this round; rock beats scissors, but loses to
			 * paper */
			if (a == 'R') {
				if (b == 'S') {
					a_wins++;
				}
				else if (b == 'P') {
					b_wins++;
				}
			}
			/* paper beats rock, but loses to scissors */
			else if (a == 'P') {
				if (b == 'R') {
					a_wins++;
				}
				else if (b == 'S') {
					b_wins++;
				}
			}
			/* scissors beats paper, but loses to rock */
			else if (a == 'S') {
				if (b == 'P') {
					a_wins++;
				}
				else if (b == 'R') {
					b_wins++;
				}
			}
			/* in the case of a draw, do nothing */
			else {
				;
			}
			/* skip space */
			while (isspace(*line_p)) {
				line_p++;
			}
		}
		/* player 1 wins */
		if (a_wins > b_wins) {
			winner = '1';
		}
		/* player 2 wins */
		else if (b_wins > a_wins) {
			winner = '2';
		}
		/* game was a draw */
		else {
			winner = '0';
		}
		/* print result */
		printf((i == n_games - 1) ? "%c\n" : "%c ", winner);
	}
	return 0;
}
