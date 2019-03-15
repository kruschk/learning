#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_round.h"
#define OCTAVES 8
#define NOTES (sizeof note_names/sizeof *note_names)
#define A4_FREQ 440.0
#define A4_OCTAVE 4
#define A4_NOTE 10
#define A4_POS ((A4_OCTAVE-1)*NOTES + (A4_NOTE-1))
#define TOTAL_NOTES (OCTAVES*NOTES)


int main(void) {
	/* name of each note in an octave */
	const char *note_names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G",
		"G#", "A", "A#", "B"};
	unsigned int i, cases;
	char (*results)[4]; /* results is a pointer to an array of 4 char */
	/* get the number of cases */
	if (1 != scanf("%u\n", &cases)) {
		fprintf(stderr, "error reading the number of cases\n");
		exit(EXIT_FAILURE);
	}
	/* allocate memory for the results */
	results = malloc(cases*sizeof *results);
	/* get each note, then look it up in the notes table */
	for (i = 0; i < cases; i++) {
		unsigned int octave_pos = -1, note_pos = -1;
		int frequency_pos;;
		double frequency;
		/* get the word, i.e. the note combined the octave (e.g. A2, G#5) */
		if (1 != scanf("%lf ", &frequency)) {
			fprintf(stderr, "error reading word %u on line 2\n", i + 1);
			exit(EXIT_FAILURE);
		}
		/* convert the given frequency to a position in the frequency table */
		frequency_pos = custom_round(NOTES*log2(frequency/A4_FREQ) + A4_POS);
		/* make sure the frequency position is valid */
		if (0 <= frequency_pos && frequency_pos < (int)TOTAL_NOTES) {
			/* since frequency_pos = octave_pos*NOTES + note_pos, can extract
			 * octave_pos and note_pos as follows: */
			octave_pos = frequency_pos/NOTES;
			note_pos = frequency_pos%NOTES;
			/* build the full name of the note, including octave and optional
			 * sharp specifier */
			strncat(results[i], note_names[note_pos], 2);
			if ('#' == results[i][1]) {
				/* convert the octave to a char and 1-index it */
				results[i][2] = octave_pos + '0' + 1;
				results[i][3] = '\0';
			}
			else {
				results[i][1] = octave_pos + '0' + 1;
				results[i][2] = '\0';
			}
		}
		else {
			fprintf(stderr, "frequency %f on line 2 is invalid\n", frequency);
			results[i][0] = '\0';
		}
	}
	/* print the results */
	for (i = 0; i < cases; i++) {
		printf((i == cases - 1) ? "%s\n" : "%s ", results[i]);
	}
	/* clean up */
	free(results);
	return 0;
}
