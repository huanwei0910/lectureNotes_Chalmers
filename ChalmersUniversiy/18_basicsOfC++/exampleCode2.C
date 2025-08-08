#include <iostream>
#include <cmath>
using namespace std;
int main()
{
float myFloat;
cout << "Please type a float!" << endl;
cin >> myFloat;
cout << "sin(" << myFloat << ") = " << sin(myFloat) << endl;
if (myFloat < 5.5){cout << myFloat << " is less than 5.5" << endl;} else
{cout << myFloat << " is not less than 5.5" << endl;};
for ( int i=0; i<myFloat; i++ ) {cout << "For-looping: " << i << endl;}
int j=0;
while (j<myFloat) {cout << "While-looping: " << j << endl; j++;}
return 0;
}
