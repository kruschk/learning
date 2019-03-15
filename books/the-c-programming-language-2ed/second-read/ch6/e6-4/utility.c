#include "e6-4.h"
#include <string.h>
#include <stdlib.h>

/* make a duplicate of s */
char *strdup(char *s) {
	char *p;

	p = malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

/* reverse: reverse an array of Treeptr in-place */
void reverse(Treeptr p[], size_t n) {
	Treeptr c;
	int i, j;

	for (i = 0, j = n - 1; i < j; i++, j--) {
		c = p[i];
		p[i] = p[j];
		p[j] = c;
	}
}
