#ifndef LINEAR_CONGRUENTIAL_GENERATOR_H
#define LINEAR_CONGRUENTIAL_GENERATOR_H
/* lcg_default: a linear congruential generator; generates a pseudorandom
 * number given seed as input, using pre-defined parameters */
unsigned int lcg_default(const unsigned int seed);

/* lcg: a linear congruential generator; generates a pseudorandom number given
 * a seed, slope, intercept, and divisor as input */
unsigned int lcg(const unsigned int seed, const unsigned int slope,
		const unsigned int intercept, const unsigned int divisor);

/* normalize: normalize a randomly-generated integer so it is in the range
 * [0 + intercept, divisor - 1 + intercept] */
unsigned int normalize(const unsigned int rand, const unsigned int divisor,
		const unsigned int intercept);
#endif
