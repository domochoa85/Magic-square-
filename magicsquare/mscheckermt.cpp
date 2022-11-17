#include<iostream>
#include <fstream>
#include<string>
#include <thread>

using namespace std;

class inputoutputparameter
{
public:
    int tid;
    int index; // index could be row or col for different checkers 
    bool flag; // communicate the status of validation

    inputoutputparameter(int tid, int whichindex)
    {
        this->tid=tid;
        this->index=whichindex;
        this->flag=true;
    }
};

int **ms; // reserve a pointer to a 2d array
int size;
int numberofthreads;

int loadms (string fn) {
  ifstream myfile;
  myfile.open (fn);
  cout << "reading from a file.\n";
  myfile>>size;
  int acell;

  //two levels of dynamic memory allocation for 2d array
  ms=new int *[size];
  for(int row=0; row<size; row++)
	  ms[row] = new int[size];
  

  for (int row=0; row<size; row++)
  for (int col=0; col<size; col++)
  {
	myfile>>acell; // read one token a time!
	ms[row][col]=acell;
  }

  myfile.close();
  return 0;

}

void showms()
{

  for (int row=0; row<size; row++)
  {
	for (int col=0; col<size; col++)
  	{
		cout<<ms[row][col]<<"\t";
	}
	cout<<endl;
  }

}

int magicnumber;

void * checkbwdiag(void *params) // the backward diagnal /
{
	inputoutputparameter * iop=(inputoutputparameter *) params;
	int sum=0;
	for(int row=0; row<size; row++)
	{
		int col=size-1-row; 
		sum+=ms[row][col];
	}
	iop->flag = sum==magicnumber; 	
	return nullptr;
}

void * checkacol(void * params)
{  
	inputoutputparameter * iop=(inputoutputparameter *) params;
	int sum=0;
	for(int row=0; row<size; row++)
	{
		sum+=ms[row][iop->index];
	}
	
	iop->flag=(sum==magicnumber);
	return nullptr; // NULL

}

bool flag=true;

void validate_ms()
{
	thread *threads= new thread[numberofthreads];
	inputoutputparameter **iopa=new inputoutputparameter*[numberofthreads];

	int threadIndex=0; 
	//check bw diagnal
	inputoutputparameter *iop=new inputoutputparameter(threadIndex, -1); // -1 is just a placeholder
	iopa[threadIndex]=iop;		
	threads[threadIndex++]=thread(checkbwdiag, iop);

	//check fw diagnal, yourwork

	//launch number of size threads, each checking a col
        for(int col=0; col<size; col++)
	{
	
		inputoutputparameter *iop=new inputoutputparameter(threadIndex, col);		
		iop->index=col;
		iopa[threadIndex]=iop;		
		threads[threadIndex++]=thread(checkacol, iop);
	
	}	
	//
	//launch number of size threads, each checking a row, your work
	//
	//
	cout<<"before all joining"<<endl;
	flag=true;

	for(int i=0; i<numberofthreads; i++)
	{
        	cout<<"joining: "<< i<<", " <<iopa[i]->tid <<", "<<iopa[i]->index<< ", "<<iopa[i]->flag<<endl;

		threads[i].join();

		if(iopa[i]->flag==false)
		{
			cout<<i<<", "<< iopa[i]->index <<" isn't correct "<<endl;
			flag=false;
		}
	}

	cout<<"after all joining"<<endl;

	return ;
}



int main()
{

	string fn;
	cout<<"Please input file name (such as ms1.txt): " ;
	cin>>fn;
	loadms(fn); //fn
	showms();
	magicnumber=size*(size*size+1)/2;
	numberofthreads=2*size+2; 

	validate_ms();
	if (flag == true)
		cout<<"Magical"<<endl;
	else
		cout<<"Illegal status"<<endl;

	return EXIT_SUCCESS; //0
}
