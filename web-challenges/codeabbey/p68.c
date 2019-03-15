#include <stdio.h>

int main(void) {
	int i, cases;
	/* get the number of test cases */
	scanf("%d\n", &cases);
	/* determine the distance that bicyclist A travels for each case */
	for (i = 0; i < cases; i++) {
		int d, v_A, v_B;
		double d_A;
		/* get the total distance and each cyclist's speed */
		scanf("%d %d %d\n", &d, &v_A, &v_B);
		/* compute distance travelled by cyclist A. To derive this formula, use
		 * d_i = v_i*t_i, d = d_1 + d_2, and note that t_1 == t_2 */
		d_A = (double)d*v_A/v_B/(1.0 + (double)v_A/v_B);
		/* print result */
		printf((i == cases - 1) ? "%f\n" : "%f ", d_A);
	}
	return 0;
}
