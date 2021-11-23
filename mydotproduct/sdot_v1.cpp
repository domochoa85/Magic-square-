//dot product
#include <iostream> 
 
using namespace std; 
 
int a[] = {1,2,3,4 ,5,6,14, 3, 1, 6, 8, 9, 10, 3, 13, 44, 14, 67, 89, 
           34, 23, 69, 100, 6, 2, 3, 4, 5, 6, 18}; 
 
int b[] = {1,2,3,4,5,6, 11, 7, 8, 4, 9, 12, 10, 3, 1, 14, 7, 7, 9, 3, 3, 6, 11, 65, 2, 1, 4, 15, 8, 3}; 
 
int sum = 0; 
 
void scalculatedotproduct(int size ) { 

    for (int pos=0; pos<size; pos++) 
        sum += a[pos] * b[pos]; //store sum of element i from both arrays into sum variable 

} 
 
 
int main() { 

    scalculatedotproduct(30);

    cout << "dot product = " << sum << endl; 
    return 0;
} 
