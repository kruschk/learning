#include <stdio.h>
#include <string.h>
#define A 445
#define C 700001
#define M 2097152

/* lcg: a linear congruential generator; generates a pseudorandom number given
 * seed as input */
unsigned int lcg(const unsigned int seed) {
	return (A*seed + C)%M;
}

int main(void) {
	const char consonants[] = "bcdfghjklmnprstvwxz";
	const char vowels[] = "aeiou";
	const unsigned int cons_len = (sizeof consonants - 1)/sizeof consonants[0];
	const unsigned int vow_len = (sizeof vowels - 1)/sizeof vowels[0];
	unsigned int words, seed, i, rand;
	/* get the number of words to generate and the seed value */
	scanf("%u %u\n", &words, &seed);
	rand = seed;
	/* generate the random words */
	for (i = 0; i < words; i++) {
		unsigned int length, j;
		/* get the desired word length */
		scanf("%u", &length);
		/* odd-positioned letters will always be consonants, and
		 * even-positioned letters will be vowels */
		for (j = 1; j <= length; j++) {
			char c;
			/* generate random number */
			rand = lcg(rand);
			/* assign c to a letter in the consonants or vowels array */
			if (j%2 == 0) {
				c = vowels[rand%vow_len];
			}
			else {
				c = consonants[rand%cons_len];
			}
			/* print the letter */
			putchar(c);
		}
		putchar((i == words - 1) ? '\n' : ' ');
	}
	return 0;
}
