export module bizwen.export32.registry;
export import bizwen.win32.foundation;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    WIN32_ERROR RegOpenKeyExW(handle hKey, wcstr lpSubKey, dword ulOptions, dword samDesired,
                              phandle phkResult);
    WIN32_ERROR RegCreateKeyExW(handle hKey, wcstr lpSubKey, dword Reserved, wcstr wclpClass,
                                dword dwOptions, dword samDesired, pobj lpSecurityAttributes,
                                phandle phkResult, pdword dwDisposition);
    WIN32_ERROR RegCloseKey(handle hKey);
    WIN32_ERROR RegSetValueExW(handle hKey, wcstr lpValueName, dword Reserved,
                                                        dword dwType, const void *lpData,
                                                        dword cbData);
    WIN32_ERROR RegGetValueW(handle hkey, wcstr lpSubKey, wcstr lpValue, dword dwFlags,
                             pdword pdwType, const void*pvData, pdword pcbData);
    WIN32_ERROR RegDeleteKeyExW(handle hKey, wcstr lpSubKey, dword Reserved, dword dwFlags);
    // no W postfix
    WIN32_ERROR RegRenameKey(handle hKey, wcstr lpSubKey, wcstr lpNewKeyName);
    WIN32_ERROR RegDeleteValueW(handle hKey, wcstr lpValueName);
    WIN32_ERROR RegDeleteTreeW(handle hKey, wcstr lpSubKey);
    WIN32_ERROR RegDeleteKeyValueW(handle hKey, wcstr lpSubKey, wcstr lpValueName);
    WIN32_ERROR RegCopyTreeW(handle hKeySrc, wcstr lpSubKey, handle hKeyDest);
    // todo: QueryInfoKeyExW, OpenUserClassesRoot, NotifyChangeKeyValue, EnumValueW, EnumKeyExW
    // todo?: EnableReflectionKey, DisableReflectionKey, QueryReflectionKey
}
} // namespace export32