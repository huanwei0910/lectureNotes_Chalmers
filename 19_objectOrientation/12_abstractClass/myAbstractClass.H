#ifndef MY_ABSTRACT_CLASS_H
#define MY_ABSTRACT_CLASS_H

class myAbstractClass
{
public:
    virtual ~myAbstractClass() {}
    virtual void write() const = 0; // 纯虚函数
};

#endif
