export module bizwen.export32.threading;
import bizwen.win32.foundation;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    WAIT_EVENT WaitForSingleObjectEx(handle hHandle, dword dwMilliseconds, boolean bAlertable) noexcept;
    HANDLE CreateEventExW(pobj lpEventAttributes, wcstr lpName, dword dwFlags, dword dwDesiredAccess) noexcept;
    HANDLE OpenEventW(dword dwDesiredAccess, boolean bInheritHandle, wcstr lpName) noexcept;
    BOOL SetEvent(handle hEvent) noexcept;
    BOOL ResetEvent(handle hEvent) noexcept;
    HANDLE CreateMutexExW(pobj lpMutexAttributes, wcstr lpName, dword dwFlags, dword dwDesiredAccess) noexcept;
    HANDLE OpenMutexW(dword dwDesiredAccess, boolean bInheritHandle, wcstr lpName) noexcept;
    BOOL ReleaseMutex(handle hMutex) noexcept;
}
} // namespace export32