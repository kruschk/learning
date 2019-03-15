#include "e6-4.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

/* build_binary_tree: build a binary tree by using the recursive addtree algorithm */
int build_binary_tree(Treeptr *root) {
	char word[MAXWORD];

	int getword(char *word, int lim);
	Treeptr addtree(Treeptr p, char *s);

	*root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			*root = addtree(*root, word);
		}
	}
	return 0;
}

/* addtree: add a node with w, at or below p */
Treeptr addtree(Treeptr p, char *w) {
	int cond;

	char *strdup(char *s);
	Treeptr talloc(void);

	if (p == NULL) {  /* a new word has arrived */
		p = malloc(sizeof(Treenode)); /* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++; /* repeated word */
	}
	else if (cond < 0) { /* less than into left subtree */
		p->left = addtree(p->left, w);
	}
	else { /* greater than into right subtree */
		p->right = addtree(p->right, w);
	}
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(Treeptr p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
	return;
}

#define ALLOCATE_ADDITIONAL_OBJECTS 512
/* tree_to_array: add pointers from each node in the tree to array, starting from root */
Treeptr *tree_to_array(Treeptr p) {
	static size_t i = 0;    /* objects */
	static size_t size = 0; /* bytes */
	static Treeptr *array = NULL;
	void *status = NULL;
	if (sizeof(*array)*i >= size) {
		const size_t n_additional_objects = 512;
		size += sizeof(*array)*n_additional_objects;
		status = realloc(array, size);
		if (status != NULL) {
			array = status;
		}
		else {
			printf("realloc: error\n");
		}
	}
	if (p != NULL) {
		tree_to_array(p->left);
		array[i] = p;
		i++;
		tree_to_array(p->right);
	}
	array[i] = NULL;
	return array;
}

/* compare the count members of two treenodes for the qsort routine */
int tnode_count_compare(const Treeptr *tn1, const Treeptr *tn2) {
	return ((*tn1)->count > (*tn2)->count) - ((*tn1)->count < (*tn2)->count);
	/* above one-liner does the same as below */
	/*
	if ((*tn1)->count < (*tn2)->count) {
		return -1;
	}
	else if ((*tn1)->count > (*tn2)->count) {
		return 1;
	}
	else {
		return 0;
	}
	*/
}
