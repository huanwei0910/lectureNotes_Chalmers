#include "Cat.H"

Cat::Cat() {
    cout << "Cat constructor" << endl;
}

Cat::~Cat() {
    cout << "Cat destructor" << endl;
}

void Cat::speak() const {
    cout << "Meow! I am a Cat." << endl;
}
