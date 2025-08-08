/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2025 AUTHOR,AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    OFtutorial3

Description

\*---------------------------------------------------------------------------*/

// #include "fvCFD.H"

// // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// int main(int argc, char *argv[])
// {
//     #include "setRootCase.H"
//     #include "createTime.H"

//     // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//     Info<< nl;
//     runTime.printExecutionTime(Info);

//     Info<< "End\n" << endl;

//     return 0;
// }


#include "fvCFD.H"  // OpenFOAM 核心头文件，包含处理 fvMesh 和字段的基础类

int main(int argc, char *argv[])
{
    #include "setRootCase.H"  // 设置案例路径（支持 -case 等命令行选项）

    // 创建时间控制系统（对象名为 runTime）和 fvMesh 网格（对象名为 mesh）
    #include "createTime.H"
    #include "createMesh.H"

    // runTime 和 mesh 是对象，拥有诸如 .timeName(), .C(), .Cf() 等成员函数
    // mesh.C() 返回每个单元格（cell）的中心点坐标向量
    // mesh.Cf() 返回每个内部面的中心点坐标向量
    // mesh.C().size() 表示整个网格中的 cell 数量
    Info << "Hello there, the most recent time folder found is " << runTime.timeName() << nl
         << "The mesh has " << mesh.C().size() << " cells and " << mesh.Cf().size()
         << " internal faces in it. Wubalubadubdub!" << nl << endl;

    // 使用标准 C++ 循环遍历每个 cell，并打印每隔 20 个 cell 的中心点坐标
    for (label cellI = 0; cellI < mesh.C().size(); cellI++)
        if (cellI % 20 == 0) // 每隔 20 个 cell 打印一次，避免输出过多
            Info << "Cell " << cellI << " with centre at " << mesh.C()[cellI] << endl;
    Info << endl;

    // 遍历所有内部面（internal faces）
    // mesh.owner() 和 mesh.neighbour() 提供面所属的两个 cell 编号
    for (label faceI = 0; faceI < mesh.owner().size(); faceI++)
        if (faceI % 40 == 0)
            Info << "Internal face " << faceI << " with centre at " << mesh.Cf()[faceI]
                 << " with owner cell " << mesh.owner()[faceI]
                 << " and neighbour " << mesh.neighbour()[faceI] << endl;
    Info << endl;

    // 通过 boundaryMesh 可以访问边界面（patch）
    // mesh.boundary() 返回所有 patch 的列表
    // mesh.boundary()[i] 表示第 i 个 patch，可访问其名称、面数、起始面编号等
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch " << patchI << ": " << mesh.boundary()[patchI].name() << " with "
             << mesh.boundary()[patchI].Cf().size() << " faces. Starts at total face "
             << mesh.boundary()[patchI].start() << endl;
    Info << endl;

    // 访问边界 patch 中的面，可以获取相邻 cell、法向量和面积
    label patchFaceI(0);
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch " << patchI << " has its face " << patchFaceI << " adjacent to cell "
             << mesh.boundary()[patchI].patch().faceCells()[patchFaceI]
             << ". It has normal vector " << mesh.boundary()[patchI].Sf()[patchFaceI]
             << " and surface area " << mag(mesh.boundary()[patchI].Sf()[patchFaceI])
             << endl;
    Info << endl;

    // 对于内部面，也可以直接通过 mesh.Sf() 获取法向量，mesh.magSf() 获取面积
    // 内部面法向量方向从 owner 指向 neighbour；边界面法向量指向域外（邻居为虚拟单元）

    // 下面获取更底层的 mesh 构造信息：faces、points、faceCentres
    const faceList& fcs = mesh.faces();          // 所有面（包括内部面和边界面）
    const List<point>& pts = mesh.points();      // 所有顶点坐标
    const List<point>& cents = mesh.faceCentres(); // 所有面的中心点坐标

    // 遍历所有面（包括内部面和边界面），每隔 80 个面打印一次详细信息
    forAll(fcs, faceI)
        if (faceI % 80 == 0)
        {
            if (faceI < mesh.Cf().size())
                Info << "Internal face "; // 内部面
            else
            {
                forAll(mesh.boundary(), patchI)
                    if ((mesh.boundary()[patchI].start() <= faceI) &&
                        (faceI < mesh.boundary()[patchI].start() + mesh.boundary()[patchI].Cf().size()))
                    {
                        Info << "Face on patch " << patchI << ", faceI "; // 边界面
                        break;
                    }
            }

            // 打印该面中心点、顶点数量及其坐标
            Info << faceI << " with centre at " << cents[faceI]
                 << " has " << fcs[faceI].size() << " vertices:";
            forAll(fcs[faceI], vertexI)
                Info << " " << pts[fcs[faceI][vertexI]]; // 打印每个顶点的坐标
            Info << endl;
        }
    Info << endl;

    // 检查某个边界 patch 是否是 "empty" 类型（通常用于 2D 模拟的前后面）
    label patchID(0);
    const polyPatch& pp = mesh.boundaryMesh()[patchID];
    if (isA<emptyPolyPatch>(pp))
    {
        // 如果是 empty 类型，这段话会被打印
        Info << "You will not see this." << endl;
    }

    // 还可以通过 patch 的名称获取其编号，这在读取字典文件中特定 patch 时非常有用
    word patchName("movingWall");  // 假设我们想获取名为 "movingWall" 的 patch
    patchID = mesh.boundaryMesh().findPatchID(patchName); // 查找其 ID
    Info << "Retrieved patch " << patchName << " at index " << patchID << " using its name only." << nl << endl;

    Info << "End\n" << endl;

    return 0;  // 程序正常退出
}


    
// ************************************************************************* //
