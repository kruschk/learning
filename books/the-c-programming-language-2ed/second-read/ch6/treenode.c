#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main(void) {
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word);
		}
	}
	treeprint(root);

	return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

	if (p == NULL) {  /* a new word has arrived */
		p = talloc(); /* make a new node */
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
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
	return;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
	return (struct tnode *)malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *strdup(char *s) {
	char *p;

	p = (char *)malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

/* get next word or character from input */
int getword(char *word, int lim) {
	int c;
	int getch(void);
	void ungetch(int c);
	char *w = word;

	while (isspace(c = getch())) {
		;
	}
	if (c != EOF) {
		*w++ = c;
	}
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
