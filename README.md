# Lightweight Modern C++ Win32 Wrapper

Wraps the core Win32 APIs using every modern C++ programming technique.

## Why does this project exist?

Or, why not use win32metadata?

1. Firstly, it does not provide C++ projections.
2. The projections it provides expose all the flaws of the existing APIs.
3. The APIs it provides are still fragile and unsafe.
4. It cannot provide RAII, which implies memory leaks.
5. Issues present in projections for other languages.

## Project Goals

1. Simplify using Win32 APIs and replace existing code that may leak memory.

2. Focus solely on the core Win32 APIs, i.e., those that are stable and still worthwhile.
    - Does not provide A-version APIs; the W-version is more comprehensive and efficient.
    - Does not provide COM; C++/WinRT handles that.
    - Does not provide cryptography.
    - Does not provide removed features like Alljoyn.
    - Does not provide obsolete features like GDI.
    - Does not provide superseded APIs, e.g., the original versions of functions that have an Ex variant.
    - Does not provide APIs constrained by MAX_PATH or similar limitations.
    - And all other undesirable APIs.

3. Utilize modern C++ as much as possible. It currently requires C++20. If a feature justifies an upgrade to C++23, it will be upgraded immediately (provided MSVC supports it).
    - Uses modules.
    - Uses all freestanding parts of the standard library.
    - Uses exceptions.
    - Uses concepts (and, of course, templates).
    - And other modern C++ features.

4. Fully support all meaningful code for an API once it is provided.
    - If you believe a provided API lacks meaningful functionality compared to the original API, file a BUG report explaining how it works and why it is meaningful.

## How to Build

1. A compiler with C++20 support.
2. A standard library with C++20 support.
3. Add the `include` directory to the module include path.
4. Compile all `.cpp` files under the `src` directory as modules.

## How to Use

Almost all names have been changed to lowercase (except `TRUE` and `FALSE`). Most functions have been renamed to remove duplication and unnecessary information. Nearly all constants retain their original names (except `DELETE`). Therefore, you can simply search for keywords to use them. Most functions throw `win32::error`; any exceptions will be specifically noted.

## How to Contribute

This project organizes its APIs using the partitioning provided by Win32MetaData. Before contributing, please confirm which partition the API you wish to add belongs to.

Download the [Win32MetaData Nuget package](https://www.nuget.org/packages/Microsoft.Windows.SDK.Win32Metadata/), change the extension to .zip and extract it. Download [ILSpy](https://github.com/icsharpcode/ILSpy/releases/latest), extract it, and run ILSpy.exe. Click File -> Open, and select `Windows.Win32.winmd`.