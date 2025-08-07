#ifndef CAT_H
#define CAT_H

#include "Animal.H"

class Cat : public Animal {
public:
    Cat();
    ~Cat();
    void speak() const override;
};

#endif
