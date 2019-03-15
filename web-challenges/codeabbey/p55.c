#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 4096
#define WORD_LEN 3

/* define a tree_node structure, which describes a leaf of the binary tree */
struct tree_node {
	char name[4];
	unsigned int count;
	struct tree_node *left;
	struct tree_node *right;
};

/* get a word of length line from line_p into word */
char *get_word(char *word, size_t len,  char *line_p) {
	/* skip whitespace */
	while (isspace(*line_p) && *line_p != '\0') {
		line_p++;
	}
	/* if we've reached the end of the string, return NULL */
	if (*line_p == '\0') {
		return NULL;
	}
	/* copy len letters from line_p to word */
	strncpy(word, line_p, len);
	/* adjust line_p to point to the next word */
	line_p += len;
	/* if we've reached the end, return NULL */
	if (strcmp(word, "end") == 0) {
		return NULL;
	}
	/* return a pointer to the next word */
	return line_p;
}

/* add_node: recursively add word to the binary tree, or increment the count of
 * that word */
struct tree_node *add_node(struct tree_node *node, char *word) {
	int comparison;
	if (node == NULL) {
		/* if the node is empty, create a new node */
		node = malloc(sizeof *node);
		strncpy(node->name, word, WORD_LEN);
		node->count = 1;
		node->left = node->right = NULL;
	}
	else if ((comparison = strcmp(word, node->name)) > 0) {
		/* word is greater than node->name */
		node->right = add_node(node->right, word);
	}
	else if (comparison < 0) {
		/* word is less than node->name */
		node->left = add_node(node->left, word);
	}
	else {
		/* names match */
		node->count++;
	}
	return node;
}

/* print_nodes_count_greater_than: recursively print nodes with a count greater
 * than count, starting from root, in alphabetical order */
void print_nodes_count_greater_than(struct tree_node *root, size_t count) {
	/* avoid SIGSEGV */
	if (root != NULL) {
		/* go as far left as possible */
		print_nodes_count_greater_than(root->left, count);
		/* print if the node count is greater than count */
		if (root->count > count) {
			printf("%s ", root->name);
		}
		/* go right */
		print_nodes_count_greater_than(root->right, count);
	}
	return;
}
void print_nodes(struct tree_node *root) {
	/* avoid SIGSEGV */
	if (root != NULL) {
		/* go as far left as possible */
		print_nodes(root->left);
		printf("%s ", root->name);
		/* go right */
		print_nodes(root->right);
	}
	return;
}

int main(void) {
	/* declare/initialize variables */
	char line[MAX_LINE], *line_p;
	char word[WORD_LEN + 1]; /* room for '\0' */
	struct tree_node *root = NULL;
	/* get the line */
	fgets(line, MAX_LINE, stdin);
	line_p = line;
	/* go through each word and add it to a binary tree */
	while ((line_p = get_word(word, WORD_LEN, line_p)) != NULL) {
		root = add_node(root, word);
	}
	/* print the words with counts greater than 1, in alphabetical order */
	print_nodes_count_greater_than(root, 1);
	/* slap a newline on there */
	putchar('\n');
	return 0;
}
