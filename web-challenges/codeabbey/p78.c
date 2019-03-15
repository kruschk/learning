#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_round.h"

/* a vector, or a point in 2-D space */
struct vector {
	double x;
	double y;
};

/* a line from a start point to an end point */
struct line {
	struct vector start;
	struct vector end;
};

/* vector_add: add vectors a and b */
struct vector vector_add(struct vector a, struct vector b) {
	struct vector result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

/* vector_subtract: subtract vector b from vector a */
struct vector vector_subtract(struct vector a, struct vector b) {
	struct vector result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

/* scalar_multiple: multiply a vector by a scalar value */
struct vector scalar_multiple(double scalar, struct vector vector) {
	struct vector result;
	result.x = scalar*vector.x;
	result.y = scalar*vector.y;
	return result;
}

/* generate_new_points: generates a new set of points using the array of lines
 * by converting each line into a vector from the origin (by subtracting its
 * end point from its start point), taking the scalar multiple of this new
 * vector with alpha, then adding the original starting point of the line back
 * to this vector so that the new point is on the correct point on the original
 * line (note: vector == point). */
void generate_new_points(double alpha, struct vector *points,
		struct line *lines, unsigned short int n_points) {
	unsigned short int i;
	for (i = 0; i < n_points; i++) {
		struct vector new_point = vector_subtract(lines[i].end,
				lines[i].start);
		new_point = scalar_multiple(alpha, new_point);
		new_point = vector_add(new_point, lines[i].start);
		points[i] = new_point;
	}
	return;
}

/* update_lines: use the set of n_points in the array points to produce
 * n_points-1 lines. The lines connect all of the points sequentially. */
void update_lines(struct vector *points, struct line *lines,
		unsigned short int n_points) {
	unsigned short int i;
	for (i = 0; i < n_points - 1; i++) {
		lines[i].start = points[i];
		lines[i].end = points[i+1];
	}
	return;
}

int main(void) {
	unsigned short int n_alpha, initial_n_points, n_points, i;
	double *alphas, step;
	struct vector *initial_points, *points, *bezier_points;
	struct line *initial_lines, *lines;
	/* get the number of points and the number of alphas from input */
	if (2 != scanf("%hu %hu\n", &initial_n_points, &n_alpha)) {
		fprintf(stderr, "error reading line 1 (number of initial points and "
				"number of alpha values)\n");
		exit(EXIT_FAILURE);
	}
	/* create an array containing all of the desired values of alpha */
	alphas = malloc((n_alpha+1)*sizeof *alphas);
	step = (1.0-0.0)/(n_alpha-1.0);
	alphas[0] = 0.0;
	for (i = 1; i < n_alpha; i++) {
		alphas[i] = alphas[i-1] + step;
	}
	/* create an array containing all of the initial points */
	initial_points = malloc(initial_n_points*sizeof *points);
	for (i = 0; i < initial_n_points; i++) {
		if (2 != scanf("%lf %lf\n", &initial_points[i].x,
					&initial_points[i].y)) {
			fprintf(stderr, "error reading point %hu on line %hu", i + 1,
					i + 2);
			exit(EXIT_FAILURE);
		}
	}
	/* create an array containing all of the initial lines */
	initial_lines = malloc((initial_n_points - 1)*sizeof *lines);
	update_lines(initial_points, initial_lines, initial_n_points);
	/* points and lines arrays are used for intermediate calculations, and
	 * bezier_points stores the results */
	points = malloc(initial_n_points*sizeof *points);
	lines = malloc((initial_n_points - 1)*sizeof *lines);
	bezier_points = malloc(n_alpha*sizeof *bezier_points);
	/* compute the bezier point for each value of alpha */
	for (i = 0; i < n_alpha; i++) {
		/* make sure the points and lines arrays contain the initial points and
		 * lines values, and the number of points is reflective of this  */
		memcpy(points, initial_points,
				initial_n_points*sizeof *initial_points);
		memcpy(lines, initial_lines,
				(initial_n_points - 1)*sizeof *initial_lines);
		n_points = initial_n_points;
		while (n_points > 0) {
			n_points--;
			/* generate a new set of points from the current set of lines */
			generate_new_points(alphas[i], points, lines, n_points);
			/* update the lines to reflect the current set of points */
			update_lines(points, lines, n_points);
		}
		/* save the bezier point, which will always be in points[0] after the
		 * while loop has finished */
		bezier_points[i] = points[0];
	}
	/* print the results */
	for (i = 0; i < n_alpha; i++) {
		printf((i == n_alpha - 1) ? "%ld %ld\n" : "%ld %ld ",
				custom_round(bezier_points[i].x),
				custom_round(bezier_points[i].y));
	}
	/* free memory */
	free(alphas);
	free(initial_points);
	free(initial_lines);
	free(points);
	free(lines);
	free(bezier_points);
	return 0;
}
