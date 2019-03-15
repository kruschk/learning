#include <stdio.h>

int main(void) {
	/* initialize suits and ranks arrays to map indices to names */
	const char *suits[] = {"Clubs", "Spades", "Diamonds", "Hearts"};
	const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
		"Jack", "Queen", "King", "Ace"};
	/* declare iteration variables */
	unsigned short int n_cards, i;
	scanf("%hu\n", &n_cards);
	/* determine the card for each input number */
	for (i = 0; i < n_cards; i++) {
		/* declare card variables */
		unsigned short int card, suit_index, rank_index;
		/* get a card */
		scanf("%hu", &card);
		/* calculate the respective indices */
		suit_index = card/13;
		rank_index = card%13;
		/* print the result */
		printf("%s-of-%s", ranks[rank_index], suits[suit_index]);
		putchar((i == n_cards - 1) ? '\n' : ' ');
	}
	return 0;
}
