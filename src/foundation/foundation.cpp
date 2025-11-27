export module bizwen.win32.foundation;
export import bizwen.win32.foundation.base1;
import bizwen.export32.foundation;
import std;
import beman.cstring_view;
import bizwen.win32.utility;

export namespace win32::inline foundation
{
class handle
{
  protected:
    void *hObject_ = nullptr;

  public:
    handle() = default;
    handle(const handle &other) = delete;
    handle&operator=(const handle &other) = delete;
    handle(handle &&other) noexcept
    {
        std::swap(hObject_, other.hObject_);
    }
    handle &operator=(handle &&other) noexcept
    {
        std::swap(hObject_, other.hObject_);
        return *this;
    }
    ~handle()
    {
        if (hObject_)
        {
            check_fail(export32::CloseHandle(hObject_));
        }
    }
    void *to_void_p() const noexcept
    {
        return hObject_;
    }
};

struct waitable_handle{};

template <typename T>
concept waitable = std::derived_from<T, waitable_handle> && std::derived_from<T, handle> && sizeof(T) == sizeof(handle);

} // namespace win32::inline foundation
