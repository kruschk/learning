#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
  int fd;
  fd = open("/home/jonah/linux_sys_prog/test.txt", O_WRONLY | O_TRUNC);

  if (fd == -1) {
    perror("open");
  }
  else {
    /*
    char c;
    
    while (c = getchar(fd) != EOF) {
      putchar(c);
    }
    */
  }
}
