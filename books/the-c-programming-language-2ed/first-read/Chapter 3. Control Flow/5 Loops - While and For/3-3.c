/* Exercise 3-3. Write a function expand(s1, s2) that expands the shorthand
	notations like a-z in the string s1 into the equivalent complete list
	abc...xyz in s2. Allow for letters of either case and digits, and be
	prepared to handle cases like a-b-c (should print abc) and a-z0-9 (should
	print abc...xyz0123456789) and -a-z (should print -abc...xyz). Arrange that
	a leading or trailing - is taken literally (i.e. will be copied directly to
	s2). */

#include <stdio.h>

void expand(char shorthand[], char expanded[]);

int main(void) {
	char s1[] = "a-b-c";
	char s2[] = "a-z0-9";
	char s3[] = "-a-z";
	char strout[100];

	expand(s1, strout);
	printf("%s\n", strout);

	expand(s2, strout);
	printf("%s\n", strout);

	expand(s3, strout);
	printf("%s\n", strout);

	return 0;
}

void expand(char s1[], char s2[]) {
	/* i goes with s1, j goes with s2 */
	int i, j;
	i = j = 0;
	/* until we reach the end of the first array */
	while (s1[i] != '\0') {
		/* if the next character is a dash */
		if (s1[i] == '-') {
			/* if alphabetical||numeric && character after the dash comes after
			the one before the dash alphabetically||numerically */
			if  (( (s1[i-1] >= 'a' && s1[i+1] <= 'z')
				|| (s1[i-1] >= 'A' && s1[i+1] <= 'Z')
				|| (s1[i-1] >= '0' && s1[i+1] <= '9')) && s1[i+1] > s1[i-1]) {
				/* then copy the expanded characters to the second string */
				for (char c = s1[i-1] + 1; c <= s1[i+1]; c++) {
					s2[j++] = c;
				}
				/* skip the dash and the following character */
				i += 1;
			}
			/* otherwise, just copy the dash to the second string */
			else {
				s2[j++] = s1[i];
			}
		}
		/* otherwise, just copy the character to the second string */
		else {
			s2[j++] = s1[i];
		}
		/* next i */
		i++;
	}
	/* null-terminate string 2. */
	s2[j] = '\0';
}