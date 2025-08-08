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
    OFtutorial4

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"  // OpenFOAM 中最常用的头文件，包含了网格、字段操作等核心功能

// 函数声明：根据时间 t、空间位置 x、参考点 x0 和缩放比例 scale 计算压力值（标量）
scalar calculatePressure(scalar t, vector x, vector x0, scalar scale);

int main(int argc, char *argv[])
{
    #include "setRootCase.H"   // 设置运行路径，支持 -case、-parallel 等命令行选项
    #include "createTime.H"    // 创建时间控制器 runTime（读取 system/controlDict）
    #include "createMesh.H"    // 创建网格对象 mesh，读取 constant/polyMesh 下的网格数据

    // 读取 transportProperties 字典（位于 constant 文件夹中）
    Info << "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",        // 字典名
            runTime.constant(),           // 所在目录为 constant
            mesh,                         // 所属网格
            IOobject::MUST_READ_IF_MODIFIED, // 如果文件被修改则重新读取
            IOobject::NO_WRITE            // 只读，不写入
        )
    );

    // 读取 kinematic viscosity（动力粘度）变量 nu
    dimensionedScalar nu
    (
        "nu",                // 名称
        dimViscosity,        // 物理量维度，OpenFOAM 中预定义的粘度维度：[L^2/T]
        transportProperties.lookup("nu") // 从 transportProperties 中提取实际值
    );

    // 从时间目录中读取标量场 p（压力）
    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",                    // 字段名
            runTime.timeName(),    // 当前时间步目录
            mesh,
            IOobject::MUST_READ,   // 必须存在，否则报错
            IOobject::AUTO_WRITE   // 允许自动写入（用于 runTime.write()）
        ),
        mesh // 使用网格构造字段
    );

    // 从时间目录中读取矢量场 U（速度）
    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    // 定义一个固定参考点，用作“压力中心”
    const vector originVector(0.05, 0.05, 0.005);

    // 计算所有 cell 中距 originVector 最远的一个点的距离（用于归一化半径）
    const scalar rFarCell = max(
        mag(dimensionedVector("x0", dimLength, originVector) - mesh.C())  // 所有 cell 到 x0 的距离
    ).value(); // 转换为无单位的标量（scalar）

    Info<< "\nStarting time loop\n" << endl;

    // 时间推进循环（控制条件由 controlDict 中的 endTime、deltaT 等设置）
    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        // 遍历所有 cell，逐个计算压力值
        for (label cellI=0; cellI<mesh.C().size(); cellI++)
        {
            // 对每个 cell，根据当前时间和位置计算压力值，并赋值给 p
            p[cellI] = calculatePressure(runTime.time().value(), mesh.C()[cellI], originVector, rFarCell);
        }

        // 计算 p 的梯度作为速度场 U（U = grad(p) * Δt），只是演示用途
        U = fvc::grad(p) * dimensionedScalar("tmp", dimTime, 1.);

        // 根据 controlDict 设置，写出字段数据到对应时间目录
        runTime.write();
    }

    Info << "Finished! Best to visualise the results by plotting p iso-contours with range (-10,10) and applying a glyph filter to the U field in Paraview." << endl;

    Info<< "End\n" << endl;

    return 0; // 正常退出
}

// 自定义函数的定义体：返回一个基于距离和正弦时间变化的压力值
scalar calculatePressure(scalar t, vector x, vector x0, scalar scale)
{
    // 归一化距离（r = |x - x0| / scale），范围大致为 [0,1]
    scalar r = mag(x - x0) / scale;

    // r 的倒数并加微小值避免除以零（rR → 越靠近 x0 越大）
    scalar rR = 1. / (r + 1e-12);

    // 定义时间频率 f = 1 Hz
    scalar f = 1.;

    // 返回一个时间上正弦变化、空间上以 x0 为中心衰减的压力值
    return Foam::sin(2. * Foam::constant::mathematical::pi * f * t) * rR;
}



// ************************************************************************* //
