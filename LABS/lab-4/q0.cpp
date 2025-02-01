#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t child1, child2, child3, child4;
  int status;
  char *argList[] = {"ls", "-l", NULL};
  child1 = fork();
  fflush(stdin);
  if (child1 < 0) {
    printf("Error\n");
    return 1;
  } else if (child1 == 0) {
    printf("In child1 executing execvp\n");
    execvp("/bin/ls", argList);

  }
  // else if(child2==0){
  //     printf("In child2 executing execlp\n");
  //      execlp("/bin/ls", "ls","-l",NULL);
  // }
  else if (child1 > 0) {
    wait(&status);
  }
  // else if(child2>0){
  //     wait(&status);
  //     return 0;
  // }
}
