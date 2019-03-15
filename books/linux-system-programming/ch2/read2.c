/* Read a file and print out the information that was read, with better error
   handling. */

#include <sys/types.h> /* for open() */
#include <sys/stat.h> /* for open() */
#include <fcntl.h> /* for open() */
#include <unistd.h> /* for read() */
#include <stdio.h>
#include <stdint.h>
#include <errno.h> /* include errno */
#include <stdlib.h> /* include malloc() and free() */

int main(void) {
  char *file = "/home/jonah/LSP/read.txt";
  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    printf("failed to open file\n");
    return -1;
  }
  else {
    const size_t BUFFER_SIZE = 1048576;
    size_t len = BUFFER_SIZE;
    char *buf = malloc(len);
    ssize_t ret;
    while (len != 0 && (ret = read(fd, buf, len)) != 0) {
      if (ret == -1) {
	if (errno == EINTR) {
	  continue;
	}
	perror ("read");
	break;
      }
      len -= ret;
      buf += ret;
    }
    //printf("%s", buf);
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
      putchar(buf[i]);
    }
    free(buf);
  }
}
