export module bizwen.win32.foundation.base1;
export import bizwen.win32.foundation.base0;
import bizwen.export32.foundation;
import std;
import beman.cstring_view;
import bizwen.win32.utility;

export namespace win32::inline utility
{

void throw_last_error [[noreturn]] ()
{
    if (auto err = export32::GetLastError(); err != error::ERROR_SUCCESS)
    {
        throw err;
    }
    unreachable();
}

void check_throw [[noreturn]] (error err)
{
    if (err != error::ERROR_SUCCESS)
    {
        throw err;
    }
}

void check_fail [[noreturn]] (error err)
{
    if (err != error::ERROR_SUCCESS)
    {
        std::terminate();
    }
}

void check_throw [[noreturn]] (boolean err)
{
    if (err != boolean::TRUE)
    {
        throw_last_error();
    }
}

void check_fail [[noreturn]] (boolean err)
{
    if (err != boolean::TRUE)
    {
        std::terminate();
    }
}

void check_throw_last_error [[noreturn]] (bool value)
{
    if (!value)
    {
        throw_last_error();
    }
}

void check_fail_last_error [[noreturn]] (bool value)
{
    if (!value)
    {
        check_fail(export32::GetLastError());
    }
}
} // namespace win32::inline utility
