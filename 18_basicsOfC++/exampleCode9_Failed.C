#include <iostream> //Just for cout
using namespace std; //Just for cout
#include "tensor.H" //From OpenFOAM
#include "symmTensor.H" //From OpenFOAM
using namespace Foam; //From OpenFOAM
int main()
{ tensor t1(1, 2, 3, 4, 5, 6, 7, 8, 9); //From OpenFOAM
cout << "t1[0]: " << t1[0] << endl;
symmTensor st1(1, 2, 3, 4, 5, 6); //From OpenFOAM
cout << "st1[5]: " << st1[5] << endl;
return 0;
}