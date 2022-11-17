#include<iostream>
#include <fstream>
#include<string>
using namespace std;

int **ms; // reserve a pointer to a 2d array
int size;

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
bool checkbwdiag() // the backward diagnal /
{
	int sum=0;
	for(int row=0; row<size; row++)
	{
		int col=size-1-row; 
		sum+=ms[row][col];
	}
	
	return (sum==magicnumber);
}

bool checkacol(int whichcol)
{
	int sum=0;
	for(int row=0; row<size; row++)
	{
		sum+=ms[row][whichcol];
	}
	
	return (sum==magicnumber);

}

bool flag=true;

int main()
{

	string fn;
	cout<<"Please input file name (such as ms1.txt): " ;
	cin>>fn;
	loadms(fn); //fn
	showms();
	magicnumber=size*(size*size+1)/2;

	//check backward diagnal
	if(!checkbwdiag())
	{
		cout<<"Not a magic square!"<<endl;
		flag=false;
		return -1;
	}

	//check forward diagnal, your work
	
	
	//check each column
	for( int col= 0; col<size; col++)
	{
		if(!checkacol(col))
		{
			cout<<"Not a magic square! " << "detected on col " <<col<<endl;
			flag=false;
			return -1; 
			//break;
		}
	}

	//check each row, your work

	cout<<"It is a magic square!"<<endl;

	return 0;
}
