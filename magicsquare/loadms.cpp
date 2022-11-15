#include<iostream>
#include <fstream>
#include<string>
using namespace std;

int loadms (string fn) {
  ifstream myfile;
  int rownum;
  myfile.open (fn);
  cout << "reading from a file.\n";
  myfile>>rownum;
  string arow;

  for (int row=0; row<rownum; row++)
  for (int col=0; col<rownum; col++)
  {
	myfile>>arow;
  	cout<<arow<<endl;
  }
  myfile.close();
  return 0;

}

int **ms;



int main()
{

	string fn;
	cout<<"Please input file name: " ;
	cin>>fn;
loadms("ms1.txt"); //fn
return 0;
}
