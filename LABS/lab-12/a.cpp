#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int main(int argc, char **argv) {
  if (argc < 3 || argc > 3) {
    cout << "error" << endl;
    exit(EXIT_FAILURE);
  }

  char *args[2] = {argv[1], NULL};
  int child = fork();
  if (child < 0) {
    printf("Error creating child\n");
    exit(EXIT_FAILURE);
  } else if (child == 0) {
    int fd = open(argv[2], O_WRONLY);
    dup2(fd, STDOUT_FILENO);
    execvp(argv[1], args);
  } else if (child > 0) {
    wait(NULL);
    exit(0);
  }
}