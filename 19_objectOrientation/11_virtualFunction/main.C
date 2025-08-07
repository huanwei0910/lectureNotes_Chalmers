#include "Animal.H"
#include "Dog.H"
#include "Cat.H"

int main() {
    Animal* a1 = new Dog();
    Animal* a2 = new Cat();

    a1->speak();  // 調用 Dog 的 speak
    a2->speak();  // 調用 Cat 的 speak

    delete a1;    // 正確析構 Dog + Animal
    delete a2;    // 正確析構 Cat + Animal
    cout << "注意看main.C中的文字說寧，能夠更好得了理解虛函數" << endl;


    return 0;
}
/*
1.每個 .h 頭文件加 #ifndef 是為了防止重複包含（叫做 header guard）

2. 使用 override 是 C++11 以後的推薦寫法，防止拼錯函數名

3. 保證基類析構函數是 virtual，否則子類釋放不完全會造成資源洩漏

4. 
 什麼是虛擬成員函數？

在 C++ 中：

    虛擬成員函數（virtual function）是用來支持**動態綁定（dynamic binding）**的。

    也叫做運行時多態：
    調用哪個版本的函數，不是編譯時決定，而是執行時根據對象的實際類型來決定。

這就是為什麼：
✅ 一個指向父類的指針，可以在運行時調用子類覆蓋後的版本。

5. 
父類 Animal 有虛擬函數 speak()

子類 Dog 和 Cat 覆蓋 speak()

用父類指針調用子類函數（動態綁定）

析構函數也設為 virtual，確保正確析構


| 功能         | 說明                          |
| ---------- | --------------------------- |
| `virtual`  | 用於成員函數，實現多態，根據實際對象調用正確函數    |
| `override` | 子類明確表示重寫父類虛擬函數（C++11 之後推薦）  |
| 虛擬析構函數     | 用來保證 `delete` 父類指針時正確調用子類析構 |
| 指針調用虛擬函數   | 實現動態綁定（運行時決定調用哪個版本的函數）      |


*/
/*
 編譯指令
 g++ -std=c++11 main.cpp Animal.cpp Dog.cpp Cat.cpp -o myApp
./myApp

*/