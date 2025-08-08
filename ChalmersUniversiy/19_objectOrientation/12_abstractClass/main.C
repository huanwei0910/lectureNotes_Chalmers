#include "myAbstractClass.H"
#include "myAbstractClassInstance.H"

int main()
{
    // myAbstractClass obj; // ❌ 错误：不能创建抽象类对象

    myAbstractClass* objPtr = new myAbstractClassInstance();
    objPtr->write();

    delete objPtr;
    return 0;
}


/*
抽象类是 C++ 中一种不能直接创建对象的类。其作用主要是作为「基类」让其他类继承，并强制派生类实现某些函数。
关键点：

    如果一个类中至少有一个纯虚函数（= 0），这个类就是抽象类。

    抽象类不能直接创建对象。

    子类必须实现纯虚函数，否则自己也会变成抽象类。

    多用于「接口」或「模板式设计」。
     

总结你应该掌握的点：
概念	说明
抽象类	至少含一个纯虚函数，不能实例化
纯虚函数	virtual void func() = 0; 子类必须实现
多文件结构	用 .H 定义接口结构，用 .C 实现函数逻辑
多态调用	用基类指针调用派生类对象时，会自动执行重写的版本


*/