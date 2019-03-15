#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 2048
#define N_CARDS 52

/* SWAP: swap two entries in array of type type at positions i and j */
#define SWAP(type, array, i, j)\
	type temp = array[i];\
	array[i] = array[j];\
	array[j] = temp;

/* define a card struct */
struct card {
	char suit;
	char rank;
};

int main(void) {
	/* declare/initialize variables */
	char line[MAX_LINE], *line_p;
	size_t i;
	struct card cards[N_CARDS] = {
		{'C', 'A'}, {'C', '2'}, {'C', '3'}, {'C', '4'}, {'C', '5'}, {'C', '6'},
			{'C', '7'}, {'C', '8'}, {'C', '9'}, {'C', 'T'}, {'C', 'J'},
			{'C', 'Q'}, {'C', 'K'},
		{'D', 'A'}, {'D', '2'}, {'D', '3'}, {'D', '4'}, {'D', '5'}, {'D', '6'},
			{'D', '7'}, {'D', '8'}, {'D', '9'}, {'D', 'T'}, {'D', 'J'},
			{'D', 'Q'}, {'D', 'K'},
		{'H', 'A'}, {'H', '2'}, {'H', '3'}, {'H', '4'}, {'H', '5'}, {'H', '6'},
			{'H', '7'}, {'H', '8'}, {'H', '9'}, {'H', 'T'}, {'H', 'J'},
			{'H', 'Q'}, {'H', 'K'},
		{'S', 'A'}, {'S', '2'}, {'S', '3'}, {'S', '4'}, {'S', '5'}, {'S', '6'},
			{'S', '7'}, {'S', '8'}, {'S', '9'}, {'S', 'T'}, {'S', 'J'},
			{'S', 'Q'}, {'S', 'K'}
	};
	/* get the input line */
	fgets(line, MAX_LINE, stdin);
	line_p = line;
	/* get the next random number and use it as the index to swap two cards */
	for (i = 0; i < N_CARDS; i++) {
		/* modulo N_CARDS ensures the number is in [0, N_CARDS - 1] */
		unsigned int random = strtoul(line_p, &line_p, 10) % N_CARDS;
		SWAP(struct card, cards, i, random);
	}
	/* print the final order of the cards */
	for (i = 0; i < N_CARDS; i++) {
		printf((i == N_CARDS - 1) ? "%c%c\n" : "%c%c ", cards[i].suit,
				cards[i].rank);
	}
	return 0;
}
