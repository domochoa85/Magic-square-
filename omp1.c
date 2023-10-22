// pre-flight commands
// grep 'processor.*:' /proc/cpuinfo | wc -l
// export OMP_NUM_THREADS=2 
// or  4 number returned by the grep command 
// export OMP_NUM_THREADS=$(grep 'processor.*:' /proc/cpuinfo | wc -l)
// echo $OMP_NUM_THREADS
//to compile, gcc -o omp1 -fopenmp omp1.c
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
