/* Exercise 4-2. Extend atof to handle scientific notation of the form
	123.45e-6 where a floating-point number may be followed by e or E and an
	optionally signed exponent. */

#include <ctype.h>

/* atof: convert string s to double */
double atof(char s[]) {
	double val, power;
	int i, sign;
	
	/* skip leading white space */
	for (i = 0; isspace(s[i]); i++) {
		;
	}
	
	/* positive or negative? */
	sign = (s[i] == '-') ? -1 : 1;
	
	/* skip the sign if present */
	if (s[i] == '+' || s[i] == '-') {
		i++;
	}
	
	/* add the digits up that come before the decimal, i.e. 1*10^2 + 1*10^1 +
		1*10^0 for 111.111 */
	for (val = 0.0; isdigit(s[i]); i++) {	
		val = 10.0 * val + (s[i] - '0');
	}
	
	/* skip the decimal */
	if (s[i] == '.') {
		i++;
	}
	
	/* include the digits after the decimal, i.e. 111.111 becomes 1*10^5 +
		1*10^4 + 1*10^3 + 1*10^2 + 1*10^1 + 1*10^0 (or 111,111), power becomes
		10^3 (or 1000). */
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	
	/* support for scientific notation. Only supports single-digit exponents. */
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		int j;
		if (s[i] == '-') {
			i++;
			for (j = 0; j < s[i] - '0'; j++) {
				power *= 10.0;
			}
		}
		else if (s[i] == '+') {
			i++;
			for (j = 0; j < s[i] - '0'; j++) {
				power /= 10.0;
			}
		}
		else {
			for (j = 0; j < s[i] - '0'; j++) {
				power /= 10.0;
			}
		}
	}

	/* take the huge number, negate if necessary, and divide it by whatever
		power necessary to make it into the correct fraction. */
	return sign * val / power;
}