// pre-flight commands
// grep 'processor.*:' /proc/cpuinfo | wc -l
// export OMP_NUM_THREADS=2

//to compile, gcc -o omp1 -fopenmp thisexample.c
// https://www.linuxtoday.com/blog/openmp/

#include <omp.h> // OpenMP header
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	// parallel region
	#pragma omp parallel
	{

		printf("Oneonta 4430 from thread = %d\n", omp_get_thread_num());
	}
	// Ending of parallel region
}
