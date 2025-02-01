#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(int s, char *args[]) {
  cout << "called array done" << endl;
  int n = stoi(args[1]);
  int avg = 0;

  for (int i = 0; i < n; i++) {
    avg += stoi(args[i + 2]);
  }

  cout << avg / n << endl;
}