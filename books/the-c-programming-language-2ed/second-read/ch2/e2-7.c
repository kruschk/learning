#include <stdio.h>

int invert(const unsigned int x, const unsigned int p, const unsigned int n);

int main(void) {
	int x = 0261;
	int p = 4;
	int n = 3;

	int result = invert(x, p, n);
	printf("result (in octal): %o\n", result);

	return 0;
}

/******************************************************************************
 * invert: returns x with the n bits that begin at position p inverted (0 set
 * to 1 and 1 set to 0).The comments use, as an illustrative example:
 *     x = 0261; == 0b10110001
 *     p = 4;
 *     n = 3;
 * The example uses 8-bit registers, but the logic should work for any size.
 *****************************************************************************/
int invert(unsigned int x, const unsigned int p, const unsigned int n) {
	int xmask = 0; /* xmask == 0b00000000 */
	int temp;

	/* generate the xmask */
	size_t i;
	for (i = 0; i < n; ++i) {
		xmask = xmask | 1;
		if (i < n - 1) {
			xmask = xmask << 1;
		}
	}                             /* xmask == 0b00000111 */
	xmask = xmask << (p - n + 1); /* xmask == 0b00011100 */
	
	temp = x & xmask;    /* temp == 0b00010000 */
	temp = temp ^ xmask; /* temp == 0b00001100 */

	x = x & ~xmask; /* x == 0b10100001 */
	x = x ^ temp;   /* x == 0b10101101 */

	return x;
}
