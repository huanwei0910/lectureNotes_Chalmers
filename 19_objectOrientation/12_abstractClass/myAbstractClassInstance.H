#ifndef MY_ABSTRACT_CLASS_INSTANCE_H
#define MY_ABSTRACT_CLASS_INSTANCE_H

#include "myAbstractClass.H"
#include <iostream>

class myAbstractClassInstance : public myAbstractClass
{
public:
    void write() const override;
};

#endif
