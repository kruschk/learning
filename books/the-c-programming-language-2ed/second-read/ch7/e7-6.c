#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	size_t line;
	FILE *f1, *f2;

	size_t filecmp(FILE *f1, FILE *f2);
	
	/* check the arguments */
	if (argc != 3) {
		fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
		exit(1);
	}

	/* open the two files */
	f1 = fopen(argv[1], "r");
	if (f1 == NULL) {
		printf("failed to open %s\n", argv[1]);
		exit(2);
	}
	f2 = fopen(argv[2], "r");
	if (f2 == NULL) {
		printf("failed to open %s\n", argv[2]);
		exit(2);
	}

	/* compare the files */
	line = filecmp(f1, f2);

	/* tell user if the files are different */
	if (line == 0) {
		printf("the file contents are identical\n");
	}
	else {
		printf("difference detected on line %lu\n", line);
	}

	/* close the files */
	if (fclose(f1) == EOF || fclose(f2) == EOF) {
		fprintf(stderr, "failed to close a file\n");
		exit(3);
	}

	exit(EXIT_SUCCESS);
}

#define MAXLINE 1024

/* filecmp: compare two files line-by line, and return the line upon which they
 * are different. Return 0 if they are the same. */
size_t filecmp(FILE *f1, FILE *f2) {
	size_t line = 1;
	char s1[MAXLINE];
	char *test1;
	char *test2;
	char s2[MAXLINE];

	while (1) {
		test1 = fgets(s1, MAXLINE, f1);
		test2 = fgets(s2, MAXLINE, f2);
		/* normal case, compare the two lines */
		if (test1 != NULL && test2 != NULL) {
			if (strcmp(s1, s2) == 0) {
				line++;
			}
			else {
				return line;
			}
		}
		/* if both are NULL (meaning EOF or error, ignoring errors), then the
		 * files might still be identical */
		else if (test1 == NULL && test2 == NULL) {
			if (strcmp(s1, s2) == 0) {
				return 0;
			}
			else {
				return line;
			}
		}
		/* if only test1 or test2 is NULL, then the files must be different */
		else {
			return line;
		}
	}

	/* alternate method, less elegant and likely more buggy
	while (((test1 = fgets(s1, MAXLINE, f1)) != NULL) &&
		   ((test2 = fgets(s2, MAXLINE, f2)) != NULL)) {
		if (strcmp(s1, s2) == 0) {
			line++;
		}
		else {
			return line;
		}
	}
	*/
	/* test1 != NULL but test2 == NULL, so they must be different */
	/*
	if (test2 == NULL) {
		return line;
	}
	else if (test1 == NULL) {
	*/
		/* necessary test since the while-loop above will short-circuit when it
		 * tested test1 != NULL as false */
		/*
		if (((test2 = fgets(s2, MAXLINE, f2)) == NULL) && strcmp(s1, s2) == 0) {
			return 0;
		}
		else {
			return line;
		}
	}
	else {
		exit(EXIT_FAILURE);
	}
	*/
}
