#include <stdio.h>

#define	UPPER	300		/* lower limit of table */
#define	LOWER	0		/* upper limit */
#define	STEP	20		/* step size */

/* print Fahrenheit-Celsius table */
int main(void)
{
	int fahr;
	
	for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	return 0;
}