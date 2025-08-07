#include "Dog.H"

Dog::Dog() {
    cout << "Dog constructor" << endl;
}

Dog::~Dog() {
    cout << "Dog destructor" << endl;
}

void Dog::speak() const {
    cout << "Woof! I am a Dog." << endl;
}
