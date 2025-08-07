// File: MyClass.h
#ifndef MYCLASS_H
#define MYCLASS_H

class YourClass;  // 前置声明，告诉编译器YourClass存在

class MyClass {
public:
    void doSomething(YourClass* ptr);  // 使用YourClass指针，不需要完整定义
};

#endif
