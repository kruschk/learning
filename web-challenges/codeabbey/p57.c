#include <stdio.h>
#include <stdlib.h>

int main(void) {
	/* declare variables */
	double *in, *out;
	size_t n_values, i;
	/* get the number of values */
	scanf("%lu\n", &n_values);
	/* allocate memory */
	in = malloc(n_values*sizeof *in);
	out = malloc(n_values*sizeof *out);
	/* copy the values to the in array */
	for (i = 0; i < n_values; i++) {
		scanf("%lf", &in[i]);
	}
	/* calculate the values for the out array */
	out[0] = in[0];
	for (i = 1; i < n_values - 1; i++) {
		out[i] = (in[i-1] + in[i] + in[i+1])/3.0;
	}
	out[i] = in[i];
	/* print the out array */
	for (i = 0; i < n_values; i++) {
		printf((i == n_values - 1) ? "%.8f\n" : "%.8f ", out[i]);
	}
	/* free memory */
	free(in);
	free(out);
	return 0;
}
