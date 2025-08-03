#include <iostream> //Just for cout
using namespace std; //Just for coutclass myClass
class myClass
{
private:
protected:
public:int i_=19; //Member data (underscore is OpenFOAM convention)

// protected:int i_=19; //Member data (underscore is OpenFOAM convention)


};
int main()
{
    myClass myClassObject;
    cout << "myClassObject.i_: " << myClassObject.i_ << endl;
    return 0;
}