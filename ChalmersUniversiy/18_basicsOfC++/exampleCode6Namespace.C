#include <iostream>
using namespace std;

namespace test1 { void myPrint (); }
namespace test2 { void myPrint (); }


// using namespace test1;


int main()
{
    test1::myPrint ();
    test2::myPrint ();

    return 0;    
}

namespace test1
{
    void myPrint ()
        {
            cout << "test1 is runing under namespace test1 : " << endl;
            return ;
        }
}

namespace test2
{
    void myPrint ()
        {
            cout << "test2 is runing under namespace test2 : " << endl;
            return ;
        }
}
