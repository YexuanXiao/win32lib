export module bizwen.win32.threading;
import std;
import bizwen.export32.threading;
import bizwen.win32.foundation;
import bizwen.win32.utility;
import bizwen.win32.security.project;
import bizwen.export32.foundation;

export namespace win32::inline threading
{

enum class create_event_option : unsigned long
{
    zero,
    initial_set = 1u,
    manual_reset = 2u,
};

constexpr auto create_event_zero = create_event_option::zero;
constexpr auto create_event_initial_set = create_event_option::initial_set;
constexpr auto create_event_manual_reset = create_event_option::manual_reset;

enum class event_access : unsigned long
{
    /*
    delete_object = 0x00010000,
    read_control = 0x00020000,
    */
    synchronize = 0x00100000,
    /*
    write_dac = 0x00040000,
    write_owner = 0x00080000,
    */
    modify_state = 0x0002,
    all_access = 0x001F0003,
};

constexpr event_access operator|(event_access lhs, event_access rhs) noexcept
{
    return static_cast<event_access>(to_underlying(lhs) | to_underlying(rhs));
}

class event : public waitable_handle, public handle
{
  public:
    event() = default;
    event(event const &other) = delete;
    event &operator=(event const &other) = delete;
    event(event &&other) = default;
    event &operator=(event &&other) = default;

    static event create_event(project::security_attributes const *security_attributes = nullptr,
                              wcstring_view name = {}, create_event_option option = create_event_zero,
                              event_access access = event_access::synchronize)
    {
        event temp;
        temp.hObject_ =
            export32::CreateEventExW(security_attributes, null_or(name), to_underlying(option), to_underlying(access));
        check_throw_last_error(temp.hObject_ != nullptr);
    }

    static event open_event(wcstring_view name, bool inherit_handle = false,
                            event_access access = event_access::synchronize)
    {
        event temp;
        temp.hObject_ = export32::OpenEventW(to_underlying(access), inherit_handle, null_or(name));
        check_throw_last_error(temp.hObject_ != nullptr);
        return temp;
    }

    void set_event()
    {
        check_one(hObject_ != nullptr);
        check_throw(export32::SetEvent(hObject_));
    }

    void reset_event()
    {
        check_one(hObject_ != nullptr);
        check_throw(export32::ResetEvent(hObject_));
    }
};

static_assert(waitable<event>);

enum class mutex_access : unsigned long
{
    /*
    delete_object = 0x00010000,
    read_control = 0x00020000,
    */
    synchronize = 0x00100000,
    /*
    write_dac = 0x00040000,
    write_owner = 0x00080000,
    */
    modify_state = 0x0001,
    all_access = 0x001F0001,
};

constexpr mutex_access operator|(mutex_access lhs, mutex_access rhs) noexcept
{
    return static_cast<mutex_access>(to_underlying(lhs) | to_underlying(rhs));
}

class mutex : public waitable_handle, public handle
{

  public:
    mutex() = default;
    mutex(mutex const &other) = delete;
    mutex &operator=(mutex const &other) = delete;
    mutex(mutex &&other) = default;
    mutex &operator=(mutex &&other) = default;
    static mutex create_mutex(project::security_attributes const *security_attributes = nullptr,
                              wcstring_view name = {}, bool initial_owner = false,
                              mutex_access access = mutex_access::synchronize)
    {
        mutex temp;
        temp.hObject_ =
            export32::CreateMutexExW(security_attributes, null_or(name),
                                     initial_owner ? 1u /* CREATE_MUTEX_INITIAL_OWNER */ : 0u, to_underlying(access));
        check_throw_last_error(temp.hObject_ != nullptr);
    }
    static mutex open_mutex(wcstring_view name, bool inherit_handle = false,
                            mutex_access access = mutex_access::synchronize)
    {
        mutex temp;
        temp.hObject_ = export32::OpenMutexW(to_underlying(access), inherit_handle, null_or(name));
        check_throw_last_error(temp.hObject_ != nullptr);
        return temp;
    }
    void release_mutex()
    {
        check_one(hObject_ != nullptr);
        check_throw(export32::ReleaseMutex(hObject_));
    }

    void lock()
    {
        if (auto e = export32::WaitForSingleObjectEx(hObject_, (unsigned int)(-1), false); e != wait_event::object_0)
        {
            throw_last_error();
        }
    }

    void unlock()
    {
        release_mutex();
    }
};

static_assert(waitable<mutex>);
} // namespace win32::inline threading