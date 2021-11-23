//dot product
#include <iostream> 
#include <cmath> 
#include <thread>
#include <mutex>
#include<condition_variable>

using namespace std; 


int a[] = {1,2,3,4 ,5,6,14, 3, 1, 6, 8, 9, 10, 3, 13, 44, 14, 67, 89, 
           34, 23, 69, 100, 6, 2, 3, 4, 5, 6, 18}; 
 
int b[] = {1,2,3,4,5,6, 11, 7, 8, 4, 9, 12, 10, 3, 1, 14, 7, 7, 9, 3, 3, 6, 11, 65, 2, 1, 4, 15, 8, 3}; 
 
 bool ready = false;
bool processed = false;
int tsum2=0;
mutex mtx;
condition_variable cv;
int whichid;

void scalculatedotproduct(int tid, int start, int end ) 
{ 
	int tsum=0;
	//cout<<"Segment: "<<tid<<", "<<start<<", "<<end<<endl;
	for (int pos=start; pos<end; pos++) 
	{
        	(tsum) += a[pos] * b[pos]; //store sum of element i from both arrays into sum variable 
	}

    
// Wait until main() readya
    std::unique_lock<std::mutex> lk(mtx);
 cv.wait(lk, []{return ready;}); 

    // after the wait, we own the lock.
    cout << "Worker thread is processing data\n";
 
    // Send data back to main()
    whichid=tid;
    tsum2=tsum;

    cout << "Worker thread signals data processing completed\n";
processed = true; 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_all();

} 



 
int main() { 
    int sum = 0; 
    int size=30;
    int start=0;
    int end=size;
    int tn=4;
    int ts=ceil(double(size)/tn);
    int total;

    thread * tarray=new thread[tn];
    int *tsumarray=new int[tn];

    /*
    lock_guard<std::mutex> lk(mtx);
    cout << "main() signals data ready for processing\n";
    cv.notify_one();
*/
    for(int tid=0;tid<tn;tid++)
    {
	    int sstart=tid*ts;
            int send=(tid+1)*ts;
	    if (tid==tn-1) 
		    send=size;

    	    tarray[tid]=thread(scalculatedotproduct,tid,sstart, send);
	    //cout<<sum<<endl;
    }

    for(int tid=0; tid<tn; tid++)
    {


	    {
        lock_guard<mutex> lk(mtx);
	ready = true;
        cout << "main() signals data ready for processing\n";
	    }
	    cv.notify_all();
 
        // wait for the worker
	    { unique_lock<mutex> lk(mtx);
	     cv.wait(lk, []{return processed;});
	    }
        sum += tsum2;
	tarray[whichid].join();
    }

    cout << "dot product = " << sum << endl; 
    return 0;
} 
