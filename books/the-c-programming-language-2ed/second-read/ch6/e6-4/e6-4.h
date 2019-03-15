#ifndef E6_4_H
#define E6_4_H

/* data structures */

/* define Treeptr, which is simply a pointer to a Treenode */
typedef struct tnode *Treeptr;

/* declare a struct for a tree node, Treenode, which describes the leaves of a
 * binary tree */
typedef struct tnode {
	char *word;
	int count;
	Treeptr left;
	Treeptr right;
} Treenode;

#endif
