#include "func.H"
myClass::myClass(){}
myClass::myClass(int a, float b)
:
i_(a),
j_(b)
{
    cout<< "i_ = " << i_ << endl;
    cout<< "j_ = " << j_ << endl;
}

int& myClass::k()
{
    return k_;
}

const int& myClass::l() const
{
    return l_;
}

int main()
{
    myClass obj0=myClass();

    myClass obj=myClass(100,30.14);

    cout<< "i_0: " << obj0.i_<< endl;
    cout<< "j_0: " << obj0.j_<< endl;

    cout<< "i_: " << obj.i_<< endl;
    cout<< "j_: " << obj.j_<< endl;

    // l=20;//expression must be a modifiable lvalue, so here the compile is failed

    return 0;
}

