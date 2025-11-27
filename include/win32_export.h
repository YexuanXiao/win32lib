#ifndef WIN32_MACROS_H
#define WIN32_MACROS_H

#define DLL __declspec(dllimport)

#define WIN32_ERROR DLL [[nodiscard]] win32::error __stdcall
#define HANDLE DLL [[nodiscard]] void* __stdcall
#define BOOL DLL [[nodiscard]] win32::boolean __stdcall
#define VOID DLL void __stdcall
#define WAIT_EVENT DLL [[nodiscard]] win32::wait_event __stdcall

using handle = const void*;
using phandle = void **;
using dword = unsigned long;
using pdword = dword*;
using wcstr = const wchar_t *;
using pobj = const void*;
using boolean = unsigned int;

#endif