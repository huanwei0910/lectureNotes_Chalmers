#include <iostream> //Just for cout
using namespace std; //Just for coutclass myClass
class myClass
{
    private:
    protected:
    public:
        int i_; //Member data (underscore is OpenFOAM convention)
        float j_;
        static int m_;
        // myClass();//在类声明中显式声明构造函数和析构函数。
        myClass():i_(10),j_(10.5)
        {
            cout<< "i_ = running" << i_ << endl;
        }
        ~myClass(); 
        void write();
        
    // protected:int i_=19; //Member data (underscore is OpenFOAM convention)

};

myClass::~myClass()
{
    cout<< "finito = "<< endl; 
}

void myClass::write()
{
cout<< "My member data i_ = " << i_ << endl;
cout<< "My member data j_ = " << j_ << endl;
}

int myClass::m_ = 9;
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
    cout<< "============================================" << endl;

    myClass& myClassObjectRef = myClassObject;
    cout<< "myClassObjectRef.i_: " << myClassObjectRef.i_ << endl;
    myClassObject.i_=42;
    cout<< "myClassObject.i_: " << myClassObject.i_ << endl;
    cout<< "myClassObjectRef.i_: " << myClassObjectRef.i_ << endl;
    myClassObjectRef.i_=43;
    cout<< "myClassObject.i_: " << myClassObject.i_ << endl;
    cout<< "myClassObjectRef.i_: " << myClassObjectRef.i_ << endl;
    cout<< "============================================" << endl;

    myClass* p=& myClassObjectRef;
    p->i_=1000;
    cout<< "myClassObject.i_: " << myClassObject.i_ << endl;
    cout<< "myClassObject p->i: " << p->i_ << endl;

    cout<< "============================================" << endl;

    myClass& myClassObjectRef2 = myClassObject2;
    cout<< "myClassObject.m_: " << myClassObject.m_ << endl;
    cout<< "myClassObject2.m_: " << myClassObject2.m_ << endl;
    myClass::m_=30; //Or: myClassObject2.m_=30;
    cout<< "myClassObject.m_: " << myClassObject.m_ << endl;
    cout<< "myClassObject2.m_: " << myClassObject2.m_ << endl;
    cout<< "============================================" << endl;

    myClassObject.write();
    myClassObject2.write();
    p->write(); //Use "->" for pointers!
    cout<< "============================================" << endl;
    cout<< "============================================" << endl;




    return 0;
}