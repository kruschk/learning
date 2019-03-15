#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024

int find(char *, FILE *, char *);

int main(int argc, char *argv[]) {
	int i;

	if (argc < 3) {
		printf("usage: %s pattern file1 [file2 [...]]\n", argv[0]);
	}

	for (i = 2; i < argc; i++) {
		FILE *fp;
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "error opening file %s, skipping to next file\n", argv[i]);
			continue;
		}
		find(argv[i], fp, argv[1]);
	}

	exit(EXIT_SUCCESS);
}

#define MAXLINE 1024
/* find: print lines that match pattern from 1st arg */
int find(char *filename, FILE *fp, char *pattern) {
	int line = 1;

	while (1) {
		char *status;
		char str[MAXLINE];
		status = fgets(str, MAXLINE, fp);
		if (strstr(str, pattern) != NULL) {
			printf("match found in file %s, line %d:\n%s", filename, line, str);
		}
		if (status == NULL) {
			return 0;
		}
		line++;
	}
}
