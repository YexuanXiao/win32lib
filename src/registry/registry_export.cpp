export module bizwen.export32.registry;
export import bizwen.win32.foundation;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    WIN32_ERROR RegOpenKeyExW(handle hKey, wcstr lpSubKey, dword ulOptions, dword samDesired,
                              phandle phkResult) noexcept;
    WIN32_ERROR RegCreateKeyExW(handle hKey, wcstr lpSubKey, dword Reserved, wcstr wclpClass,
                                dword dwOptions, dword samDesired, pobj lpSecurityAttributes, phandle phkResult,
                                pdword dwDisposition) noexcept;
    WIN32_ERROR RegCloseKey(handle hKey) noexcept;
    WIN32_ERROR RegSetValueExW(handle hKey, wcstr lpValueName, dword Reserved,
                                                        dword dwType, const void *lpData,
                               dword cbData) noexcept;
    WIN32_ERROR RegGetValueW(handle hkey, wcstr lpSubKey, wcstr lpValue, dword dwFlags, pdword pdwType,
                             const void *pvData, pdword pcbData) noexcept;
    WIN32_ERROR RegDeleteKeyExW(handle hKey, wcstr lpSubKey, dword Reserved, dword dwFlags) noexcept;
    // no W postfix
    WIN32_ERROR RegRenameKey(handle hKey, wcstr lpSubKey, wcstr lpNewKeyName) noexcept;
    WIN32_ERROR RegDeleteValueW(handle hKey, wcstr lpValueName) noexcept;
    WIN32_ERROR RegDeleteTreeW(handle hKey, wcstr lpSubKey) noexcept;
    WIN32_ERROR RegDeleteKeyValueW(handle hKey, wcstr lpSubKey, wcstr lpValueName) noexcept;
    WIN32_ERROR RegCopyTreeW(handle hKeySrc, wcstr lpSubKey, handle hKeyDest) noexcept;
    // todo: QueryInfoKeyExW, OpenUserClassesRoot, NotifyChangeKeyValue, EnumValueW, EnumKeyExW
    // todo?: EnableReflectionKey, DisableReflectionKey, QueryReflectionKey
}
} // namespace export32