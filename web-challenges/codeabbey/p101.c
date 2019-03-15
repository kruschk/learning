#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "custom_round.h"
#define PI acos(-1)

/* a 2-D vector */
struct vec2 {
	double x;
	double y;
};

/* structure to make constants easier to pass around */
struct constants {
	double a;
	double b;
	double c;
};

/* function defined in problem statement */
double function(const double x, const double y, const struct constants *c) {
	const double A = c->a;
	const double B = c->b;
	const double C = c->c;
	return pow(x - A, 2) + pow(y - B, 2)
		+ C*exp(-pow(x + A, 2) - pow(y + B, 2));
}

/* computes the gradient of a function */
struct vec2 gradient(double (*f)(const double, const double,
			const struct constants *), const double x, const double y,
		const struct constants *c, const double dt) {
	struct vec2 result;
	result.x = (f(x + dt, y, c) - f(x, y, c))/dt;
	result.y = (f(x, y + dt, c) - f(x, y, c))/dt;
	return result;
}

int main(void) {
	unsigned short int cases, i;
	double *results;
	struct vec2 grad;
	struct constants c;
	/* get initial parameters */
	if (4 != scanf("%hu %lf %lf %lf\n", &cases, &c.a, &c.b, &c.c)) {
		fprintf(stderr, "Error reading line 1.\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memory for results */
	results = malloc(cases*sizeof grad);
	/* compute the angle of descent from each point */
	for (i = 0; i < cases; i++) {
		const double dt = 1.0e-9;
		double x, y, angle;
		/* get point */
		if (2 != scanf("%lf %lf\n", &x, &y)) {
			fprintf(stderr, "Error reading line %hu.\n", i + 2);
			exit(EXIT_FAILURE);
		}
		/* compute gradient, then angle, then store the angle in results */
		grad = gradient(function, x, y, &c, dt);
		angle = atan2(grad.y, grad.x)*180.0/PI + 180.0;
		results[i] = angle;
	}
	/* print results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%ld\n" : "%ld ", custom_round(results[i]));
	}
	/* clean up */
	free(results);
	return 0;
}
