#include <iostream> //Just for cout
using namespace std; //Just for cout
#include "myClass.H"
int main()
{
myClass myClassObject;
cout<< "myClassObject.i_: " << myClassObject.i_ << endl;
cout<< "myClassObject.j_: " << myClassObject.j_ << endl;
myClass myClassObject2;
cout<< "myClassObject2.i_: " << myClassObject2.i_ << endl;
myClassObject2.i_=30;
cout<< "myClassObject.i_: " << myClassObject.i_ << endl;
cout<< "myClassObject2.i_: " << myClassObject2.i_ << endl;
return 0;
}