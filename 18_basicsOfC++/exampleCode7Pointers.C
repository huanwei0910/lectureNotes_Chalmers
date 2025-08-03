#include <iostream>
#include <cmath>  // for sqrt

using namespace std;

// 一个简单的三维向量类
class Vector3D {
public:
    double x, y, z;

    // 构造函数
    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    // 成员函数：返回模长
    double magnitude() {
        return sqrt(x*x + y*y + z*z);
    }
};

int main() {
    // 普通对象方式
    Vector3D v1(3.0, 4.0, 0.0);
    cout << "v1.magnitude() = " << v1.magnitude() << endl;

    // 指针方式
    Vector3D* v2 = new Vector3D(1.0, 2.0, 2.0);
    cout << "v2->magnitude() = " << v2->magnitude() << endl;

    // 释放内存
    delete v2;

    return 0;
}
