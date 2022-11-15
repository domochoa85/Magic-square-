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

int main()
{
	printf("%d\n", isprime(100));
	printf("%d\n", isprime(67));
	int range=5000;
	int counter=0; 
	for(int i=1; i<=range; i++)
		if (isprime(i)==true)
			counter=counter+1;
	printf("Total is %d\n", counter);

	return 0; 
}
