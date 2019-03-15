/* In a two's complement number representation, our version of itoa does not
	handle the largest negative number, that is, the value of n equal to
	-(2^(wordsize-1)). Explain why not. Modify it to print that value
	correctly, regardless of the machine on which it runs. */

/* Due to the way two's complement works, the signed integer cannot handle
	numbers up to +(2^(n-1)), but only up to +(2^(n-1)-1). When n is at the
	minimum integer value, setting n = -n causes an integer overflow.  Unsigned
	integers, on the other hand, can handle numbers up to +(2^(n)-1), but
	obviously do not support negatives. */
	
/* Ranges of integers, where n is the number of bits allocated to the integer
	(always remember that 0 is included in the count, hence the -1 on the
	positive side!):
		Signed: [-(2^(n-1)), +(2^(n-1)-1)]
		Unsigned: [0, +(2^(n)-1)] */

#include <C:\Users\Jonah Kruschke\Documents\Programming\C\The C Programming Language\Chapter 3. Control Flow\3.5 Loops - While and For\reverse.c>

/* itoa: convert n characters in s */
void itoa(int n, char s[]) {
	short i, addto, sign;

	addto = 0;
	/* test for limit cases: 0, then overflow, then negative, then positive */
	if (n == 0) {
		sign = 1;
	}
	else if (n << 1 == 0) {
		sign = -1;
		addto = 1;
		n = ~n;
	}
	else if (n < 0) {
		sign = -1;
		n = -n;
	}
	else {
		sign = 1;
	}

	i = 0;
	do {
		/* get next digit */
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);	/* delete it */	

	if (sign < 0) {
		s[i++] = '-';
	}

	s[0] += addto;
	s[i] = '\0';
	reverse(s);
}