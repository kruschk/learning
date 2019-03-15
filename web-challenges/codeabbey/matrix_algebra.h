#ifndef MATRIX_ALGEBRA_H
#define MATRIX_ALGEBRA_H

/* computes the offset to refer to row r and column c in matrix */
#define OFFSET(matrix, r, c) ((r)*(matrix).width + (c))

enum error {SUCCESS = 0, DIMENSION_MISMATCH, REFERENCE_ERROR};

/* a vector is an array of elements with a certain length */
typedef struct {
	unsigned int length; /* length of the vector */
	double *elements; /* array of elements in the vector */
} Vector;
enum error vector_init(Vector *vector, const unsigned int length);
enum error vector_clear(Vector *vector);
/* vector_add: add vectors a and b together */
enum error vector_add(Vector *result, const Vector *a, const Vector *b);
enum error vector_negate(Vector *result, const Vector *vector);
enum error vector_subtract(Vector *result, const Vector *a, const Vector *b);
enum error scalar_multiple(Vector *result, const double scalar,
		const Vector *vector);
enum error dot(double *result, const Vector *a, const Vector *b);
enum error magnitude(double *result, const Vector *vector);
enum error vector_cosine(double *result, const Vector *a, const Vector *b);
enum error component(double *result, const Vector *a, const Vector *b);
enum error projection(Vector *result, const Vector *a, const Vector *b);

/* a matrix is a 2-D structure with height and width */
typedef struct {
	unsigned int height; /* height (m or number of rows) of matrix */
	unsigned int width; /* width (n or number of columns) of matrix */
	double *elements; /* 2-D array of elements in the matrix */
} Matrix;
enum error matrix_init(Matrix *matrix, const unsigned int height,
		const unsigned int width);
enum error matrix_clear(Matrix *matrix);
/* matrix_multiply: multiply a and b together, and return a pointer to the
 * result. a and b must not refer to the same matrix, or else this function
 * will give garbage results. */
enum error matrix_multiply(Matrix *result, const Matrix *a, const Matrix *b);
/* trace: compute the trace of a matrix, which is the sum of the diagonal
 * elements */
enum error trace(double *result, const Matrix *matrix);
#endif
