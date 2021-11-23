//dot product
#include <iostream> 
#include <cmath> 
#include <thread>
using namespace std; 


int a[] = {1,2,3,4 ,5,6,14, 3, 1, 6, 8, 9, 10, 3, 13, 44, 14, 67, 89, 
           34, 23, 69, 100, 6, 2, 3, 4, 5, 6, 18}; 
 
int b[] = {1,2,3,4,5,6, 11, 7, 8, 4, 9, 12, 10, 3, 1, 14, 7, 7, 9, 3, 3, 6, 11, 65, 2, 1, 4, 15, 8, 3}; 
 
 
void scalculatedotproduct(int tid, int start, int end, int *tsum ) 
{ 
	//cout<<"Segment: "<<tid<<", "<<start<<", "<<end<<endl;
	for (int pos=start; pos<end; pos++) 
	{
        	(*tsum) += a[pos] * b[pos]; //store sum of element i from both arrays into sum variable 
	}
} 
 
 
int main() { 
    int sum = 0; 
    int size=30;
    int start=0;
    int end=size;
    int tn=4;
    int ts=ceil(double(size)/tn);
    thread * tarray=new thread[tn];
    int *tsumarray=new int[tn];

    for(int tid=0;tid<tn;tid++)
    {
	    int sstart=tid*ts;
            int send=(tid+1)*ts;
	    if (tid==tn-1) 
		    send=size;

    	    tarray[tid]=thread(scalculatedotproduct,tid,sstart, send,&tsumarray[tid]);
	    //cout<<sum<<endl;
    }


    for(int tid=0; tid<tn; tid++)
    {
   	tarray[tid].join(); 
	sum+=tsumarray[tid];
    }

    cout << "dot product = " << sum << endl; 
    return 0;
} 
