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

typedef MyTemplatedClass<int> myTemplInt;
typedef MyTemplatedClass<float> myTemplFloat;

int main()
{
  MyTemplatedClass<int> myTemplatedClassIntObject(4.6);
  cout << "myTemplatedClassIntObject.x_: " << myTemplatedClassIntObject.x_ << endl;
  MyTemplatedClass<float> myTemplatedClassFloatObject(4.6);
  cout << "myTemplatedClassFloatObject.x_: " << myTemplatedClassFloatObject.x_ << endl;

  myTemplInt myTemplatedClassIntObject2(4.6);
  cout << "myTemplatedClassIntObject.x_: " << myTemplatedClassIntObject2.x_ << endl;
  myTemplFloat myTemplatedClassFloatObject2(4.6);
  cout << "myTemplatedClassFloatObject.x_: " << myTemplatedClassFloatObject2.x_ << endl;
  
  return 0;
}
