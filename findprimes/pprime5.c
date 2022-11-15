//gcc -o pprime3 pprime3.c -lm -lpthread
//./pprime3

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

struct arg_struct{
    int start;
    int end;
    int tid;
    int counter;
} ;

bool isprime(int num) // assume num >0
{
	if (num==1) return false;
	if (num==2) return true; 
	int b=sqrt((double)(num));
	for(int deno=2; deno<=b; deno++)
	{
		if (num%deno==0)
			return false;
					
	}
	return true;

}

void *findprime(void *argv)
{
	struct arg_struct *arg=(struct arg_struct *)argv;

	int counter=0; 
	for(int i=arg->start; i<=arg->end; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total in the subrange from %d to %d is %d found by thread %d\n", arg->start, arg->end, counter, arg->tid);

	int exitcode=0; // communicating with the main thread via exitcode.
	arg->counter=counter;
	pthread_exit(&exitcode);
}

int main()
{
	//printf("%d\n", isprime(100));
	//printf("%d\n", isprime(67));
	int range=401;
	int counter=0; 
	int total=0;

	pthread_t *threads;
	void **status;
	struct arg_struct *args;

	int tn; //Number of Threads
	printf("Please input range (e.g. 3000)");
	scanf("%d", &range);
	printf("Please input number of threads");
	scanf("%d", &tn);

	printf("dynamically allocating arrays");
	threads=malloc(sizeof(pthread_t)*tn);
	status=malloc(sizeof(void *)*tn);
	args=malloc(sizeof(struct arg_struct)*tn);

	int tsize= ceil((double)range/tn); 

	printf("%d on per thread\n", tsize);
       
	for(int tc=0; tc<tn; tc++)
	{
		int start=tsize*tc;
		int end=start+tsize;
		if (tc==tn-1) // the last thread 
			end=range;

		args[tc].start=start+1;
		args[tc].end=end;
		args[tc].tid=tc;
		printf("%d thread starting from %d, ending at %d\n", tc, start+1, end);
		pthread_create(&threads[tc], NULL, findprime, (void*)(&args[tc]));

	}
	
	for(int tc=0; tc<tn; tc++)
	{
		pthread_join(threads[tc], &status[tc]);
		total=total+args[tc].counter;
	}

	printf("Total from multiple threads is %d\n", total);

	for(int i=1; i<=range; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total by single scan is %d\n", counter);

	printf("free dynamically allocated space");
	free(status);
	free(args);
	free(threads);

	return 0; 
}
