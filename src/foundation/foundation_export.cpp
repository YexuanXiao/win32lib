export module bizwen.export32.foundation;
export import bizwen.win32.foundation.base0;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    BOOL CloseHandle(handle hObject) noexcept;
    WIN32_ERROR GetLastError() noexcept;
    VOID SetLastError(win32::error dwErrCode) noexcept;
}
} // namespace export32