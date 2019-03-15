#include <stdio.h>

int setbits(const int x, const unsigned int p, const unsigned int n, const int y);

int main(void) {
	int x = 0261;
	int y = 0352;
	int p = 4;
	int n = 3;

	int result = setbits(x, p, n, y);
	printf("result (in octal): %o\n", result);

	return 0;
}

/******************************************************************************
 * setbits: returns x with the n bits that begin at position p set to the
 * rightmost n bits of y while leaving the other bits unchanged. The comments
 * use, as an illustrative example:
 *     x = 0261; == 0b10110001
 *     p = 4;
 *     n = 3;
 *     y = 0352; == 0b11101010
 * The example uses 8-bit registers, but the logic should work for any size.
 *****************************************************************************/
int setbits(const int x, const unsigned int p, const unsigned int n, const int y) {
	int xmask = 0;
	int ymask;

	int xnew;
	int ynew;

	size_t i;

	/* the position must be greater than or equal to the number of bits */
	if (p < n) {
		printf("error: setbits(): n must be less than p\n");
		return -1;
	}
	else if (n == 0) {
		printf("error: setbits(): n must be greater than 0\n");
		return -1;
	}
	/* make sure p fits in x to avoid scary behaviour; sizeof returns the size
	 * in bytes, so it is converted to bits by multiplying by 8 */
	else if (p > 8*sizeof(x) - 1) {
		printf("error: setbits(): p is larger than the register size\n");
		return -1;
	}

	/* generate the xmask */
	/* xmask == 0b00000000 */
	for (i = 0; i < n; ++i) {
		xmask = xmask | 1;
		if (i < n - 1) {
			xmask = xmask << 1;
		}
	}                             /* xmask == 0b00000111 */
	xmask = xmask << (p - n + 1); /* xmask == 0b00011100 */
	xmask = ~xmask;               /* xmask == 0b11100011 */

	xnew = x & xmask; /* xnew ==  0b10100001 */

	ymask = ~0;         /* ymask == 0b11111111 */
	ymask = ymask << n; /* ymask == 0b11111000 */
	ymask = ~ymask;     /* ymask == 0b00000111 */

	ynew = y & ymask;           /* ynew == 0b00000010 */
	ynew = ynew << (p - n + 1); /* ynew == 0b00001000 */
	
	return xnew | ynew; /* 0b10101001 */
}
