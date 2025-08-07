#ifndef DOG_H
#define DOG_H

#include "Animal.H"

class Dog : public Animal {
public:
    Dog();
    ~Dog();
    void speak() const override;
};

#endif
