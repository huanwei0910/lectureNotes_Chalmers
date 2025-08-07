#include "func.H"


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
    myClass myClassObject;
    int& k = myClassObject.k();   // 获取引用
    cout << "k: " << k << endl;

    k = 5;  // 修改值

    cout << "k: " << k << endl;
    cout << "myClassObject.k(): " << myClassObject.k() << endl;

    const int& l=myClassObject.l();
    cout<< "l: " << l << endl;
    // l=20;//expression must be a modifiable lvalue, so here the compile is failed

    return 0;
}

