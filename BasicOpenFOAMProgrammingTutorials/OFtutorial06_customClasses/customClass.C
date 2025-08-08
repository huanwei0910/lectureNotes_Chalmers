// #include "customClass.H"

// namespace Foam
// {

// customClass::customClass()
// :
//     myInt_(0) // 默认初始化为 0
// {}

// customClass::~customClass() = default;

// label customClass::basicFunction() const
// {
//     // 这里做点简单输出，返回当前内部值
//     Info << "customClass::basicFunction() called. myInt_ = " << myInt_ << nl << endl;
//     return myInt_;
// }

// void customClass::meshOpFunction(const fvMesh& mesh)
// {
//     // 示例：把内部值设为网格 cell 数（也可改为 gSum(mesh.V()) 等更复杂操作）
//     myInt_ = static_cast<label>(mesh.C().size());

//     Info << "customClass::meshOpFunction(): number of cells = "
//          << myInt_ << nl << endl;
// }

// } // namespace Foam

#include "customClass.H"

customClass::customClass()
{
    myInt_= 0;
}

customClass::~customClass()
{}

label customClass::basicFunction() const
{
    Info << "Calling customClass::basicFunction()" << endl;
    return myInt_*2;
}

void customClass::meshOpFunction(fvMesh& mesh)
{
    Info << "Custom class got a mesh with " << mesh.C().size() << " cells" << endl;
    myInt_ = mesh.C().size();
}