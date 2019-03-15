#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]) {
    void filecopy(int, int);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1) { /* no args; copy standard input */
        filecopy(STDIN, STDOUT);
    }
    else {
        while (--argc > 0) {
            int fd;
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            else {
                filecopy(fd, STDOUT);
                close(fd);
            }
        }
        if (ferror(stdout)) {
            fprintf(stderr, "%s: error writing STDOUT\n", prog);
            exit(2);
        }
        exit(0);
    }

    exit(EXIT_SUCCESS);
}

/* filecopy: copy file ifd to file ofd */
void filecopy(int ifd, int ofd) {
    char buf[BUFSIZ];
    size_t n;

    while ((n = read(ifd, buf, BUFSIZ)) > 0) {
        write(ofd, buf, n);
    }
}
