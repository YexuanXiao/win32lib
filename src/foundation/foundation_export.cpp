export module bizwen.export32.foundation;
export import bizwen.win32.foundation.base0;
#include "win32_export.h"
export namespace export32
{
extern "C"
{
    BOOL CloseHandle(handle hObject);
    WIN32_ERROR GetLastError();
    VOID SetLastError(win32::error dwErrCode);
}
} // namespace export32