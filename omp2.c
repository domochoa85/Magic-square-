#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define _GNU_SOURCE // sched_getcpu(3) is glibc-specific 

// export OMP_NUM_THREADS=$(grep 'processor.*:' /proc/cpuinfo | wc -l)

//gcc -o omp2 -fopenmp omp2.c -D_GNU_SOURCE

int main (int argc, char *argv[])  { 
int nthreads, tid; 
// Fork a team of threads giving them their own copies of variables 
#pragma omp parallel private(nthreads, tid) 
 { 
   tid = omp_get_thread_num();               
// Obtain thread number 
    int cpu_num = sched_getcpu();

   printf("Hello World from thread = %3d on cpu %3d.\n", tid, cpu_num); 

if (tid == 0) {  // Only master thread does this 
  nthreads = omp_get_num_threads(); 
printf("Number of threads = %d\n", nthreads); 
   } 
}     
// All threads join master thread and disband 
 return(0); 
} 