#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_WORD 128
#define ALPHABET 26

enum boolean {FALSE, TRUE};

/* shift: shift a string encoded with a Caesar cipher by shift to decode it */
void shift(char *encoded, char *decoded, int shift) {
	unsigned int i;
	unsigned int length = strlen(encoded);
	for (i = 0; i < length - 1; i++) {
		decoded[i] = tolower(encoded[i]);
		if (!isspace(decoded[i]) && decoded[i] != '\n' && decoded[i] != '\0') {
			decoded[i] = (decoded[i] - 'a' + shift)%('z' - 'a' + 1) + 'a';
		}
	}
	decoded[i] = '\0';
}

/* get_word: get a word from line_p and store it in word */
enum boolean get_word(char *word, const char **line_p) {
	int i;
	/* skip leading whitespace and punctuation */
	while (isspace(**line_p) || ispunct(**line_p)) {
		++*line_p;
	}
	/* copy chars until we reach the next whitespace, punctuation, or \0 */
	for (i = 0; !isspace(**line_p) && !ispunct(**line_p) && **line_p != '\0';
			i++) {
		word[i] = **line_p;
		++*line_p;
	}
	word[i] = '\0';
	/* if i still equals 0, nothing was copied */
	if (i == 0) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/* recognize_words: tries to recognize all the words in line and returns the
 * fraction of the total number of words that were recognized */
double recognize_words(const char *line) {
	char word[MAX_WORD];
	char command[MAX_LINE];
	int recognized = 0;
	int total = 0;
	while (get_word(word, &line) == TRUE) {
		/* compose the grep command that is used to search our dictionary */
		command[0] = '\0';
		strcat(command, "grep -w -q ");
		strcat(command, word);
		strcat(command, " /usr/share/dict/american-english");
		/* if grep returns 0, that means there was a match */
		if (system(command) == 0) {
			recognized++;
		}
		/* increment the total */
		total++;
	}
	/* return the fraction of words that were recognized */
	return (double)recognized/(double)total;
}

int main(void) {
	char encoded[MAX_LINE], decoded[MAX_LINE];
	int i, cases;
	/* get the number of cases */
	scanf("%d\n", &cases);
	/* crack the cipher for each case */
	for (i = 0; i < cases; i++) {
		enum boolean solved = FALSE;
		int j, key = 0, words;
		/* get the encoded line of input */
		fgets(encoded, MAX_LINE, stdin);
		/* try and crack it by trying each possible shift */
		for (j = 1; !solved && j < ALPHABET; j++) {
			/* Shift the encoded message. Don't need to try j = 0 because
			 * that's the encoded message itself; we only do 25 shifts max */
			shift(encoded, decoded, j);
			/* if more 50 % or more of the words are in our dictionary, it's
			 * likely that we've deciphered the message */
			if (recognize_words(decoded) >= 0.5) {
				solved = TRUE;
			}
		}
		/* save the shift key that solved the message */
		if (solved) {
			key = ALPHABET - (j - 1);
		}
		/* truncate the message after third word, output is more interesting if
		 * this block is commented out */
		/*for (j = 0, words = 0; decoded[j] != '\0'; j++) {
			if (isspace(decoded[j]) || ispunct(decoded[j])) {
				words++;
				if (words == 3) {
					decoded[j] = '\0';
				}
			}
		}*/
		/* print the result */
		printf((i == cases - 1) ? "%s %d\n" : "%s %d ", decoded, key);
	}
	return 0;
}
