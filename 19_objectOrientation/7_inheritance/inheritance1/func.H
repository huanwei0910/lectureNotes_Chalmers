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
    myClass(){}
    myClass(int i, int j) : i_(i), j_(j) {}
    void write() const {
        std::cout << "(" << i_ << ", " << j_ << ")\n";
    }
     

};
inline myClass operator+(const myClass& mC1, const myClass& mC2)
{
return myClass
(
mC1.i_ + mC2.i_,
mC1.j_ + mC2.j_
);
}