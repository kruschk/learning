#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float fahr2cels(int fahr);

int main(void) {
	int fahr;

	for (fahr = LOWER; fahr <= UPPER; fahr += STEP) {
		printf("%3d\t%6.1f\n", fahr, fahr2cels(fahr));
	}
}

float fahr2cels(int fahr) {
	return (5.0/9.0)*(fahr-32.0);
}
