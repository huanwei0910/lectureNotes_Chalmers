#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
using namespace std;

class Animal {
public:
    Animal();
    virtual ~Animal();  // 必須虛擬析構
    virtual void speak() const;
};

#endif
