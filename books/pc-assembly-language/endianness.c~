#include <stdio.h>

unsigned int invert_endian(unsigned x) {
	unsigned invert;
	const unsigned char *xp = (const unsigned char *) &x;
	unsigned char *ip = (unsigned char *) &invert;

	ip[0] = xp[3];	/* reverse the individual bytes */
	ip[1] = xp[2];
	ip[2] = xp[1];
	ip[3] = xp[0];

	return invert;	/* return the bytes reversed */
}

int main(void) {
	unsigned short word = 0x1234; /* assumes sizeof (short) == 2 */
	unsigned char *p = (unsigned char *) &word;

	printf("sizeof(short): %lu\n", sizeof(short));

	if (p[0] == 0x12) {
		printf ("Big Endian Machine\n");
	}
	else {
		printf ("Little Endian Machine\n");
	}

	unsigned int number = 0x12345678;
	printf("normal: %x\n", number);
	printf("inverted: %x\n", invert_endian(number));

	return 0;
}
