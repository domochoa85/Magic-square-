//to compile: g++ -lpthread -o cfindprime_v1 cfindprime_v1.cpp
//to test 1000  times: for i in {1..1000}; do ./cfindprime_v1; done
#include <iostream>
#include <cmath>
#include <thread>
using namespace std;

int total=0;
bool isprime(int num)
{       
        int sr=sqrt(num);
        
        if (num==1) return false;
        if (num==2) return true;
        
        for(int denominator=2; denominator<=sr; denominator++)
        {       
                if (num%denominator==0)
                        return false; // early termination
        }
        return true;
}

void count_t(int tid, int lowerbound, int upperbound)
{
        //cout<<"Thread: "<<tid<<endl;
        for(int d=lowerbound; d<=upperbound; d++)
        {
                if (isprime(d))
                {       
                        ++total;
                        //cout<<total<<" " <<d<<endl;
                }
        }
}

int tsize;
int main()
{
        int noft;
        int range;
        range=987;
	noft=4;
        //cout<<"Please input a positive integer used for the upper bound: ";
        //cin>>range;
        //cout<<"Please input number of threads"<<endl;
        //cin>>noft;
        thread *t = new thread[noft]; // create thread array
        tsize=ceil(double(range)/noft);
	//cout<<"Thread size is: "<<tsize<<endl;
        for(int tid=0;tid<noft; tid++)
        {
                int tstart=tid*tsize;
                int tend;
                if (tid==noft-1)
                        tend=range; // the last one is special
                else
                        tend=(tid+1)*tsize;
                t[tid]=thread(count_t, tid, tstart, tend);
        }

       for(int tid=0; tid<noft; tid++)
                t[tid].join();

        cout<<"Total number of prime between 1 and " << range;
        cout<< " is: " <<total<<endl;
        return 0;
}

