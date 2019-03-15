#include <C:\Users\Jonah Kruschke\Documents\Programming\C\The C Programming Language\Chapter 3. Control Flow\3.5 Loops - While and For\reverse.c>

/* itoa: convert n characters in s */
void itoa(int n, char s[]) {
	int i, sign;
	
	/* record sign */
	if ((sign = n) < 0) {
		/* make n positive. This is the step that causes the problem in Exercise 3-4. */
		n = -n;
	}

	i = 0;
	do {
		/* get next digit */
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);	/* delete it */
	
	if (sign < 0) {
		s[i++] = '-';
	}
	
	s[i] = '\0';
	reverse(s);
}