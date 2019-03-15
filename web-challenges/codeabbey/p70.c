#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 445
#define C 700001
#define M 2097152
#define WORD_LENGTH 6
#define NUM_WORDS 900000

#define OFFSET(r, c, cols)\
	(r)*(cols) + (c)

/* lcg: a linear congruential generator; generates a pseudorandom number given
 * seed as input */
unsigned int lcg(const unsigned int seed) {
	return (A*seed + C)%M;
}

/* funny_words: generate words words, each of length length, using an lcg with
 * seed seed */
char *funny_words(unsigned int words, unsigned int length, unsigned int seed) {
	const char consonants[] = "bcdfghjklmnprstvwxz";
	const char vowels[] = "aeiou";
	const unsigned int cons_len = (sizeof consonants - 1)/sizeof consonants[0];
	const unsigned int vow_len = (sizeof vowels - 1)/sizeof vowels[0];
	unsigned int i, rand;
	/* word_array is a 2-D array, where each row contains a word and each
	 * column contains a character. The words are null-terminated */
	char *word_array = malloc(words*(length + 1)*sizeof *word_array);
	rand = seed;
	/* generate the random words */
	for (i = 0; i < words; i++) {
		unsigned int j;
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
			/* add the letter to the array */
			word_array[OFFSET(i, j - 1, length+1)] = c;
		}
		/* null-terminate the word */
		word_array[OFFSET(i, length, length+1)] = '\0';
	}
	return word_array;
}

int main(void) {
	unsigned int seed, i, max_pairs, max_pairs_index;
	char *word_array;
	/* get the seed value */
	scanf("%u\n", &seed);
	/* generate the word array */
	word_array = funny_words(NUM_WORDS, WORD_LENGTH, seed);
	/* sort the array; can use strcmp without a wrapper because this is an
	 * array of char, not an array of char * */
	qsort(word_array, NUM_WORDS, (WORD_LENGTH+1)*sizeof *word_array,
			(int (*)(const void *, const void *))strcmp);
	/* count the number of pairs of each word, and save the maximum value and
	 * its index (note: the frequency of a word is just one more than the
	 * number of pairs) */
	max_pairs = 0;
	max_pairs_index = 0;
	for (i = 0; i < NUM_WORDS - 1; i++) {
		unsigned int curr_pairs = 0;
		while (i < NUM_WORDS - 1
				&& strcmp(&word_array[OFFSET(i, 0, WORD_LENGTH+1)],
					&word_array[OFFSET(i+1, 0, WORD_LENGTH+1)]) == 0) {
			curr_pairs++;
			i++;
		}
		/* save the maximum and the index */
		if (curr_pairs > max_pairs) {
			max_pairs = curr_pairs;
			max_pairs_index = i;
		}
	}
	/* print the word at the maximum frequency index */
	printf("%s\n", &word_array[OFFSET(max_pairs_index, 0, WORD_LENGTH+1)]);
	/* free malloc'd memory */
	free(word_array);
	return 0;
}
