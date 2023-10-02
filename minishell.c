#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void printmenu()
{
	printf("0. exit\n");
	printf("1. ls \n");
	printf("2. uname -r\n");

}

int main()
{
   int choice;
   int flag;
   int status;

   do
	{
	printmenu();
	scanf("%d", &choice);
	pid_t pid=fork();

	if (pid==0)	
	{
		switch (choice)
		{
			case 1:
				execl("/usr/bin/ls", "ls", NULL);
				printf("no chance to run?"); //
				break; // 
			case 2:
				execl("/usr/bin/uname", "uname", "-r", NULL);
				break;
			case 0: 
				break;
		}
	}
	if (pid>0)
	{
pid = wait(&status);
  printf("End of process %d: ", pid);

  if (WIFEXITED(status)) {
    printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
  }

  if (WIFSIGNALED(status)) {
    printf("The process ended with kill -%d.\n", WTERMSIG(status));
  }	
  }
	
}while(choice!=0);

   printf("Bybey.... myshell exit\n");
   return 0;
}
