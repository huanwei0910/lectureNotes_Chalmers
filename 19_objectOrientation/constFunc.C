#include <iostream>
class myClass {
    public:
        void write() const {
            std::cout << "Safe to call on const object!" << std::endl;
        }
    };
    
    int main() {
        const myClass obj;    // 常量对象
        obj.write();          // ✅ OK，因为 write 是 const 函数
        return 0;
    }
    