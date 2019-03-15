int main(void) {
  char buf[BUFSIZE];
  ssize_t nr;

start:
  nr = read(fd, buf, BUFSIZE);
  if (nr == -1) {
    if (errno == EINTR) {
      goto start;
    }
    if (errno == EAGAIN) {
    }
    else {
      perror("error");
    }
  }
}
