#include "func.H"
class mySubClass : public myClass {
public:
  mySubClass();
  mySubClass(int, int);
};
mySubClass::mySubClass() : myClass() {}
mySubClass::mySubClass(int i, int j) : myClass(i, j) {}

int main() {
  //   myClass myClass();
  mySubClass mySubClassObject(45, 90);
  cout << "mySubClassObject.i_: " << mySubClassObject.i_ << endl;
  cout << "mySubClassObject.j_: " << mySubClassObject.j_ << endl;
  mySubClassObject.write();
  mySubClass sobj(2, 4);
  mySubClass sobj2(2, 4);
  myClass mySum=sobj+sobj2;
    mySum.write();



  return 0;
}
