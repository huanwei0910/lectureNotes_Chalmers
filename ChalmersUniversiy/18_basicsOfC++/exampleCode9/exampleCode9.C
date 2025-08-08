#include <iostream> //Just for cout
using namespace std; //Just for cout
#include "tensor.H" //From OpenFOAM
#include "symmTensor.H" //From OpenFOAM
using namespace Foam; //From OpenFOAM

// g++ -std=c++11 exampleCode9.C \
//     -DWM_DP -DWM_LABEL_SIZE=32 \
//     -I$WM_PROJECT_DIR/src/OpenFOAM/lnInclude \
//     -I$WM_PROJECT_DIR/src/OSspecific/POSIX/lnInclude \
//     -I$WM_PROJECT_DIR/src \
//     -L$WM_PROJECT_DIR/platforms/$WM_OPTIONS/lib \
//     -lOpenFOAM \
//     -o exampleCode9

int main()
{ tensor t1(1, 2, 3, 4, 5, 6, 7, 8, 9); //From OpenFOAM
cout << "t1[0]: " << t1[0] << endl;
symmTensor st1(1, 2, 3, 4, 5, 6); //From OpenFOAM
cout << "sucessfully compiled and running! \
please see the exampleCode9.C file,\
 there is some command to guide you how to compile this code " << endl;
return 0;
}