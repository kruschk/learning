#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* 2-D vector */
struct vector {
	double x;
	double y;
};

/* vector_add: add vectors a and b together */
struct vector vector_add(struct vector a, struct vector b) {
	struct vector result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

/* vector_negate: negate a vector */
struct vector vector_negate(struct vector vector) {
	struct vector result;
	result.x = -vector.x;
	result.y = -vector.y;
	return result;
}

/* vector_subtract: subtract vector b from a */
struct vector vector_subtract(struct vector a, struct vector b) {
	struct vector result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

/* scalar_multiple: returns the scalar multiple of scalar with vector */
struct vector scalar_multiple(double scalar, struct vector vector) {
	struct vector result;
	result.x = scalar*vector.x;
	result.y = scalar*vector.y;
	return result;
}

/* dot: returns the dot product of two vectors */
double dot(struct vector a, struct vector b) {
	return a.x*b.x + a.y*b.y;
}

/* magnitude: returns the magnitude of a vector */
double magnitude(struct vector vector) {
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

/* vector_cosine: return the cosine of the angle between vectors a and b */
double vector_cosine(struct vector a, struct vector b) {
	return dot(a, b)/(magnitude(a)*magnitude(b));
}

/* component: returns the scalar projection of b onto a */
double component(struct vector a, struct vector b) {
	return dot(a, b)/magnitude(a);
}

/* projection: returns the vector projection of b onto a */
struct vector projection(struct vector a, struct vector b) {
	return scalar_multiple(dot(a, b)/pow(magnitude(a), 2), a);
}

int main(void) {
	unsigned short int cases, i;
	double *results;
	/* get the number of cases */
	if (1 != scanf("%hu\n", &cases)) {
		fprintf(stderr, "error reading number of cases on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memore for the results array */
	results = malloc(cases*sizeof *results);
	/* determine the distance from each point to the line segment */
	for (i = 0; i < cases; i++) {
		struct vector a, b, p;
		struct vector line_segment, test_vector;
		/* get the points from input */
		if (6 != scanf("%lf %lf %lf %lf %lf %lf\n", &a.x, &a.y, &b.x, &b.y,
					&p.x, &p.y)) {
			fprintf(stderr, "error reading a coordinate on line %hu\n", i + 2);
			exit(EXIT_FAILURE);
		}
		/* the line segment is the vector from a to b */
		line_segment = vector_subtract(b, a);
		/* the test vector is the vector from a to p */
		test_vector = vector_subtract(p, a);
		/* the cosine is representative of the angle between test_vector and
		 * line_segment */
		/* The point does not "belong" to the segment; i.e., a line cannot be
		 * drawn perpendicularly from the segment to the point. Note that a
		 * cosine less than zero implies an angle in the range (90, 180] or
		 * (-90, -180], so the point is not in the desired region. */
		if (vector_cosine(line_segment, test_vector) < 0.0) {
			/* the desired result is simply the length of the test vector */
			results[i] = magnitude(test_vector);
		}
		/* Otherwise, if the cosine is greater than or equal to  0.0, then the
		 * angle is in the range [-90, 90]. If the test vector is too long,
		 * then the point is outside the range, but if it's sufficiently short,
		 * then it's in the desired range. */
		else {
			/* If the projection of the test vector onto the line segment is
			 * longer than the line segment, then the point lies outside the
			 * desired range. The desired result is the length from the point
			 * nearest to p (i.e. b) to p. */
			if (component(line_segment, test_vector)
					> magnitude(line_segment)) {
				results[i] = magnitude(vector_subtract(p, b));
			}
			/* point "belongs" to the segment; i.e., a line can be drawn
			 * perpendicularly from the segment to the point */
			else {
				/* the desired result is the perpendicular line from the line
				 * segment to the point, computed using pythagoras' formula */
				results[i] = sqrt(pow(magnitude(test_vector), 2)
						- pow(component(line_segment, test_vector), 2));
			}
		}
	}
	/* print results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%.8f\n" : "%.8f ", results[i]);
	}
	/* free memory */
	free(results);
	return 0;
}
