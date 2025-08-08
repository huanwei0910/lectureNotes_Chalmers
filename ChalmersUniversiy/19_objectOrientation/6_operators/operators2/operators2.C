#include "func.H"

inline myClass operator+(const myClass& mC1, const myClass& mC2)
{
    return myClass(mC1.i_ + mC2.i_, mC1.j_ + mC2.j_);
}

int main()
{
    myClass a(1, 2);
    myClass b(3, 4);
    myClass c = a + b;

    c.write();  // Output: (4, 6)

    return 0;
}

