#include "myClass.H"
#include <iostream>  //Just for cout
using namespace std; // Just for cout
myClass::myClass()
    : i_(20),
      j_(21.5)
{
    cout << "i_ = " << i_ << endl;
}
myClass::~myClass()
{
}