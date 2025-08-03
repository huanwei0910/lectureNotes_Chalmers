#include <iostream>
using namespace std;

namespace test1 { double average (double&, double&, int nvalues=2); }
namespace test2 { double average (double&, double&, int nvalues=2); }


using namespace test1;


int main()
{
double d1=2.1;
double d2=4;
cout << "Modified average: " << test2::average(d1,d2) << endl;
cout << "Half modified average: " << test2::average(d1,d2,4) << endl;
cout << "d1: " << d1 << ", d2: " << d2 << endl;
return 0;}

namespace test1
{
double average (double& x1, double& x2, int nvalues)
{x1 = 8; return (x1+x2)/nvalues;}
}
namespace test2
{
double average (double& x1, double& x2, int nvalues)
{x1 = 10; return (x1+x2)/(2*nvalues);}
}