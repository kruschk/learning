#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix_algebra.h"

enum error vector_init(Vector *vector, const unsigned int length) {
	vector->length = length;
	vector->elements = malloc(vector->length*sizeof *vector->elements);
	return SUCCESS;
}

enum error vector_clear(Vector *vector) {
	vector->length = 0;
	free(vector->elements);
	vector->elements = NULL;
	return SUCCESS;
}

/* vector_add: add vectors a and b together */
enum error vector_add(Vector *result, const Vector *a, const Vector *b) {
	if (result->length != a->length || a->length != b-> length) {
		fprintf(stderr, "vector_add: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		unsigned int i;
		/*result->length = a->length;
		  result->elements = malloc(result->length*sizeof *result->elements);*/
		for (i = 0; i < result->length; i++) {
			result->elements[i] = a->elements[i] + b->elements[i];
		}
		return SUCCESS;
	}
}

/* vector_negate: negate a vector */
enum error vector_negate(Vector *result, const Vector *vector) {
	unsigned int i;
	if (result->length != vector->length) {
		fprintf(stderr, "vector_negate: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		/*result->length = vector->length;
		  result->elements = malloc(result->length*sizeof *result->elements);*/
		for (i = 0; i < result->length; i++) {
			result->elements[i] = -(vector->elements[i]);
		}
		return SUCCESS;
	}
}

/* vector_subtract: subtract vector b from a */
enum error vector_subtract(Vector *result, const Vector *a, const Vector *b) {
	if (result->length != a->length || a->length != b-> length) {
		fprintf(stderr, "vector_subtract: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		unsigned int i;
		/*result->length = a->length;
		  result->elements = malloc(result->length*sizeof *result->elements);*/
		for (i = 0; i < result->length; i++) {
			result->elements[i] = a->elements[i] - b->elements[i];
		}
		return SUCCESS;
	}
}

/* scalar_multiple: returns the scalar multiple of scalar with vector */
enum error scalar_multiple(Vector *result, const double scalar,
		const Vector *vector) {
	if (result->length != vector->length) {
		fprintf(stderr, "scalar_multiple: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		unsigned int i;
		/*result->length = vector->length;
		  result->elements = malloc(result->length*sizeof *result->elements);*/
		for (i = 0; i < result->length; i++) {
			result->elements[i] = scalar*vector->elements[i];
		}
		return SUCCESS;
	}
}

/* dot: returns the dot product of two vectors */
enum error dot(double *result, const Vector *a, const Vector *b) {
	if (a->length != b-> length) {
		fprintf(stderr, "dot: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		unsigned int i;
		/*result->length = a->length;
		result->elements = malloc(result->length*sizeof *result->elements);*/
		*result = 0.0;
		for (i = 0; i < a->length; i++) {
			*result += a->elements[i]*b->elements[i];
		}
		return SUCCESS;
	}
}

/* magnitude: returns the magnitude of a vector */
enum error magnitude(double *result, const Vector *vector) {
	unsigned int i;
	for (*result = 0.0, i = 0; i < vector->length; i++) {
		*result += pow(vector->elements[i], 2);
	}
	*result = sqrt(*result);
	return SUCCESS;
}

/* vector_cosine: return the cosine of the angle between vectors a and b */
enum error vector_cosine(double *result, const Vector *a, const Vector *b) {
	if (a->length != b-> length) {
		fprintf(stderr, "vector_cosine: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		double dot_product, mag_a, mag_b;
		dot(&dot_product, a, b);
		magnitude(&mag_a, a);
		magnitude(&mag_b, b);
		*result = dot_product/(mag_a*mag_b);
		return SUCCESS;
	}
}

/* component: returns the scalar projection of b onto a */
enum error component(double *result, const Vector *a, const Vector *b) {
	if (a->length != b-> length) {
		fprintf(stderr, "component: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		double dot_product, mag;
		dot(&dot_product, a, b);
		magnitude(&mag, a);
		*result = dot_product/mag;
		return SUCCESS;
	}
}

/* projection: returns the vector projection of b onto a */
enum error projection(Vector *result, const Vector *a, const Vector *b) {
	if (a->length != b-> length) {
		fprintf(stderr, "component: vector dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		double dot_product, mag, scalar;
		dot(&dot_product, a, b);
		magnitude(&mag, a);
		scalar = dot_product/pow(mag, 2);
		scalar_multiple(result, scalar, result);
		return SUCCESS;
	}
}

enum error matrix_init(Matrix *matrix, const unsigned int height,
		const unsigned int width) {
	matrix->height = height;
	matrix->width = width;
	matrix->elements =
		malloc(matrix->height*matrix->width*sizeof *matrix->elements);
	return SUCCESS;
}

enum error matrix_clear(Matrix *matrix) {
	matrix->height = 0;
	matrix->width = 0;
	free(matrix->elements);
	matrix->elements = NULL;
	return SUCCESS;
}

/* matrix_multiply: multiply a and b together, and return the result */
enum error matrix_multiply(Matrix *result, const Matrix *a, const Matrix *b) {
	/* make sure a and b aren't pointing to the same matrix */
	if (result == a || a == b) {
		fprintf(stderr, "matrix_multiply: matrix arguments may not refer to "
			   	"the same objects\n");
		return REFERENCE_ERROR;
	}
	/* make sure the matrix inner dimensions agree */
	else if (a->width != b->height) {
		fprintf(stderr, "matrix_multiply: matrix dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else if (result->height != a->height || result->width != b->width) {
		fprintf(stderr, "matrix_multiply: matrix dimensions do not agree\n");
		return DIMENSION_MISMATCH;
	}
	else {
		unsigned short int i;
		/* result has the outer dimensions of a and b */
		/*result->height = a->height;
		result->width = b->width;*/
		/* allocate memory for the resulting matrix */
		/*result->elements =
			malloc(result->height*result->width*sizeof *result->elements);*/
		for (i = 0; i < result->height; i++) {
			unsigned short int j;
			for (j = 0; j < result->width; j++) {
				unsigned short int k;
				double sum;
				/* element result_ij is produced by taking the dot product of
				 * the ith row of a and the jth column of b */
				for (k = 0, sum = 0.0; k < a->width; k++) {
					sum += a->elements[OFFSET(*a, i, k)]
						*b->elements[OFFSET(*b, k, j)];
				}
				result->elements[OFFSET(*result, i, j)] = sum;
			}
		}
		return SUCCESS;
	}
}

/* trace: compute the trace of a matrix, which is the sum of the diagonal
 * elements */
enum error trace(double *result, const Matrix *matrix) {
	if (matrix->height != matrix->width) {
		fprintf(stderr, "trace: matrix must be square");
		return DIMENSION_MISMATCH;
	} else {
		unsigned short int i;
		for (i = 0, *result = 0.0; i < matrix->height; i++) {
			*result += matrix->elements[OFFSET(*matrix, i, i)];
		}
		return SUCCESS;
	}
}
