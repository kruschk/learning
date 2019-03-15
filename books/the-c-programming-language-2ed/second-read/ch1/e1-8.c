#include <stdio.h>

int main(void) {
	int c, blank, tab, nl;

	nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			++nl;
		}
		else if (c == ' ') {
			++blank;
		}
		else if (c == '\t') {
			++tab;
		}
	}

	printf("Blanks: %d\nTabs: %d\nNewlines: %d\n", blank, tab, nl);
	printf("%d\n", nl);

	return 0;
}
