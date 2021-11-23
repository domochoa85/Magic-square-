//dot product
#include <iostream> 
#include <cmath> 
#include <thread>

using namespace std; 
 
int a[] = {1,2,3,4 ,5,6,14, 3, 1, 6, 8, 9, 10, 3, 13, 44, 14, 67, 89, 
           34, 23, 69, 100, 6, 2, 3, 4, 5, 6, 18}; 
 
int b[] = {1,2,3,4,5,6, 11, 7, 8, 4, 9, 12, 10, 3, 1, 14, 7, 7, 9, 3, 3, 6, 11, 65, 2, 1, 4, 15, 8, 3}; 
 
int sum = 0; 
 
void scalculatedotproduct(int tid, int start, int end ) 
{ 
	//cout<<"Segment: "<<tid<<", "<<start<<", "<<end<<endl;

	for (int pos=start; pos<end; pos++) 
        	sum += a[pos] * b[pos]; //store sum of element i from both arrays into sum variable 
} 
 
 
int main() { 
    int size=30;  // size of array 
    int start=0;  // first index
    int end=size; // size of the  
    int tn=4;     //number of threads

    int ts=ceil(double(size)/tn);   //thread size
    thread * tarray=new thread[tn]; //thred array

    for(int tid=0;tid<tn;tid++)
    {
	    int tstart=tid*ts;
            int tend=(tid+1)*ts;
	    if (tid==tn-1) 
		    tend=size;

    	    tarray[tid]=thread(scalculatedotproduct,tid,tstart, tend);

	    //cout<<sum<<endl;
    }

    //wait all threads completing
    for(int tid=0; tid<tn; tid++)
    {
   	tarray[tid].join(); // a blocking function, resume when the thread finsihes.
    }

    cout << "dot product = " << sum << endl; 

    return 0;
} 
