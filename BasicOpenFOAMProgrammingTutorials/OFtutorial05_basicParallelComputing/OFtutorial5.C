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
    OFtutorial5

Description

\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
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

\*---------------------------------------------------------------------------*/


#include "fvCFD.H"  // OpenFOAM 核心头文件，包含有限体积网格、字段操作、并行通信等工具
#include "processorPolyPatch.H"

int main(int argc, char *argv[])
{
    // 初始化运行路径，例如从 -case 指定目录中读取系统设置
    #include "setRootCase.H"

    // 创建时间控制器 runTime（读取 system/controlDict）
    #include "createTime.H"

    // 创建计算网格 mesh（读取 constant/polyMesh）
    #include "createMesh.H"

    // 每个处理器输出自身信息，包括处理器编号和负责的 cell 数量
    // Pout 是所有处理器都可写入的输出流（区别于 Info 只主进程输出）
    Pout << "Hello from processor " << Pstream::myProcNo()
         << "! I am working on " << mesh.C().size() << " cells" << endl;

    // === 每个处理器计算自身子域体积 ===
    scalar meshVolume(0.0);
    forAll(mesh.V(), cellI)
        meshVolume += mesh.V()[cellI];

    Pout << "Mesh volume on this processor: " << meshVolume << endl;

    // 使用 reduce 将所有处理器的 meshVolume 求和（归约）
    reduce(meshVolume, sumOp<scalar>());

    // 仅主进程输出全网格体积和总 cell 数
    Info << "Total mesh volume on all processors: " << meshVolume
         << " over " << returnReduce(mesh.C().size(), sumOp<label>()) << " cells" << endl;

    // 使用 scatter 将 meshVolume 广播给所有处理器
    Pstream::scatter(meshVolume);
    Pout << "Mesh volume on this processor is now " << meshVolume << endl;

    // === 收集各处理器面数和 patch 数量 ===
    List<label> nInternalFaces(Pstream::nProcs()), nBoundaries(Pstream::nProcs());

    // 本处理器写入自身数据
    nInternalFaces[Pstream::myProcNo()] = mesh.Cf().size();         // 内部面数
    nBoundaries[Pstream::myProcNo()] = mesh.boundary().size();      // 边界 patch 数

    // 汇总所有处理器的数据到主进程（gather）
    Pstream::gatherList(nInternalFaces);
    Pstream::gatherList(nBoundaries);

    // 可选：将列表广播回所有处理器
    Pstream::scatterList(nInternalFaces);
    Pstream::scatterList(nBoundaries);

    // 主处理器输出所有处理器的信息
    if (Pstream::master())
    {
        forAll(nInternalFaces, i)
            Info << "Processor " << i << " has " << nInternalFaces[i]
                 << " internal faces and " << nBoundaries[i] << " boundary patches" << endl;
    }

    // === 输出当前处理器所有 patch 的名称 ===
    forAll(mesh.boundary(), patchI)
        Pout << "Patch " << patchI << " named " << mesh.boundary()[patchI].name() << endl;

    // === 检查并输出哪些 patch 是处理器间边界（processor boundary）===
    forAll(mesh.boundary(), patchI)
    {
        const polyPatch& pp = mesh.boundaryMesh()[patchI];
        if (isA<processorPolyPatch>(pp))
            Pout << "Patch " << patchI << " named " << mesh.boundary()[patchI].name()
                 << " is definitely a processor boundary!" << endl;
    }

    // === 引入 createFields.H 文件，定义 p、U 字段 ===
    // 一般在这个文件中定义 volScalarField p 和 volVectorField U
    #include "createFields.H"

    // === 构造距离场 r = |x - x0|，x0 是参考点 ===
    const dimensionedVector originVector("x0", dimLength, vector(0.05, 0.05, 0.005));
    volScalarField r(mag(mesh.C() - originVector));

    // 计算最大距离 rFarCell，并使用 maxOp 并行归约
    const scalar rFarCell = returnReduce(max(r).value(), maxOp<scalar>());

    // 定义频率 f = 1 Hz
    scalar f = 1.;

    Info << "\nStarting time loop\n" << endl;

    // === 时间推进主循环 ===
    while (runTime.loop())
    {
        Info << "Time = " << runTime.timeName() << nl << endl;

        // === 构造随时间正弦变化、随距离衰减的压力场 p ===
        // p(x, t) = sin(2πft) / (r/rFarCell + ε)，再乘以具有压力单位的标量
        p = Foam::sin(2. * constant::mathematical::pi * f * runTime.time().value())
            / (r / rFarCell + dimensionedScalar("small", dimLength, 1e-12))
            * dimensionedScalar("tmp", dimensionSet(0, 3, -2, 0, 0), 1.);

        // 必须更新并行边界的 patch 值，防止求梯度时出错
        p.correctBoundaryConditions();

        // === 根据 p 计算速度场 U = grad(p) * Δt ===
        // Δt 为 1 秒（仅用于演示）
        U = fvc::grad(p) * dimensionedScalar("tmp", dimTime, 1.0);

        // 写出字段数据到当前时间目录
        runTime.write();
    }

    Info << "End\n" << endl;
    return 0;
}


// ************************************************************************* //