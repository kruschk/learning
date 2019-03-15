#include <stdio.h>
#include <stdlib.h>

/* global variables for the instruction and memory buffers, instruction and
 * memory pointers, and the memory size */
static char *instruction, *instruction_p;
static int *memory, *memory_p;
static unsigned int memory_size = 1;

/* possible error values */
enum error {SUCCESS = 0, IOERROR, INVALID_COMMAND, BRACKET_MISMATCH};
/* possible brainfuck commands */
enum commands {PTR_INC = '>', PTR_DEC = '<', VAL_INC = '+', VAL_DEC = '-',
	CHAR_PRINT = '.', CHAR_SAV = ',', JMPZ = '[', JMP = ']',
	PRINT_DEC_INT = ':', SAV_DEC_INT = ';'};

/* copy_file_into_buffer: copy the contents of a file into a buffer */
enum error copy_file_into_buffer(char **buf_p, const char *filepath) {
	FILE *fp;
	long filepos;
	/* validate buf_p and filepath */
	if (NULL == buf_p || NULL == filepath) {
		fprintf(stderr, "error: invalid buffer or filepath\n");
		return IOERROR;
	}
	/* open the file */
	fp = fopen(filepath, "r");
	if (fp == NULL) {
		fprintf(stderr, "error opening file\n");
		return IOERROR;
	}
	/* go to the end of the file */
	if (0 != fseek(fp, 0L, SEEK_END)) {
		fprintf(stderr, "error seeking end of file\n");
		return IOERROR;
	}
	/* save the current file position */
	filepos =  ftell(fp);
	if (-1 == filepos) {
		fprintf(stderr, "error determining file size\n");
		return IOERROR;
	}
	/* allocate sufficient memory for the destination buffer */
	*buf_p = malloc((filepos + 1)*sizeof **buf_p);
	if (NULL == *buf_p) {
		fprintf(stderr, "error allocating memory for instruction buffer\n");
		return IOERROR;
	}
	/* go back to the start of the file */
	if (0 != fseek(fp, 0L, SEEK_SET)) {
		fprintf(stderr, "error seeking start of file\n");
		return IOERROR;
	}
	/* copy everything from the file into the buffer */
	fread(*buf_p, sizeof **buf_p, filepos + 1, fp);
	if (0 != ferror(fp)) {
		fprintf(stderr, "error reading file\n");
		return IOERROR;
	}
	/* null-terminate the buffer */
	(*buf_p)[filepos] = '\0';
	/* close the file */
	if (0 != fclose(fp)) {
		fprintf(stderr, "error closing file\n");
		return IOERROR;
	}
	return SUCCESS;
}

/* brainfuck_init: initialize the brainfuck interpreter */
enum error brainfuck_init(char *filepath) {
	copy_file_into_buffer(&instruction, filepath);
	instruction_p = instruction;
	memory = calloc(memory_size, sizeof *memory);
	memory_p = memory;
	return SUCCESS;
}

/* brainfuck_clear: clean up after the brainfuck interpreter */
enum error brainfuck_clear(void) {
	free(instruction);
	free(memory);
	return SUCCESS;
}

/* execute: execute the given command */
enum error execute(enum commands command) {
	unsigned int brackets;
	unsigned int position;
	switch (command) {
		case PTR_INC: /* increment memory cell pointer */
			memory_p++;
			position = memory_p - memory;
			if (position > memory_size - 1) {
				memory_size *= 2;
				memory = realloc(memory, memory_size*sizeof *memory);
				memory_p = memory + position;
			}
			break;
		case PTR_DEC: /* decrement memory cell pointer */
			memory_p--;
			break;
		case VAL_INC: /* increment the value in current memory cell */
			(*memory_p)++;
			break;
		case VAL_DEC: /* decrement the value in current memory cell */
			(*memory_p)--;
			break;
		case CHAR_PRINT: /* print value in current cell as a character */
			putchar(*memory_p);
			break;
		case CHAR_SAV: /* save input character to current memory cell */
			*memory_p = getchar();
			break;
		/* jump to the matching right-bracket if the current cell contains
		 * zero, otherwise do nothing (main loop will increment the instruction
		 * pointer so this won't create an infinite loop) */
		case JMPZ:
			if (0 == *memory_p) {
				brackets = 1; /* current bracket counts as 1 */
				while (0 != brackets && '\0' != *instruction_p) {
					instruction_p++;
					if ('[' == *instruction_p) {
						brackets++;
					}
					else if (']' == *instruction_p) {
						brackets--;
					}
				}
				/* if we reached the end, brackets are mismatched */
				if ('\0' == *instruction_p) {
					fprintf(stderr, "error: could not find closing bracket to "
							"match opening bracket\n");
					return BRACKET_MISMATCH;
				}
			}
			break;
		case JMP: /* jump back to the matching left-bracket */
			brackets = 1;
			while (0 != brackets && instruction_p >= instruction) {
				instruction_p--;
				if ('[' == *instruction_p) {
					brackets--;
				}
				else if (']' == *instruction_p) {
					brackets++;
				}
			}
			/* if we went past the instruction base pointer and the bracket
			 * count is still non-zero, the brackets must be mismatched (if the
			 * bracket count IS zero, this means there was a matching bracket at the start) */
			if (instruction_p < instruction) {
				fprintf(stderr, "error: could not find opening bracket to "
						"match closing bracket\n");
				return BRACKET_MISMATCH;
			}
			/* need to go one before the '[' because the main execution loop
			 * will increment instruction pointer so it points to the '['
			 * again */
			instruction_p--;
			break;
		case PRINT_DEC_INT: /* print the current cell as a decimal integer */
			printf("%d ", *memory_p);
			break;
		case SAV_DEC_INT: /* save a decimal integer to the current cell */
			scanf(" %d ", memory_p);
			break;
		default: /* default for an unrecognized command */
			return INVALID_COMMAND;
			break;
	}
	return SUCCESS;
}

int main(int argc, char *argv[]) {
	char c;
	/* make sure program is called correctly */
	if (argc != 2) {
		fprintf(stderr, "usage: %s /path/to/file.brainfuck\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* initialize brainfuck */
	brainfuck_init(argv[1]);
	/* brainfuck main loop */
	while ('\0' != (c = *instruction_p)) {
		/*printf("%d %c, ", *memory_p, *instruction_p);*/
		enum error status = execute(c);
		if (BRACKET_MISMATCH == status) {
			fprintf(stderr, "unrecoverable error, exiting");
			break;
		}
		instruction_p++;
	}
	putchar('\n');
	/* clean up */
	brainfuck_clear();
	return 0;
}
