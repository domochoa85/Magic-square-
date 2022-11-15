//gcc -o pprime3 pprime3.c -lm -lpthread
//./pprime3

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>

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
	printf("%d\n", isprime(100));
	printf("%d\n", isprime(67));
	int range=401;
	int counter=0; 
	int total=0;

	const int NUM_THREADS=4; //Number of Threads

	pthread_t threads[NUM_THREADS];
	void * status[NUM_THREADS];
	struct arg_struct args[NUM_THREADS];

	int tsize= ceil((double)range/NUM_THREADS); 
	printf("%d on per thread\n", tsize);
       
	for(int tc=0; tc<NUM_THREADS; tc++)
	{
		int start=tsize*tc;
		int end=start+tsize;
		if (tc==NUM_THREADS-1) // the last thread 
			end=range;

		args[tc].start=start+1;
		args[tc].end=end;
		args[tc].tid=tc;
		printf("%d thread starting from %d, ending at %d\n", tc, start+1, end);
		pthread_create(&threads[tc], NULL, findprime, (void*)(&args[tc]));

	}
	
	for(int tc=0; tc<NUM_THREADS; tc++)
	{	pthread_join(threads[tc], &status[tc]);
		total=total+args[tc].counter;
	}
	printf("Total from all threads is %d\n", total);


	for(int i=1; i<=range; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total in one scan is %d\n", counter);



	return 0; 
}
