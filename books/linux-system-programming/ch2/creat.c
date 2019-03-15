#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
  int fd;
  char *file = "/home/jonah/linux_sys_prog/test.txt";

  /*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
    S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);*/
  fd = creat(file, 0664);

  if (fd == -1) {
    printf("wuh-oh\n");
  }
  else {
    printf("no wuh-oh!\n");
  }
}
