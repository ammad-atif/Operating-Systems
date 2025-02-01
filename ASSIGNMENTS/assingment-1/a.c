#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define str_size 1000
#define args_size 100

int cmd_handler(char **args) {
  if (strcmp(args[0], "exit") == 0) {
    printf("\nEXITED\n");
    exit(0);
    return 1;
  } else if (strcmp(args[0], "cd") == 0) {
    chdir(args[1]);
    return 1;
  } else {
    return 0;
  }
}

void clear() { system("clear"); }

// void user()
// {
// 	char *username = getenv("USER");
// 	printf("%s", username);
// }

void print_cwd() {
  char arr[str_size];
  getcwd(arr, str_size);
  printf("%s", arr);
  printf("$: ");
}

int takeinput(char *str) {
  fgets(str, str_size, stdin);
  int len;
  len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
  if (strlen(str) != 0) {
    return 1;
  } else {
    return 0;
  }
}

int tokenize(char *str, char **args, int *n) {
  char *token;
  token = strtok(str, " ");
  while (token != NULL) {
    args[(*n)++] = token;
    token = strtok(NULL, " ");
  }
  args[(*n)++] = NULL;
}

void execute_command(char *args[]) {

  pid_t new_process = fork();
  if (new_process < 0) {
    return;
  } else if (new_process == 0) {
    if (execvp(args[0], args) < 0) {
      perror("execvp");
      printf("not operated successfully");
      printf("\n");
      exit(EXIT_FAILURE); //?
    }
  } else {
    wait(NULL);
    return;
  }
}

int main() {
  char str[str_size];
  char *args[args_size];
  int no_of_args = 0;
  clear();
  while (1) {
    print_cwd();
    if (takeinput(str)) {
      tokenize(str, args, &no_of_args);
      // printf("%d", no_of_args);
      // printf("\n");
      // for (int i = 0; i < no_of_args; i++)
      // {
      //     printf("%s", args[i]);
      //     printf("\n");
      // }
      if (!cmd_handler(args)) {
        execute_command(args);
      }
      no_of_args = 0;
    }
  }
}