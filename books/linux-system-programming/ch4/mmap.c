/*
 * Use mmap() to map a file to memory, then print the file to stdout.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
  struct stat sb;
  off_t len;
  char *p;
  int fd;

  /* check arguments */
  if (argc < 2) {
    fprintf(stderr, "usage: %s <file> \n", argv[0]);
    return 1;
  }

  /* open file */
  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  /* make sure we're looking at a regular file */
  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    return 1;
  }
  if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "%s is not a file\n", argv[1]);
    return 1;
  }

  /* map the opened file to memory */
  p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  /* close the file */
  if (close(fd) == -1) {
    perror("close");
    return 1;
  }

  /* print to stdout, byte-by-byte */
  for (len = 0; len < sb.st_size; len++) {
    putchar(p[len]);
  }

  /* unmap file from memory */
  if (munmap(p, sb.st_size) == -1) {
    perror("munmap");
    return 1;
  }

  return 0;
}
