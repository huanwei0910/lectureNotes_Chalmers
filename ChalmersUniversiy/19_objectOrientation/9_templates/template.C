// #include "func.H"
#include <iostream>  //Just for cout
using namespace std; // Just for cout

template <typename T>
class MyTemplatedClass
{
public:
  T x_;
  MyTemplatedClass(T);
};
template <typename T>
MyTemplatedClass<T>::MyTemplatedClass(T x)
    : x_(x)
{
  cout << "x_ = " << x_ << endl;
}

int main()
{
  MyTemplatedClass<int> myTemplatedClassIntObject(4.6);
  cout << "myTemplatedClassIntObject.x_: " << myTemplatedClassIntObject.x_ << endl;
  MyTemplatedClass<float> myTemplatedClassFloatObject(4.6);
  cout << "myTemplatedClassFloatObject.x_: " << myTemplatedClassFloatObject.x_ << endl;
  return 0;
}
