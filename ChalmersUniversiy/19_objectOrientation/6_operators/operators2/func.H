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
    myClass(int i, int j) : i_(i), j_(j) {}

    //     // metohd1 Member version of operator+
    // myClass operator+(const myClass& other) const {
    //     return myClass(i_ + other.i_, j_ + other.j_);
    // }

    void write() const {
        std::cout << "(" << i_ << ", " << j_ << ")\n";
    }
     
};

//         // method 2Inline non-member operator+
// inline myClass operator+(const myClass& a, const myClass& b)
// {
//     return myClass(a.i_ + b.i_, a.j_ + b.j_);
// }

        // method 3: Inline non-member operator+
inline myClass operator+(const myClass&, const myClass&);