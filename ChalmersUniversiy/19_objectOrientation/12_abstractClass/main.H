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
🧩 编译指令（终端里）：

g++ main.C myAbstractClassInstance.C -o abstractDemo
./abstractDemo
*/