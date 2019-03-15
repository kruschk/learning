#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_round.h"
#define OCTAVES 8
#define NOTES (sizeof note_names/sizeof *note_names)
#define A4 440.0
#define A4_OCTAVE 4
#define A4_NOTE 10


int main(void) {
	/* name of each note in an octave */
	const char *note_names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G",
		"G#", "A", "A#", "B"};
	unsigned int i, j, cases;
	double *results;
	double notes[OCTAVES][NOTES];
	/* compute every frequency and store it in the notes table */
	for (i = 0; i < OCTAVES; i++) {
		for (j = 0; j < NOTES; j++) {
			/* notes[A4_OCTAVE - 1][A4_NOTE - 1] is the position of A4, the
			 * numerator variable computes an offset from the A4 position */
			int numerator = NOTES*(i - A4_OCTAVE + 1) + (j - A4_NOTE + 1);
			/* A4 is the standard baseline frequency at 440 Hz */
			notes[i][j] = A4*pow(2, numerator/12.0);
		}
	}
	/* get the number of cases */
	if (1 != scanf("%u\n", &cases)) {
		fprintf(stderr, "error reading the number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memory for the results */
	results = malloc(cases*sizeof *results);
	/* get each note, then look it up in the notes table */
	for (i = 0; i < cases; i++) {
		char word[4], note[3];
		unsigned int octave_pos = -1, note_pos = -1;
		/* get the word, i.e. the note combined the octave (e.g. A2, G#5) */
		if (1 != scanf("%3s ", word)) {
			fprintf(stderr, "error reading word %u on line 2\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* if the word has a sharp specifier, i.e. G#5 */
		if (3 == strlen(word)) {
			note[0] = word[0]; /* letter */
			note[1] = word[1]; /* # */
			note[2] = '\0'; /* null-terminate note */
			octave_pos = word[2] - '0' - 1; /* octave is the 1-digit number */
		}
		/* if the word has no sharp specifier, i.e. A2 */
		else if (2 == strlen(word)) {
			note[0] = word[0]; /* letter */
			note[1] = '\0'; /* null-terminate note */
			octave_pos = word[1] - '0' - 1; /* octave is the 1-digit number */
		}
		else {
			fprintf(stderr, "error reading word %u on line 2\n", i + 1);
			continue;
		}
		/* find the position of the note in note_names so we can look it up in
		 * our table */
		for (j = 0; j < NOTES; j++) {
			if (0 == strcmp(note, note_names[j])) {
				note_pos = j;
				break;
			}
		}
		/* check that the note is valid */
		if (octave_pos < OCTAVES && note_pos < NOTES) {
			/* store the resulting frequency */
			results[i] = notes[octave_pos][note_pos];
		}
		else {
			fprintf(stderr, "note %u on line 2 is invalid\n", i + 1);
			results[i] = 0.0;
		}
	}
	/* print the results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%lu\n" : "%lu ", custom_round(results[i]));
	}
	/* clean up */
	free(results);
	return 0;
}
