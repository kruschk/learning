/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
	use a function for conversion. */

#include <stdio.h>

#define	LOWER	-100	/* lower temp limit */
#define	UPPER	300		/* upper temp limit */
#define	STEP	20		/* step size */

double fahrToCels(double temp);

int main(void)
{
	double fahr, celsius;

	fahr = LOWER;
	printf("\nFahrenheit to Celsius Conversion Table\n\n");
	printf("Fahr.\tCelsius\n");
	
	while (fahr <= UPPER)
	{
		celsius = fahrToCels(fahr);
		printf("%4.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + STEP;
	}
	
	return 0;
}

double fahrToCels(double fahr)
{
	return (5.0 / 9.0) * (fahr - 32.0);
}