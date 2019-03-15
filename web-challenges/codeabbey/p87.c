#include <stdio.h>
#include <stdlib.h>

/* tree node structure */
struct node {
	int value;
	unsigned int count;
	struct node *left;
	struct node *right;
};

/* add_node: adds a node to the tree in the appropriate location */
struct node *add_node(struct node *root, int value) {
	/* if the root node already exits */
	if (NULL != root) {
		if (value < root->value) {
			root->left = add_node(root->left, value);
		}
		else if (value > root->value) {
			root->right = add_node(root->right, value);
		}
		else {
			root->count++;
		}
	}
	/* create the node if it doesn't exist */
	else {
		root = malloc(sizeof *root);
		root->value = value;
		root->count = 1;
		root->left = root->right = NULL;
	}
	return root;
}

/* print_node: print members of a node */
void print_node(struct node *node) {
	if (NULL == node->left) {
		printf("(-,");
	}
	printf("%d,", node->value);
	if (NULL == node->right) {
		printf("-)");
	}
	return;
}

/* clear_node: clear memory allocated to a node */
void clear_node(struct node *node) {
	node->value = 0;
	node->count = 0;
	free(node);
	node = NULL;
	return;
}

/* descend_tree: recursively descend into the binary tree, calling
 * left_callback function after returning to a parent node from the left, and
 * call the right_callback function after returning from a right node.
 * left_callback is useful for doing things in ascending order, e.g. printing
 * members of each node in order of value. right_callback is useful for
 * operating on a node without needing to worry about it being used again (so
 * segfaults or double free()s won't occur). For example, freeing the tree can
 * be done this way. The function can be called with a NULL value for either
 * callback function (or both, although that wouldn't be useful). */
void descend_tree(struct node *root, void (*left_callback)(struct node *),
		void (*right_callback)(struct node *)) {
	if (root != NULL) {
		descend_tree(root->left, left_callback, right_callback);
		if (NULL != left_callback) {
			left_callback(root);
		}
		descend_tree(root->right, left_callback, right_callback);
		if (NULL != right_callback) {
			right_callback(root);
		}
	}
	return;
}

/* print_tree_funny: print the tree in the requested (funny) format */
void print_tree_funny(struct node *node) {
	if (NULL != node) {
		putchar('(');
		print_tree_funny(node->left);
		printf(",%d,", node->value);
		print_tree_funny(node->right);
		putchar(')');
	}
	else {
		putchar('-');
	}
	return;
}

int main(void) {
	unsigned int num_nodes = 0, i = 0;
	struct node *root = NULL;
	/* get the number of nodes */
	if (1 != scanf("%u\n", &num_nodes)) {
		fprintf(stderr, "error reading the number of nodes on line 1\n");
		exit(EXIT_FAILURE);
	}
	/* generate the tree */
	for (i = 0, root = NULL; i < num_nodes; i++) {
		int value;
		/* get the value */
		if (1 != scanf("%d ", &value)) {
			fprintf(stderr, "error reading value %u on line 2\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* add it to the tree */
		root = add_node(root, value);
	}
	/* recursively descend into the tree, calling the print_node function after
	 * returning to a parent node from the left (this has the effect of
	 * printing the nodes in ascending order of node.value) */
	/*descend_tree(root, print_node, NULL);*/
	/* print the tree in the desired format */
	print_tree_funny(root);
	putchar('\n');
	/* recursively descend into the tree, calling the clear_node function after
	 * returning to a parent node from the right (this avoids segfaults and
	 * double frees, as nothing will attempt to use the parent node again) */
	descend_tree(root, NULL, clear_node);
	return 0;
}
