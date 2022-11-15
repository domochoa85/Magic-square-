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
  for(int i=0; i<size; i++)
	  ms[i] = new int[size];

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


int main()
{

	string fn;
	cout<<"Please input file name (such as ms1.txt): " ;
	cin>>fn;
	loadms(fn); //fn
	showms();
	return 0;
}
