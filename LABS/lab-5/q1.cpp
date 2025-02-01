#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {

  int pipe1[2];
  int pipe2[2];

  int p1 = pipe(pipe1);
  int p2 = pipe(pipe2);

  if (p1 < 0) {
    perror("pipe");
    exit(1);
  }
  if (p2 < 0) {
    perror("pipe");
    exit(1);
  }

  pid_t child_pid = fork();

  if (child_pid == -1) {
    perror("Error creating fork");
    return 1;
  }

  if (child_pid == 0) {
    char buffer[1000];
    ssize_t inputSize = read(pipe1[0], buffer, sizeof(buffer));

    // remove numbers
    for (int i = 0; i < inputSize; i++) {
      if (buffer[i] >= '0' && buffer[i] <= '9')
        buffer[i] = ' ';
    }

    write(pipe2[1], buffer, inputSize);
    close(pipe1[0]);
  } else {

    int f = open("file.txt", O_RDONLY);
    if (f < 0) {
      perror("Error opening file for reading");
      return 1;
    }

    char buffer[1000];
    ssize_t bytesRead = read(f, buffer, sizeof(buffer));
    if (bytesRead < 0) {
      perror("Error reading from file");
      close(f);
      return 1;
    }
    close(f);

    write(pipe1[1], buffer, bytesRead);
    close(pipe1[1]);

    char result[1000];
    ssize_t bytesWritten = read(pipe2[0], result, sizeof(result));
    if (bytesWritten < 0) {
      perror("Error reading from pipe");
      return 1;
    }

    int f1 = open("updated.txt", O_WRONLY);
    if (f1 < 0) {
      perror("Error opening file for writing");
      return 1;
    }

    write(f1, result, bytesWritten);
    close(f1);
  }

  return 0;
}