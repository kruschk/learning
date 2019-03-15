#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* swap two elements of a string in-place */
#define SWAP(string, i, j)\
	temp = string[i];\
	string[i] = string[j];\
	string[j] = temp;

enum boolean {FALSE, TRUE};

/* factorial: returns the factorial of a nonnegative integer */
unsigned int factorial(unsigned int n) {
	unsigned int i, result = 1;
	for (i = 2; i <= n; i++) {
		result *= i;
	}
	return result;
}

/* narayana: uses Narayana Pandita's algorithm to transform a string into its
 * next (next in terms of lexicographical order) permutation */
enum boolean narayana(char *str) {
	unsigned int i, j;
	int last_pos = strlen(str) - 1;
	char temp;
	/* find the largest index i such that str[i] < str[i + 1] */
	i = last_pos - 1;
	while (i != 0 && str[i] >= str[i + 1]) {
		i--;
	}
	/* if no such index exists, this permutation is the last permutation */
	if (str[i] >= str[i + 1]) {
		return FALSE;
	}
	/* find the largest index j greater than i, such that str[i] < str[j] */
	j = last_pos;
	while (j > i && str[i] >= str[j]) {
		j--;
	}
	/* swap these two values */
	SWAP(str, i, j);
	/* reverse the string from the i + 1 position to the end (inclusive) */
	for (i++, j = last_pos; i < j; i++, j--) {
		SWAP(str, i, j);
	}
	return TRUE;
}

int main(void) {
	char str[] = "ABCDEFGHIJKL";
	unsigned int cases, i;
	char (*permutations)[sizeof str/sizeof *str];
	/* the number of possible permutations */
	const unsigned int n_perms = factorial((sizeof str - 1)/sizeof *str);
	/* get the number of cases */
	if (1 != scanf("%u\n", &cases)) {
		fprintf(stderr, "error reading the number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* generate an array of all the possible permutations (very expensive!) */
	permutations = malloc(n_perms*sizeof *permutations);
	for (i = 0; i < n_perms; i++) {
		strcpy(permutations[i], str);
		narayana(str);
	}
	/* from the given index in each case, determine the string from which
	 * Geeglo must begin */
	for (i = 0; i < cases; i++) {
		unsigned int index;
		/* get the index */
		if (1 != scanf("%u\n", &index)) {
			fprintf(stderr, "error reading the input index on on line %u\n",
					i + 2);
			exit(EXIT_FAILURE);
		}
		/* if the index is within acceptable range */
		if (index < n_perms) {
			/* print it */
			printf((i == cases - 1) ? "%s\n" : "%s ", permutations[index]);
		}
		else {
			fprintf(stderr, "index out of possible range on line %u\n", i + 2);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
