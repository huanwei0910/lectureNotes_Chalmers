// File: YourClass.h
#ifndef YOURCLASS_H
#define YOURCLASS_H

class MyClass;  // 前置声明，告诉编译器MyClass存在

class YourClass {
public:
    void doSomethingElse(MyClass* ptr);  // 使用MyClass指针
};

#endif
