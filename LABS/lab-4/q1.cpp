#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t child1, child2, child3, child4;
  int status;
  char *argList1[] = {"ls", "-l", NULL};
  char *cmd = "/bin/ls";
  char *argList2[] = {"ls", "-lh", NULL};
  child1 = fork();
  fflush(stdin);
  if (child1 < 0) {
    printf("Error\n");
    return 1;
  } else if (child1 == 0) {
    printf("In child1 executing execvp\n");
    execvp("/bin/ls", argList1);

  } else if (child1 > 0) {
    wait(&status);
    child2 = fork();
    if (child2 == 0) {
      printf("In child2 executing execlp\n");
      execlp("/bin/mkdir", "mkdir","TestFolder",NULL);
    } else {
      wait(&status);
    }

    child3 = fork();
    if (child3 == 0) {
      printf("In child3 executing execvp\n");
      execvp("/bin/ls", argList2);
    } else {
      wait(&status);
    }
  }
}
