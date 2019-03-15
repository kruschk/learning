#ifndef GEN_PRIMES_H
#define GEN_PRIMES_H
enum boolean {FALSE, TRUE};
/* is_prime: returns TRUE if the given number is a prime, FALSE otherwise. Uses
 * some Project Euler problem #7 magic. */
enum boolean is_prime(const unsigned int n);
/* generate_prime_array: write all the primes up to max_prime into the array
 * primes, which has initial length primes_size, and store the occupied length
 * of the array in end_length. */
void generate_prime_array(unsigned int *primes[], size_t *primes_size,
		size_t *end_length, const unsigned int max_prime);
#endif
