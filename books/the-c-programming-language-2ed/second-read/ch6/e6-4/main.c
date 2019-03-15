/* tree_to_array() uses dynamic memory allocation. getword and getch/ungetch
 * should do the same. */
#include "e6-4.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* word frequency count */
int main(void) {
	/* variable declarations */
	Treeptr root;
	Treeptr *treeptr_array = NULL;
	size_t count;
	size_t i;

	/* tnode_func.c function declarations */
	int build_binary_tree(Treeptr *);
	void treeprint(Treeptr);
	Treeptr *tree_to_array(Treeptr);
	int tnode_count_compare(const Treeptr *, const Treeptr *);
	void reverse(Treeptr *, size_t);

	/* build the binary tree */
	build_binary_tree(&root);

	/* print the tree (it will be in alphabetical order by word member of each
	 * treenode) */
	/*treeprint(root);*/

	/* add each node to an array, beginning at root */
	treeptr_array = tree_to_array(root);

	/* count the number of pointers in the array */
	count = 0;
	while (treeptr_array[count] != NULL) {
		count++;
	}

	/* sort the array based on the count member of each tnode */
	qsort(treeptr_array, count, sizeof(*treeptr_array),
	      (int (*)(const void *, const void *))tnode_count_compare);

	/* reverse the order */
	reverse(treeptr_array, count);

	/* print the array */
	for (i = 0; treeptr_array[i] != NULL; i++) {
		printf("%4lu: %4d %s\n", i, treeptr_array[i]->count, treeptr_array[i]->word);
	}

	/* free allocated memory */
	free(treeptr_array);

	return 0;
}
