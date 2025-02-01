#include <cstdio>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t child1, child2, child3;

//   char *cmd1 = "/bin/mkdir";
//   char *cmd1List[] = {"mkdir", "./myFolder1", "./myFolder2", NULL};
//   char *cmd2 = "/bin/mkdir";
//   char *cmd2List[] = {"mkdir", "/myFolder1/mySubFolder", NULL};
int status;
  child1 = fork();

  if (child1 < 0 || child2 < 0 || child3 < 0) {
    printf("Error!!! Creatinfg child\n");
    return 1;
  } else if (child1==0){
    printf("In Child1 Making Two Folder\n");
    fflush(stdout);
    execlp("/bin/mkdir","mkdir","myFolder1","myFolder2",NULL);
    sleep(2);
  }
  else {
    wait(&status);
    child2=fork();
    if(child2==0){
        printf("In Child2 Making SubFolder\n");
        fflush(stdout);
        execlp("/bin/mkdir","mkdir","./myFolder1/mySubFolder",NULL);
        sleep(2);
    }
    else {
        wait(&status);
        
    }
    child3=fork();
    if(child3==0){
        printf("In Child3 Mlisting files\n");
        fflush(stdout);
        execlp("/bin/ls","ls","-S",NULL);
        sleep(2);
    }
    else{
        wait(&status);
    }
  }
}
