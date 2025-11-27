export module bizwen.export32.threading;
import bizwen.win32.foundation;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    WAIT_EVENT WaitForSingleObjectEx(handle hHandle, dword dwMilliseconds, boolean bAlertable);
    HANDLE CreateEventExW(pobj lpEventAttributes, wcstr lpName,
                          dword dwFlags, dword dwDesiredAccess);
    HANDLE OpenEventW(dword dwDesiredAccess, boolean bInheritHandle, wcstr lpName);
    BOOL SetEvent(handle hEvent);
    BOOL ResetEvent(handle hEvent);
    HANDLE CreateMutexExW(pobj lpMutexAttributes, wcstr lpName, dword dwFlags, dword dwDesiredAccess);
    HANDLE OpenMutexW(dword dwDesiredAccess, boolean bInheritHandle, wcstr lpName);
    BOOL ReleaseMutex(handle hMutex);
}
} // namespace export32