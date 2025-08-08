#include <iostream>
using namespace std;
int main()
{
double d1=2.1;
double d2=3.7;
double* d3; //d3 is a pointer, currently not pointing at anything
d3 = &d1; //Now d3 points at the memory location of d1
cout << "d1: " << d1 << endl;//2.1
cout << "d2: " << d2 << endl;//3.7
cout << "d3: " << d3 << endl;// addresss of d1
cout << "*d3: " << *d3 << endl;//2.1
d3 = &d2; //Now d3 points at the memory location of d2
cout << "d3: " << d3 << endl;//adress of d2;
cout << "*d3: " << *d3 << endl;//3.7
return 0;}