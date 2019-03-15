#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 300, 280, ..., 0 */
int main(void) {
	int lower, upper, step;

	lower = 0;   /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20;   /* step size */

	printf("Fahrenheit\tCelsius\n");

	for (int fahr = upper; fahr >= lower; fahr = fahr - step) {
		float celsius = (5.0/9.0)*(fahr-32.0);
		printf("%10d\t%7.1f\n", fahr, celsius);
	}

	return 0;
}
