#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <thread>
using namespace std;

const int NUM_THREADS=27;	

//prototypes of functions
int loadgame(string);
void showgame();
bool validate_t();
void * check_3x3_t(void *iop);
void * check_arow_t(void *iop);
void * check_acol_t(void *iop);

int sudoku[9][9];	


class inputoutputparameter
{
public:
    int tid;
    int row; // The starting row.
    int col; // The starting column.
    //int ** game; //data
    bool flag;

    inputoutputparameter(int tid, int whichrow, int whichcol)
    {
        this->tid=tid;
        this->row=whichrow;

        this->col=whichcol;
        this->flag=true;

    }
};

int main()
{
	string filename;

	cout<<"Please input the name of the file holding a SUDOKU game: "<<endl;
	cin>>filename;

	int code=loadgame(filename);
	switch (code)
	{
		case 1: 
			cerr<<"Wrong format! Sudoku should be 9 cols!"<<endl;	
			return EXIT_FAILURE;
			break;
		case 2:
      			cerr << "Wrong format, only 1-9 allowed"<<endl;
			return EXIT_FAILURE;
			break;
		case 3:
      			cerr << "Wrong format, 9 rows"<<endl;
			return EXIT_FAILURE;
			break;
		
		case 4:
			cerr<<"File operation failure"<<endl;
			break;
	}

	showgame();

	if (validate_t())
		cout<<"Good status"<<endl;
	else
		cout<<"Illegal status"<<endl;

	return EXIT_SUCCESS; 
}


bool validate_t()
{
	thread * threads=new thread[NUM_THREADS];

	inputoutputparameter **iopa=new inputoutputparameter*[NUM_THREADS];

	int threadIndex=0;

	for(int row=0; row<9; row++)
	{
		inputoutputparameter *iop=new inputoutputparameter(threadIndex, row,-1);		
		iopa[threadIndex]=iop;
		threads[threadIndex++]=thread(check_arow_t, iop);
	}

	for(int col=0; col<9; col++)
	{
		inputoutputparameter *iop=new inputoutputparameter(threadIndex, -1, col);	
		iopa[threadIndex]=iop;
		threads[threadIndex++]=thread( check_acol_t, iop);
	}

	for(int row=0; row<3; row++)
		for(int col=0; col<3; col++)
		{
			inputoutputparameter *iop=new inputoutputparameter(threadIndex, row*3, col*3);		
			iopa[threadIndex]=iop;
			threads[threadIndex++]=thread( check_3x3_t, iop);
		}
        cout<<"before all joining"<<endl;
	bool flag=true;

	for(int i=0; i<NUM_THREADS; i++)
	{
        	cout<<"joining: "<< i<<", " <<iopa[i]->tid <<", "<<iopa[i]->row <<", "<<iopa[i]->col<< ", "<<iopa[i]->flag<<endl;
		threads[i].join();;

		if(iopa[i]->flag==false)
		{
			cout<<i<<", "<< iopa[i]->row<<", "<< iopa[i]->col <<" isn't correct "<<endl;
			flag=false;
		}
	}

        cout<<"after all joining"<<endl;

	if (flag==true)
	{
		cout<<"Good configuration"<<endl;
	}

	return flag;
}


void showgame()
{
	for (int row=0; row<9; row++)
	{
		for(int col=0; col<9; col++)
			cout<<sudoku[row][col]<<"\t";
		cout<<endl;
	}

}

int loadgame(string filename)
{
	ifstream hgf; //handle for the game file

        #define toDigit(c) (c-'0')
	string arow;	
	int row=0;
	int returncode=0;
	try{
		hgf.open(filename);
		for (row=0; row<9; row++)
		{
			//read row by row 
			hgf >> arow; 
			if (arow.length()!=9)
			{
				returncode=1;
				break;
			}
			regex int_re=regex("^([1-9]+)$") ;
			if (!regex_match (arow, int_re))
			{
				returncode=2;
				break;
			}
	
			for(int col=0; col<9; col++)
			{
				sudoku[row][col]=toDigit(arow[col]);
			}
		}

		hgf.close();

		if (returncode==0 && row<9)
			returncode= 3;

	}
	catch(exception e)
	{
		returncode=4;
	}
	
	return returncode;
	
}

void *check_3x3_t(void *params)
{
	inputoutputparameter * iop=(inputoutputparameter *) params;
	int startRow=iop->row;
	int startCol=iop->col;
	cout<<iop->tid<< ","<<startRow<<", "<<startCol<<endl;

    int validarray[10] = {0}; //10 possible values 0-9
     iop->flag=true;
    for (int row = startRow; row < startRow + 3; ++row)
    {
        for (int col = startCol; col < startCol + 3; ++col)
        {
            int val = sudoku[row][col];

            if (validarray[val] != 0)
               iop->flag= false;
            else
                validarray[val] = 1;
        }
    }
    //If the execution has reached this point, then the 3x3 sub-grid is valid.
     cout<<"check 3X3 : "<<iop->tid<<", "<<iop->flag<<" flag. "<<endl;
     
     return NULL;
}

/**
 * Checks each row if it contains all digits 1-9.
 * There is an array called validarray[10] initialized to 0.
 * For every value in the row, the corresponding index in validarray[] is checked for 0 and set to 1.
 * If the value in validarray[] is already 1, then it means that the value is repeating. So, the sudoku is invalid.
 *
 * @param   void *      The parameters (pointer).
 */


void *check_acol_t(void *params)
{
	inputoutputparameter * iop=(inputoutputparameter *) params;
	int startCol=iop->col;
	cout<<iop->tid<< ", "<<iop->row<<", "<<startCol<<endl;
	
     iop->flag= true;
    int validarray[10] = {0}; //10 possible values 0-9
    for (int row = 0; row < 9; ++row)
    {
            int val = sudoku[row][startCol];

            if (validarray[val] != 0)
               iop->flag= false;
            else
                validarray[val] = 1;
     }
    //If the execution has reached this point, then the 3x3 sub-grid is valid.
     cout<<"check col: "<<iop->tid<<", "<<iop->flag<<" flag. "<<endl;
	return NULL;
}

void *check_arow_t(void *params)
{
	inputoutputparameter * iop=(inputoutputparameter *) params;
	int startRow=iop->row;
	
	cout<<"Thread id"<<iop->tid<< ","<<startRow<<", "<<iop->col<<endl;
	
     iop->flag= true;
    int validarray[10] = {0}; //10 possible values 0-9
    for (int col = 0; col < 9; ++col)
    {
            int val = sudoku[startRow][col];

            if (validarray[val] != 0)
               iop->flag= false;
            else
                validarray[val] = 1;
        }
    //If the executio3 has reached this point, then the 3x3 sub-grid is valid.
     cout<<"check row: "<<iop->tid<<", "<<iop->flag<<" flag. "<<endl;
	return NULL;
}

