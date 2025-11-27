# 轻量的现代 C++ Win32 包装

使用任何现代 C++ 编程技术包装 Win32 核心 API。

## 为什么该项目存在？

或者说，为什么不用 win32metadata？

1. 首先，它不提供 C++ 投影
2. 它提供的投影暴露了所有现有 API 的缺陷
3. 它提供的 API 仍然是脆弱和 unsafe 的
4. 它不能提供 RAII，这意味着内存泄漏
5. 其他语言的投影中存在的问题

## 该项目的目标

1. 轻松使用 Win32API，并且替换现有的会泄漏内存的代码

2. 只关心核心 Win32 API，即那些稳定的以及仍然值得使用的
   - 不提供 A 版本 API，W 版本更全面并且更有效
   - 不提供 COM，C++/WinRT 做这件事
   - 不提供加密
   - 不提供过时的功能，如 GDI
   - 不提供已经删除的功能，如 Alljoyn
   - 不提供被替代的 API，例如几乎所有存在 Ex 变体的函数的原始版本
   - 不提供受到 MAX_PATH 限制或者类似限制的 API
   - 其他所有不好的 API

3. 尽可能使用现代 C++，目前它需要 C++20，如果哪个特性值得升级到 C++23，会立即升级（如果 MSVC 支持）
   — 使用模块
   - 使用标准库的所有 freestanding 部分
   - 使用异常
   - 使用概念（当然，模板）
   - 以及其他 C++ 现代特性

4. 一旦提供了该 API，就支持该 API 的所有有意义代码
   - 如果你认为某个已经提供的 API 相比于原始 API 缺少有意义的功能，发送 BUG 报告并解释它如何工作以及为什么有意义

## 如何构建

1. 支持 C++20 的编译器
2. 支持 C++20 的标准库
3. 将 include 目录作为模块的包含路径
4. 将 src 目录下的所有.cpp 文件编译为模块

## 如何使用

几乎所有名字都被改写为小写（除了 TRUE 和 FALSE），大部分函数都重新命名以去除重复和无用信息，几乎所有常量都保持了原有名字（除了 DELETE）。因此只需要搜索关键字即可使用。大部分函数都抛出 win32::error，如有例外会特别说明。

## 如何贡献

本项目的 API 组织方式使用 Win32MetaData 中提供的划分方式。贡献前请确认你要添加的 API 处在哪个分区中。

下载 [Win32MetaData Nuget 包](https://www.nuget.org/packages/Microsoft.Windows.SDK.Win32Metadata/)，修改扩展名为 zip 并解压缩；下载 [ILSpy](https://github.com/icsharpcode/ILSpy/releases/latest)，解压缩并运行 ILSpy.exe，点击左上角文件，打开，选择 Windows.Win32.winmd。
