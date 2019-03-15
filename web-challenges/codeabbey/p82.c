#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD 1024

/* max: returns the maximum of two values */
unsigned int max(unsigned int a, unsigned int b) {
	return a > b ? a : b;
}

/* min: returns the minimum of two values */
unsigned int min(unsigned int a, unsigned int b) {
	return a < b ? a : b;
}

/* triple_min: returns the minimum of three values */
unsigned int triple_min(unsigned int a, unsigned int b, unsigned int c) {
	if (a < b) {
		if (a < c) { /* a < b && a < c */
			return a;
		}
		else { /* a < b && c <= a */
			return c;
		}
	}
	else { /* b <= a */
		if (b < c) { /* b <= a && b < c */
			return b;
		}
		else { /* b <= a && c <= b */
			return c;
		}
	}
}

/* levenshtein: returns the Levenshtein distance of two strings with given
 * lengths. This function works, but is ridiculously slow for strings longer
 * than ~10 characters.*/
unsigned int levenshtein(const char *str_a, const char *str_b,
		const unsigned int len_a, const unsigned int len_b) {
	if (min(len_a, len_b) == 0) {
		return max(len_a, len_b);
	}
	else {
		return triple_min(levenshtein(str_a, str_b, len_a - 1, len_b) + 1,
				          levenshtein(str_a, str_b, len_a, len_b - 1) + 1,
				          levenshtein(str_a, str_b, len_a - 1, len_b - 1)
				          + !(str_a[len_a - 1] == str_b[len_b - 1]));
	}
}

#define OFFSET(matrix, r, c) (r)*matrix.width + (c)

/* a matrix object */
struct matrix {
	unsigned int height;
	unsigned int width;
	unsigned int *element;
};

/* levenshtein_table: returns the Levenshtein distance of two strings using the
 * table method */
unsigned int levenshtein_table(const char *str_a, const char *str_b) {
	unsigned int i, j;
	struct matrix table;
	unsigned int distance;
	/* we want the table dimensions to be 1 more than the lengths of the
	 * strings */
	table.height = strlen(str_a) + 1;
	table.width = strlen(str_b) + 1;
	table.element = malloc(table.height*table.width*sizeof *table.element);
	/* set all elements in the table to 0 (I don't think this step is
	 * necessary since the table is built column-by-column, and the build
	 * procedure only refers to values before it (i.e. to the left and
	 * above it)) */
	/*for (i = 0; i < table.height; i++) {
		for (j = 0; j < table.width; j++) {
			table.element[OFFSET(table, i, j)] = 0;
		}
	}*/
	/* set each element in the first row to its index */
	for (j = 0; j < table.width; j++) {
		table.element[OFFSET(table, 0, j)] = j;
	}
	/* set each element in the first column to its index */
	for (i = 0; i < table.height; i++) {
		table.element[OFFSET(table, i, 0)] = i;
	}
	/* compute the Levenshtein distance for each element using values already
	 * stored in the table */
	for (j = 1; j < table.width; j++) {
		for (i = 1; i < table.height; i++) {
			table.element[OFFSET(table, i, j)] =
				triple_min(table.element[OFFSET(table, i - 1, j    )] + 1,
						   table.element[OFFSET(table, i,     j - 1)] + 1,
						   table.element[OFFSET(table, i - 1, j - 1)]
						   + !(str_a[i - 1] == str_b[j - 1]));
		}
	}
	/* the Levenshtein distance is the value stored in the last element of the
	 * matrix (i.e. the bottom-rightmost value) */
	distance = table.element[OFFSET(table, table.height - 1, table.width - 1)];
	/* free allocated memory */
	free(table.element);
	/* return the distance */
	return distance;
}

int main(void) {
	unsigned int cases, i;
	/* get the number of cases from input */
	if (1 != scanf("%u\n", &cases)) {
		fprintf(stderr, "error reading the number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* for each case, compute the Levenshtein distance between the two words */
	for (i = 0; i < cases; i++) {
		char str_a[MAX_WORD], str_b[MAX_WORD];
		unsigned int distance;
		/* get the two words */
		if (2 != scanf(" %s %s \n", str_a, str_b)) {
			fprintf(stderr, "error reading string line %u\n", i + 2);
			exit(EXIT_FAILURE);
		}
		/* compute the Levenshtein distance using the table method */
		distance = levenshtein_table(str_a, str_b);
		/* print the results */
		printf((i == cases - 1) ? "%u\n" : "%u ", distance);
	}
	return EXIT_SUCCESS;
}
