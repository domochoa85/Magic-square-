#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include <stdlib.h>



void sig_handler(int signum){

  //Return type of the handler function should be void
  printf("\nInside handler function\n");
  sleep(5);

  //exit(-1);
}

int main()
{

	signal(SIGINT,sig_handler); // Register signal handler

	for(int i=0; i<1000000; i++)
		printf("%d", i);
	return 0; 
}


