#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define MAX_NODES 1024

/* declare a binary tree node structure */
struct node {
	unsigned short int value;
	/* children */
	struct node *left;
	struct node *right;
};

/* find_max: find the path through the tree which contains the greatest sum of
 * values, and return that maximum sum. The path itself is not returned in any
 * form. */
unsigned short int find_max(struct node *root, unsigned short int max,
		unsigned short int sum) {
	/* if root is a proper node, add its value to sum and descend further down
	 * the tree. After returning from those child nodes, we subtract this node
	 * value from sum. */
	if (root != NULL) {
		sum += root->value;
		max = find_max(root->left, max, sum);
		max = find_max(root->right, max, sum);
		sum -= root->value;
	}
	/* if root is a NULL pointer and the current sum is greater than max,
	 * assign sum to max */
	else {
		if (sum > max) {
			max = sum;
		}
	}
	/* return the max as it appears in this stack frame */
	return max;
}

int main(void) {
	/* declare iteration variables */
	unsigned short int n_cases, i;
	/* get the number of cases */
	scanf("%hu\n", &n_cases);
	/* generate a binary tree for each case, then descend into it using
	 * find_max to determine the maximum sum */
	for (i = 0; i < n_cases; i++) {
		/* declare variables */
		char line[MAX_LINE], *line_p;
		unsigned short int j = 0, n_nodes, max;
		struct node arr[MAX_NODES];
		/* get the next line */
		fgets(line, MAX_LINE, stdin);
		line_p = line;
		/* populate the value members of each struct in the array */
		for (j = 0; *line_p != '\n' && *line_p != '\0'; j++) {
			arr[j].value = strtoul(line_p, &line_p, 10);
		}
		/* save the array length */
		n_nodes = j;
		/* iterate through the array and set the left and right children to the
		 * appropriate values */
		for (j = 0; j < n_nodes; j++) {
			if (j + 2 < n_nodes) {
				arr[j].left = &arr[j+2];
			}
			else {
				arr[j].left = NULL;
			}
			if (j + 3 < n_nodes) {
				arr[j].right = &arr[j+3];
			}
			else {
				arr[j].right = NULL;
			}
		}
		/* find the maximum sum from the tree */
		max = find_max(&arr[0], 0, 0);
		/* print the result */
		printf((i == n_cases - 1) ? "%hu\n" : "%hu ", max);
	}
	return 0;
}
