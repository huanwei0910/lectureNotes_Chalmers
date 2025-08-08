#include <iostream> //Just for cout
using namespace std; //Just for cout

class myClass
{
    protected:
    private:
        int k_=7;
        const int l_=17;

    public:
        int i_; //Member data (underscore is OpenFOAM convention)
        float j_;
    // myClass();
    // ~myClass();

     int& k();
     const int& l() const;

};