#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 4096

int expand(const char s1[], char s2[]);
int expand_internal(char s2[], int *i, int *j, int from, int to);

int main(void) {
	char s1[] = "-c-r, a-z, 0-9, a-3, 1-p, 5-8-i-j, 9-3, p-g\n";
	char s2[MAX_LINE];

	int status = expand(s1, s2);

	printf("String before expansion: %s", s1);
	if (status >= 0) {
		printf("String after expansion: %s", s2);
	}

	return 0;
}

/******************************************************************************
 * expand: converts string a-z to abc...xyz or 0-9 to 012...789.
 *****************************************************************************/
int expand(const char s1[], char s2[]) {
	int i, j;
	for (i = 0, j = 0; s1[i] != '\0'; ++i, ++j) {
		char from = s1[i];
		char to = s1[i+2];
		if (isalpha(from) && (s1[i+1] == '-') && isalpha(to)) {
			expand_internal(s2, &i, &j, from, to);
		}
		else if (isdigit(from) && (s1[i+1] == '-' && isdigit(to))) {
			expand_internal(s2, &i, &j, from, to);
		}
		else {
			s2[j] = s1[i];
		}
	}
	s2[j] = '\0';
	
	return 0;
}

/******************************************************************************
 * expand_internal: does the actual legwork of converting the string a-z to
 * abc...xyz or 0-9 to 012...789 once the necessary characters or digits are
 * known.
 *****************************************************************************/
int expand_internal(char s2[], int *i_pos, int *j_pos, int from, int to) {
	/* create a temporary variable so we don't have to dereference a pointer a
	 * whole bunch of times */
	int j = *j_pos;
	if (from < to) {
		while (from <= to) {
			s2[j] = from;
			++j;
			++from;
		}
		--j;
	}
	else if (from > to) {
		while (from >= to) {
			s2[j] = from;
			++j;
			--from;
		}
		--j;
	}
	else {
		s2[j] = from;
		++j;
		s2[j] = '-';
		++j;
		s2[j] = to;
	}

	/* add two to the value of i_pos so that the "-x" (where x is a number or
	 * character) is skipped */
	(*i_pos) += 2;

	/* set the value of j_pos to j, so that escape resumes where it's supposed
	 * to */
	*j_pos = j;

	return 0;
}
