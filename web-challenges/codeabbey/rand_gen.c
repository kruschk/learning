#define A 445
#define C 700001
#define M 2097152

/* lcg_default: a linear congruential generator; generates a pseudorandom
 * number given seed as input, using pre-defined parameters */
unsigned int lcg_default(const unsigned int seed) {
	return (A*seed + C)%M;
}

/* lcg: a linear congruential generator; generates a pseudorandom number given
 * seed as input */
unsigned int lcg(const unsigned int seed, const unsigned int slope,
		const unsigned int intercept, const unsigned int divisor) {
	return (slope*seed + intercept)%divisor;
}

/* normalize: normalize a randomly-generated integer so it is in the range
 * [0 + intercept, divisor - 1 + intercept] */
unsigned int normalize(const unsigned int rand, const unsigned int divisor,
		const unsigned int intercept) {
	return rand%divisor + intercept;
}
