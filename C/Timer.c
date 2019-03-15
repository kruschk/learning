/* Good timer, measures CPU TIME ONLY, and therefore may differ from actual
	time elapsed. However, it's good in that it won't be affected by other
	active processes, therefore it will give consistent results. */

#include <time.h>

int main(void)
{
	clock_t start = clock(), diff;
	ProcessIntenseFunction();
	diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);
}