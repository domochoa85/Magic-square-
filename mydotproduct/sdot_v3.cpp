//dot product
#include <iostream> 
#include <cmath> 
using namespace std; 
 
int a[] = {1,2,3,4 ,5,6,14, 3, 1, 6, 8, 9, 10, 3, 13, 44, 14, 67, 89, 
           34, 23, 69, 100, 6, 2, 3, 4, 5, 6, 18}; 
 
int b[] = {1,2,3,4,5,6, 11, 7, 8, 4, 9, 12, 10, 3, 1, 14, 7, 7, 9, 3, 3, 6, 11, 65, 2, 1, 4, 15, 8, 3}; 
 
int sum = 0; 
 
void scalculatedotproduct(int sid, int start, int end ) 
{ 
	cout<<"Segment: "<<sid<<", "<<start<<", "<<end<<endl;

	for (int pos=start; pos<end; pos++) 
        	sum += a[pos] * b[pos]; //store sum of element i from both arrays into sum variable 
} 
 
 
int main() { 
    int size=30;
    int start=0;
    int end=size;
    int tn=4;
    int ts=ceil(double(size)/tn);

    for(int sid=0;sid<tn;sid++)
    {
	    int sstart=sid*ts;
            int send=(sid+1)*ts;
	    if (sid==tn-1) 
		    send=size;

    	    scalculatedotproduct(sid,sstart, send);
	    cout<<sum<<endl;
    }

    cout << "dot product = " << sum << endl; 

    return 0;
} 
