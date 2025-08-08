// File: MyClass.cpp
#include "MyClass.H"
#include "YourClass.H"
#include <iostream>

void MyClass::doSomething(YourClass* ptr) {
    std::cout << "MyClass is doing something with YourClass pointer." << std::endl;
}
