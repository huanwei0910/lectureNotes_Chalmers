
/*
容器类（Container classes）简介

    容器类的定义：
    容器类用来存放和管理数据集合。可以理解成特定类型对象的列表。
    容器类本质上是一种模板（template），因此它可以用来存放任何类型的对象。

    成员函数：算法（algorithms）
    容器类自带一些成员函数，这些函数叫做算法，比如搜索、排序等操作。

    迭代器（iterators）
    容器类和算法通常都会用到迭代器，迭代器是一种类似指针的对象，用来遍历容器中的元素。

    OpenFOAM里的容器类

        位置：$FOAM_SRC/OpenFOAM/containers

        例如：Lists、UList 等类

    forAll宏定义
    OpenFOAM定义了一个方便遍历列表的宏 forAll，在 UList.H 文件里：

#define forAll(list, i) \
    for (Foam::label i=0; i<(list).size(); i++)


总结：

容器类是管理数据集合的模板类。

它们有算法成员函数用于操作数据。

迭代器类似指针，是遍历容器元素的工具。

OpenFOAM提供了 forAll 宏方便遍历容器。
*/
#include <iostream>
#include <vector>

// 模拟 OpenFOAM 的 forAll 宏
#define forAll(list, i) for (size_t i = 0; i < (list).size(); ++i)

int main() {
    // 创建一个简单的整型容器（向量）
    std::vector<int> myList = {10, 20, 30, 40, 50};

    // 使用 forAll 宏遍历容器元素
    forAll(myList, i) {
        std::cout << "Element " << i << " = " << myList[i] << std::endl;
    }
    std::cout << "=======================================" << std::endl;
      // 使用 for 历容器元素
    for (size_t i = 0; i < myList.size(); ++i){
        std::cout << "Element " << i << " = " << myList[i] << std::endl;
    }


    return 0;
}
