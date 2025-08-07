// File: YourClass.cpp
#include "YourClass.H"
#include "MyClass.H"
#include <iostream>

void YourClass::doSomethingElse(MyClass* ptr) {
    std::cout << "YourClass is doing something else with MyClass pointer." << std::endl;
}
