#include <cinttypes>
#include <inttypes.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int status;
  if(argc<3){
    printf("Error!!! Arguments too low!!! Give input name and output name\nExample: ./run.cpp input.cpp ./output\n");
    return 1;

  }
  char *cmd = "/bin/gcc";
  char *argList[] = {"g++", argv[1], "-o", argv[2], NULL};
  pid_t child = fork();
  if (child < 0) {
    printf("Error \n");
    return 1;
  } else if (child == 0) {
    execvp(cmd, argList);
  }
  else {
    wait(&status);
    int child2=fork();
    if(child2<0){
        printf("Error \n");
    }
    else if(child2==0){
        execvp(argv[2],NULL);
    }
    else {
        wait(&status);
    }
    printf("Program Completed\n");
  }
}
