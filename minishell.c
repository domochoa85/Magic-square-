#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void printmenu() {
  printf("=======Mini Shell by S. Z. =========\n");
  printf("0. exit\n");
  printf("1. ls -l\n");
  printf("2. uname -r\n");
  printf("3. top\n");
  printf("=====Select a command to run.========\n");
}

int main() {
  int choice;
  int flag;
  int status;
  signal(SIGINT, SIG_IGN);
  do {
    printmenu();
    scanf("%d", &choice);
    pid_t pid = fork();

    if (pid == 0) {
      switch (choice) {
      case 1:
        execl("/usr/bin/ls", "ls", "-l",NULL);
        printf("no chance to run?"); //
        break;                       //
      case 2:
        execl("/usr/bin/uname", "uname", "-r", NULL);
        break;
      case 3:
        execl("/usr/bin/top", "top", NULL);
        break;
      case 0:
        break;
      }
    }
    if (pid > 0) {
      pid = wait(&status);
      printf("End of process %d: ", pid);

      if (WIFEXITED(status)) {
        printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
      }

      if (WIFSIGNALED(status)) {
        printf("The process ended with kill -%d.\n", WTERMSIG(status));
      }
    }

  } while (choice != 0);

  printf("Byebye.... myshell exit\n");
  return 0;
}
