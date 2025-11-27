module;
#include <version>
export module bizwen.win32.utility;
import std;

export namespace win32::inline utility
{
template <typename T>
    requires std::is_enum_v<T>
constexpr auto to_underlying(T e) noexcept
{
    return static_cast<std::underlying_type_t<T>>(e);
}

namespace detail
{
// do not export because it is not wanted to be catched
struct invalid_state
{
};

struct invalid_argument
{
};
} // namespace detail

template <typename T>
constexpr void *to_void_p(T const &t) noexcept
{
    if constexpr (std::is_same_v<T, void *>)
    {
        static_assert(false, "disallow calling to_void_p with void*");
    }
    else if constexpr (std::is_class_v<T>)
    {
        return t.to_void_p();
    }
    else if constexpr (std::is_enum_v<T>)
    {
        return reinterpret_cast<void *>(to_underlying(t));
    }
    else if constexpr (std::is_integral_v<T>)
    {
        return reinterpret_cast<void *>(t);
    }
    else if constexpr (std::is_pointer_v<T>)
    {
        using non_const_type = std::remove_const_t<std::remove_pointer_t<T>>;
        return reinterpret_cast<void *>(const_cast<std::add_pointer_t<non_const_type>>(t));
    }
    else
    {
        static_assert(false);
    }
}

template <typename T>
    requires std::is_scalar_v<T>
constexpr void check_null(T value)
{
    if (value == T{})
    {
        throw detail::invalid_state{};
    }
}
template <typename T>
    requires std::is_scalar_v<T>
constexpr void check_not_null(T value)
{
    if (value == T{})
    {
        throw detail::invalid_state{};
    }
}

template <typename... Args>
void check_one(Args... args)
{
    if (!(... || args))
    {
        throw detail::invalid_argument{};
    }
}

template <typename... Args>
void check_all(Args... args)
{
    if (!(... && args))
    {
        throw detail::invalid_argument{};
    }
}

#ifdef __cpp_lib_unreachable
using std::unreachable;
#else
void unreachable [[noreturn]] () noexcept
{
    std::terminate();
}
#endif

} // namespace win32::inline utility