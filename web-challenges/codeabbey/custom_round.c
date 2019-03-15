#include <math.h>
long custom_round(double num) {
	double fractional_part, integral_part;
	/* fractional part will contain a double between 0 and 1. integral_part
	   is discarded, but can't set second argument to NULL because this results
	   in a SIGSEGV */
	fractional_part = modf(num, &integral_part);
	if (num >= 0) { /* for positive results */
		if (fractional_part >= 0.5) {
			return ceil(num); /* round toward +infinity */
		}
		else {
			return floor(num); /* round toward -infinity */
		}
	}
	/* for negative results */
	else {
		if (fractional_part < -0.5) {
			return floor(num); /* round toward -infinity */
		}
		else {
			return ceil(num); /* round toward +infinity */
		}
	}
}
