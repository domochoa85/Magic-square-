//gcc -o sequentialprime sequentialprime.c -lm
//./sequentialprime

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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

void *findprime(int ts, int te, int tid)
{
	int counter=0; 
	for(int i=ts; i<=te; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total in the subrange from %d to %d is %d found by thread %d\n", ts, te, counter, tid);
}

int main()
{
	printf("%d\n", isprime(100));
	printf("%d\n", isprime(67));
	int range=401;
	int counter=0; 


	int tn=4;
	int tsize= ceil((double)range/tn); 
	printf("%d on per thread\n", tsize);
        
	for(int tc=0; tc<tn; tc++)
	{
		int start=tsize*tc;
		int end=start+tsize;
		if (tc==tn-1) // the last thread 
			end=range;
		printf("%d segment starting from %d, ending at %d\n", tc, start, end);

		findprime(start+1, end, tc);
	}

	for(int i=1; i<=range; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total is %d\n", counter);



	return 0; 
}
