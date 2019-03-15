#include <stdio.h>

int main(void)
{
	float celsius, fahr;
	short int lower, upper, step;
	
	lower = -100;
	upper = 100;
	step = 10;
	
	celsius = (float)lower;
	printf("\nFahrenheit to Celsius Conversion Table\n\n");
	printf("Celsius | Fahrenheit\n");
	printf("--------|-----------\n");
	
	while (celsius <= upper)
	{
		fahr = ((float)9.0 / (float)5.0) * celsius + (float)32.0;
		printf("%7.0f | %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return 0;
}