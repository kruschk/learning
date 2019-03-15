#include <stdio.h>
#include <stdlib.h>

/* a vector object */
struct vector {
	unsigned int length;
	double *array;
};

/* initialize a vector object */
void vector_init(struct vector *v, unsigned int length) {
	v->length = length;
	v->array = malloc(v->length*sizeof *v->array);
	return;
}

/* clean up a vector object */
void vector_clear(struct vector *v) {
	v->length = 0;
	free(v->array);
	v->array = NULL;
	return;
}

/* returns the average value of the vector v */
double average(struct vector *v) {
	double sum;
	unsigned int i;
	for (i = 0, sum = 0.0; i < v->length; i++) {
		sum += v->array[i];
	}
	return sum/v->length;
}

/* returns the variance of the vector v */
double variance(struct vector *v) {
	double v_avg = average(v);
	double sum;
	unsigned int i;
	for (i = 0, sum = 0.0; i < v->length; i++) {
		sum += (v->array[i] - v_avg)*(v->array[i] - v_avg);
	}
	return sum;
}


/* returns the covariance of two vectors */
double covariance(struct vector *x, struct vector *y) {
	unsigned int length;
	double x_avg = average(x);
	double y_avg = average(y);
	unsigned int i;
	double sum;
	/* let the length used be the lesser of the two vectors' lengths */
	if (x->length <= y->length) {
		length = x->length;
	}
	else if (x->length > y->length) {
		length = y->length;
	}
	/* compute the covariance and return it */
	for (i = 0, sum = 0.0; i < length; i++) {
		sum += (x->array[i] - x_avg)*(y->array[i] - y_avg);
	}
	return sum;
}

/* Result must be a vector of length 2, and x and y are regular vectors. After
 * calling this function, result will contain the parameters alpha (intercept)
 * and beta (slope) of the linear regression in result->array[0] and 
 * esult->array[1], respectively. */
void linear_regression(struct vector *result, struct vector *x,
		struct vector *y) {
	if (result->length != 2) {
		fprintf(stderr, "linear_regression: result must be an array of length "
				"2, returning\n");
		return;
	}
	result->array[1] = covariance(x, y)/variance(x); /* beta */
	result->array[0] = average(y) - result->array[1]*average(x); /* alpha */
	return;
}
	
int main(void) {
	int start_year, end_year;
	unsigned int n_years, i;
	struct vector x, y, result;
	/* get the start and end year */
	if (2 != scanf("%d %d\n", &start_year, &end_year)) {
		fprintf(stderr,
				"error reading start year and/or end year on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* the end year must be larger than or equal to the start year; if not,
	 * swap the two */
	if (end_year < start_year) {
		int temp = start_year;
		start_year = end_year;
		end_year = temp;
	}
	n_years = end_year - start_year + 1;
	/* initialize vectors x and y */
	vector_init(&x, n_years);
	vector_init(&y, n_years);
	/* populate the vectors */
	for (i = 0; i < n_years; i++) {
		int year;
		if (3 != scanf("%d: %lf %lf\n", &year, &x.array[i], &y.array[i])) {
			fprintf(stderr, "error reading line %u\n", i + 2);
			exit(EXIT_FAILURE);
		}
	}
	/* initialize a vector to hold the regression parameters, perform the
	 * regression, and print the results */
	vector_init(&result, 2u);
	linear_regression(&result, &x, &y);
	printf("%.8f %.8f\n", result.array[1], result.array[0]);
	/* clean up */
	vector_clear(&x);
	vector_clear(&y);
	vector_clear(&result);
	return 0;
}
