export module bizwen.win32.security;
import bizwen.win32.security.project;
import bizwen.win32.foundation;
import bizwen.win32.utility;
import std;
export namespace win32::inline security
{
class security_attributes
{
    struct sa_impl
    {
        unsigned long nLength;
        void *lpSecurityDescriptor;
        boolean bInheritHandle;
    };
    const unsigned long nLength = sizeof(sa_impl);
    void *lpSecurityDescriptor{};
    boolean bInheritHandle{};

  public:
    security_attributes() = delete;
    security_attributes(security_attributes const &other) = delete;
    security_attributes &operator=(security_attributes const &other) = delete;
    void *to_void_p() const noexcept
    {
        if (lpSecurityDescriptor == nullptr)
        {
            check_null(bInheritHandle);
            return nullptr;
        }
        else
        {
            return win32::to_void_p(this);
        }
    }

    operator project::security_attributes *() noexcept
    {
        return reinterpret_cast<project::security_attributes *>(this);
    }
};
} // namespace win32::inline security
