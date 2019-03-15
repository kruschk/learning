/* Read a file and print out the information that was read. */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
  char *file = "/home/jonah/LSP/read.txt";
  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    printf("failed to open file\n");
    return -1;
  }
  else {
    size_t BUFFER_SIZE = 1048576;
    char word[BUFFER_SIZE];
    //unsigned long word;
    ssize_t nr;
    /* read a couple bytes into 'word' from 'fd' */
    nr = read(fd, word, sizeof(word));
    if (nr == -1) {
      printf("failed to read file\n");
      return -1;
    }
    else {
      printf("word: %s", word);
      /*
      for (int i = 0; i < nr; ++i) {
	putchar(word[i]);
      }
      */
      printf("number of bytes read: %lu\n", nr);
      return 0;
    }
  }
}
