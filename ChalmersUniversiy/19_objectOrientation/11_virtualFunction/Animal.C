#include "Animal.H"

Animal::Animal() {
    cout << "Animal constructor" << endl;
}

Animal::~Animal() {
    cout << "Animal destructor" << endl;
}

void Animal::speak() const {
    cout << "Animal speaks." << endl;
}
