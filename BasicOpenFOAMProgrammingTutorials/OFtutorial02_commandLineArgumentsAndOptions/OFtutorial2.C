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
    OFtutorial2

Description

\*---------------------------------------------------------------------------*/

/*#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< nl;
    runTime.printExecutionTime(Info);

    Info<< "End\n" << endl;

    return 0;
}
    */

// 引入 OpenFOAM 的基本头文件，包含网格、求解器等大部分功能
#include "fvCFD.H"

int main(int argc, char *argv[])
{
    // === 添加程序的说明信息，用于运行程序时显示帮助内容 ===
    argList::addNote
    (
        "演示如何处理命令行参数。\n"
        "\n"
        "输入参数:\n"
        "----------------\n"
        "  someWord - 执行某些操作\n"
        "  someScalar - 执行更多操作\n"
    );

    // 禁止并行运行（不会自动分配多个 CPU），此程序设计为串行
    argList::noParallel();

    // 设置两个必需的命令行参数：
    // 第一个是字符串类型（someWord）
    argList::validArgs.append("someWord");

    // 第二个是浮点数类型（someScalar）
    argList::validArgs.append("someScalar");

    // 定义可选参数：--dict，类型为字符串（word）
    argList::addOption
    (
        "dict",             // 参数名 --dict
        "word",             // 参数类型
        "用于指定额外的字典路径（这个例子中其实没有真正使用）"
    );

    // 定义可选参数：--someSwitch，一个布尔类型的开关选项
    argList::addBoolOption
    (
        "someSwitch",       // 参数名 --someSwitch
        "用于在A与B之间切换的开关"
    );

    // 定义可选参数：--someInt，类型为整数（label）
    argList::addOption
    (
        "someInt",          // 参数名 --someInt
        "label",            // 参数类型
        "可选的整数值"
    );

    // === 实例化命令行参数列表对象 ===
    // 这一步通常在 setRootCase.H 中包含，这里直接手动写出
    Foam::argList args(argc, argv);

    // 检查当前目录是否是有效的 OpenFOAM case 根目录（含 system、constant、0 等）
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit(); // 如果不是有效目录，则退出程序
    }

    // === 从命令行中读取前两个必需参数 ===

    // 读取第一个参数（字符串），赋值给 someWord
    const word someWord = args[1];

    // 读取第二个参数（浮点数），使用 argRead<类型>() 自动转换
    const scalar someScalar = args.argRead<scalar>(2);

    // 打印读取到的参数
    Info << "获取到的参数 someWord：" << someWord
         << "，someScalar：" << someScalar << endl;

    // === 读取可选参数 ===

    // 设置一个默认的字典路径，如果用户没有传递 --dict 选项，就使用这个
    fileName dictPath("./system/defaultDict");

    // 如果命令行中使用了 --dict 选项
    if (args.optionFound("dict"))
    {
        // 尝试读取 --dict 参数值并赋值给 dictPath（如果存在）
        args.optionReadIfPresent("dict", dictPath);

        Info << "检测到字典路径覆盖参数 --dict" << endl;
    }

    // 输出字典路径
    Info << "将从该路径读取字典：" << dictPath << endl;

    // === 读取布尔开关选项 ===

    // 如果传入了 --someSwitch 选项，则返回 true，否则返回 false
    const bool someConstBool = args.optionFound("someSwitch");

    Info << "布尔开关 someSwitch 的值为：" << someConstBool << endl;

    // === 读取可选整数参数 ===

    // 定义一个整数变量 someInt，默认值为 0
    label someInt(0);

    // 如果传入了 --someInt 参数，就读取其值
    args.optionReadIfPresent("someInt", someInt);

    // 打印整数值
    Info << "整数参数 someInt 的值为：" << someInt << endl;

    // 程序结束
    Info << "程序结束\n" << endl;

    return 0;
}

// ************************************************************************* //
