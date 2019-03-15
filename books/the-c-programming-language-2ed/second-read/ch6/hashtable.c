#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {          /* table entry: */
	struct nlist *next; /* next entry in chain */
	char *name;         /* defined name */
	char *defn;         /* replacement text */
};
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s);
struct nlist *lookup(char *);
char *strdup(char *);
struct nlist *install(char *name, char *defn);

int main(void) {
	char *namearray[3] = {"Jimmy", "Victoria", "Otto"};
	char *defnarray[3] = {"Gangster", "Banker", "Engineer"};
	int i;

	for (i = 0; i < 3; i++) {
		install(namearray[i], defnarray[i]);
	}

	for (i = 0; i < 3; i++) {
		struct nlist *table_entry_ptr = lookup(namearray[i]);
		printf("%s: %s\n", table_entry_ptr->name, table_entry_ptr->defn);
	}

	return 0;
}

/* hash: form hash values for string s */
unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np; /* found */
		}
	}
	return NULL;       /* not found */
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

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else { /* already there */
		free(np->defn); /* free previous defn */
	}
	if ((np->defn = strdup(defn)) == NULL) {
		return NULL;
	}

	return np;
}
