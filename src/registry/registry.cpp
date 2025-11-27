export module bizwen.win32.registry;
import std;
import bizwen.export32.registry;
import bizwen.win32.foundation;
import bizwen.win32.utility;
import bizwen.win32.security.project;

export namespace win32::inline registry
{

enum class predefined_key : std::size_t
{
    null = 0,
    hkcr = 0x80000000,
    hkcu = 0x80000001,
    hklm = 0x80000002,
    hku = 0x80000003,
    /*
    hkpd = 0x80000004,
    hkpt = 0x80000050,
    hkpnlst = 0x80000060,
    hkcc = 0x80000005,
    hkdd = 0x80000006,   // removed since windows 2000
    hkculs = 0x80000007,
    */
};

static_assert(sizeof(predefined_key) == sizeof(void *));

constexpr auto hkcr = predefined_key::hkcr;
constexpr auto hkcu = predefined_key::hkcu;
constexpr auto hklm = predefined_key::hklm;
constexpr auto hku = predefined_key::hku;

enum class registry_access : unsigned long
{
    query_value = 0x0001,
    set_value = 0x0002,
    create_sub_key = 0x0004,
    enumerate_sub_keys = 0x0008,
    notify = 0x0010,
    /*
    https://scorpiosoftware.net/2020/07/17/creating-registry-links/
    win32 DeleteKey cannot delete symbolic link keys
    key_create_link = 0x0020,
    */
    wow64_32key = 0x0200,
    wow64_64key = 0x0100,
    read = 0x20019,
    write = 0x20006,
    execute = 0x20019,
    all_access = 0xF003F,
};

constexpr registry_access key_query_value = registry_access::query_value;
constexpr registry_access key_set_value = registry_access::set_value;
constexpr registry_access key_create_sub_key = registry_access::create_sub_key;
constexpr registry_access key_enumerate_sub_keys = registry_access::enumerate_sub_keys;
constexpr registry_access key_notify = registry_access::notify;
constexpr registry_access key_wow64_32key = registry_access::wow64_32key;
constexpr registry_access key_wow64_64key = registry_access::wow64_64key;
constexpr registry_access key_read = registry_access::read;
constexpr registry_access key_write = registry_access::write;
constexpr registry_access key_execute = registry_access::execute;
constexpr registry_access key_all_access = registry_access::all_access;

constexpr registry_access operator|(registry_access lhs, registry_access rhs) noexcept
{
    return static_cast<registry_access>(to_underlying(lhs) | to_underlying(rhs));
}

enum class registry_create_option : unsigned long
{
    key_non_volatile = 0x00000000,
    key_volatile = 0x00000001,
    /*
    create_link = 0x00000002,
    backup_restore = 0x00000004,
    open_link = 0x00000008,
    */
    dont_virtualize = 0x00000010,
};

constexpr auto reg_option_non_volatile = registry_create_option::key_non_volatile;
constexpr auto reg_option_volatile = registry_create_option::key_volatile;
constexpr auto reg_option_dont_virtualize = registry_create_option::dont_virtualize;

constexpr registry_create_option operator|(registry_create_option lhs, registry_create_option rhs) noexcept
{
    return static_cast<registry_create_option>(to_underlying(lhs) | to_underlying(rhs));
}

enum class registry_value_type : unsigned long
{
    none = 0,
    sz = 1,
    expand_sz = 2,
    binary = 3,
    dword = 4,
    dword_little_endian = 4,
    /*
    dword_big_endian = 5, no_corresponding registry restrict type
    link = 6,
    */
    multi_sz = 7,
    /*
    resource_list = 8,
    full_resource_descriptor = 9,
    resource_requirements_list = 10,
    */
    qword = 11,
    qword_little_endian = 11,
};

constexpr auto reg_none = registry_value_type::none;
constexpr auto reg_sz = registry_value_type::sz;
constexpr auto reg_expand_sz = registry_value_type::expand_sz;
constexpr auto reg_binary = registry_value_type::binary;
constexpr auto reg_dword = registry_value_type::dword;
constexpr auto reg_dword_little_endian = registry_value_type::dword_little_endian;
constexpr auto reg_multi_sz = registry_value_type::multi_sz;
constexpr auto reg_qword = registry_value_type::qword;
constexpr auto reg_qword_little_endian = registry_value_type::qword_little_endian;

namespace detail
{
void verify_registry_value_type(registry_value_type type)
{
    using enum registry_value_type;
    if (!(type == none || type == sz || type == expand_sz || type == binary || type == dword || type == multi_sz ||
          type == qword))
    {
        throw error::ERROR_NOT_SUPPORTED;
    }
}
} // namespace detail

enum class registry_restrict_type : unsigned long
{
    reg_none = 0x00000001,
    reg_sz = 0x00000002,
    reg_expand_sz = 0x00000004,
    reg_binary = 0x00000008,
    reg_dword = 0x00000010,
    reg_multi_sz = 0x00000020,
    reg_qword = 0x00000040,
    /*
    dword = 0x00000018,
    qword = 0x00000040,
    */
    any = 0x0000ffff,
    noexpand = 0x10000000,
    zeroonfailure = 0x20000000,
    subkey_wow6464key = 0x00010000,
    subkey_wow6432key = 0x00020000,
};

constexpr registry_restrict_type operator|(registry_restrict_type lhs, registry_restrict_type rhs) noexcept
{
    return static_cast<registry_restrict_type>(to_underlying(lhs) | to_underlying(rhs));
}

constexpr auto rrf_rt_reg_none = registry_restrict_type::reg_none;
constexpr auto rrf_rt_reg_sz = registry_restrict_type::reg_sz;
constexpr auto rrf_rt_reg_expand_sz = registry_restrict_type::reg_expand_sz;
constexpr auto rrf_rt_reg_binary = registry_restrict_type::reg_binary;
constexpr auto rrf_rt_reg_dword = registry_restrict_type::reg_dword;
constexpr auto rrf_rt_reg_multi_sz = registry_restrict_type::reg_multi_sz;
constexpr auto rrf_rt_reg_qword = registry_restrict_type::reg_qword;
constexpr auto rrf_rt_any = registry_restrict_type::any;
constexpr auto rrf_noexpand = registry_restrict_type::noexpand;
constexpr auto rrf_zeroonfailure = registry_restrict_type::zeroonfailure;
constexpr auto rrf_subkey_wow6464key = registry_restrict_type::subkey_wow6464key;
constexpr auto rrf_subkey_wow6432key = registry_restrict_type::subkey_wow6432key;

class registry_key
{
    void *hKey_ = nullptr;

  public:
    void *to_void_p() const noexcept
    {
        return hKey_;
    }

    registry_key() = default;
    registry_key(registry_key &&other) noexcept
    {
        std::swap(hKey_, other.hKey_);
    }
    registry_key &operator=(registry_key &&other) noexcept
    {
        std::swap(hKey_, other.hKey_);
        return *this;
    }

    void close()
    {
        if (hKey_)
        {
            check_throw(export32::RegCloseKey(hKey_));
            hKey_ = nullptr;
        }
    }

    ~registry_key()
    {
        if (hKey_)
        {
            // return error_invalid_handle if pass nullptr
            check_fail(export32::RegCloseKey(hKey_));
        }
    }

    [[nodiscard]] static registry_key open_key(predefined_key key, wcstring_view sub_key, registry_access sam_desired)
    {
        registry_key temp;
        check_throw(export32::RegOpenKeyExW(win32::to_void_p(key), null_or(sub_key), 0u, to_underlying(sam_desired),
                                            &temp.hKey_));
    }

  private:
    [[nodiscard]] static registry_key create_impl(void *key, wcstring_view sub_key, wcstring_view class_name,
                                                  registry_create_option option, registry_access sam_desired,
                                                  project::security_attributes const *security_attributes,
                                                  bool allow_exist = true)
    {
        registry_key temp;
        // 1: not exist, 2: exist
        auto disposition = 0ul;
        check_throw(export32::RegCreateKeyExW(key, null_or(sub_key), 0u, null_or(class_name), to_underlying(option),
                                              to_underlying(sam_desired), security_attributes, &temp.hKey_,
                                              &disposition));
        if (disposition == 2u && !allow_exist)
        {
            throw error::ERROR_ALREADY_EXISTS;
        }
        return temp;
    }

  public:
    // throw registry_error::key_is_exist
    [[nodiscard]] static registry_key create_key(predefined_key key, wcstring_view sub_key, wcstring_view class_name,
                                                 registry_create_option option, registry_access sam_desired,
                                                 project::security_attributes const *security_attributes,
                                                 bool allow_exist = true)
    {
        return create_impl(win32::to_void_p(key), sub_key, class_name, option, sam_desired, security_attributes,
                           allow_exist);
    }

    // throw registry_error::key_is_exist
    [[nodiscard]] static registry_key create_key(registry_key key, wcstring_view sub_key, wcstring_view class_name,
                                                 registry_create_option option, registry_access sam_desired,
                                                 project::security_attributes const *security_attributes,
                                                 bool allow_exist = true)
    {
        return create_impl(win32::to_void_p(key), sub_key, class_name, option, sam_desired, security_attributes,
                           allow_exist);
    }

  private:
    void set_value_impl(wcstring_view name, registry_value_type type, const void *data, std::size_t size)
    {
        check_throw(export32::RegSetValueExW(hKey_, null_or(name), 0u, to_underlying(type), data,
                                             static_cast<unsigned long>(size)));
    }

  public:
    void set_value(wcstring_view name, wcstring_view value, registry_value_type type = reg_sz)
    {
        using enum registry_value_type;
        check_one(type == sz, type == multi_sz, type == expand_sz);
        set_value_impl(name, type, static_cast<const void *>(value.data()),
                       static_cast<unsigned long>((value.size() + 1u) * 2u) /* NB */);
    }

    void set_value(wcstring_view name, std::span<const std::byte> value, registry_value_type type = reg_binary)
    {
        using enum registry_value_type;
        check_one(type == none, type == binary);
        set_value_impl(name, type, static_cast<const void *>(value.data()), static_cast<unsigned long>(value.size()));
    }

    void set_value(wcstring_view name, std::span<const unsigned char> value, registry_value_type type = reg_binary)
    {
        set_value(name, std::as_bytes(value), type);
    }

    void set_value(wcstring_view name, unsigned long value)
    {
        set_value_impl(name, reg_dword, static_cast<const void *>(&value), static_cast<unsigned long>(sizeof(value)));
    }

    void set_value(wcstring_view name, unsigned long long value)
    {
        set_value_impl(name, reg_qword, static_cast<const void *>(&value), static_cast<unsigned long>(sizeof(value)));
    }

    // throw registry_error::verify_registry_value_type
    auto get_value_info(wcstring_view sub_key, wcstring_view name, registry_restrict_type type = rrf_rt_any)
    {
        struct value_info
        {
            registry_value_type type;
            unsigned long size;
        };
        value_info result;
        check_throw(export32::RegGetValueW(hKey_, null_or(sub_key), null_or(name), to_underlying(rrf_rt_any),
                                           reinterpret_cast<unsigned long *>(&result.type), nullptr, &result.size));
        detail::verify_registry_value_type(result.type);
        return result;
    }

    // Passing wstring.data(), wstring.size() + 1 is safe.
    // Returns the number of characters written, including the trailing 0.
    std::size_t get_value(wcstring_view sub_key, wcstring_view name, std::span<wchar_t> value,
                          registry_restrict_type type)
    {
        auto type_u = to_underlying(type);
        check_one(type_u & to_underlying(rrf_rt_reg_sz), type_u & to_underlying(rrf_rt_reg_expand_sz),
                  type_u & to_underlying(rrf_rt_reg_multi_sz));
        unsigned long buffer_size = static_cast<unsigned long>((value.size() + 1u) * sizeof(wchar_t));
        check_throw(export32::RegGetValueW(hKey_, null_or(sub_key), null_or(name), to_underlying(type), nullptr,
                                           static_cast<void *>(value.data()), &buffer_size));
        return buffer_size / sizeof(wchar_t);
    }

    std::size_t get_value(wcstring_view sub_key, wcstring_view name, std::span<std::byte> data,
                          registry_restrict_type type = rrf_rt_reg_binary)
    {
        auto type_u = to_underlying(type);
        check_one(type_u & to_underlying(rrf_rt_reg_none), type_u & to_underlying(rrf_rt_reg_binary));
        unsigned long buffer_size = static_cast<unsigned long>(data.size());
        check_throw(export32::RegGetValueW(hKey_, null_or(sub_key), null_or(name), to_underlying(type), nullptr,
                                           static_cast<void *>(data.data()), &buffer_size));
        return buffer_size;
    }

    std::size_t get_value(wcstring_view sub_key, wcstring_view name, std::span<unsigned char> data,
                          registry_restrict_type type = rrf_rt_reg_binary)
    {
        return get_value(sub_key, name, std::as_writable_bytes(data), type);
    }

    void get_value(wcstring_view sub_key, wcstring_view name, unsigned long &value)
    {
        unsigned long buffer_size = static_cast<unsigned long>(sizeof(value));
        check_throw(export32::RegGetValueW(hKey_, null_or(sub_key), null_or(name), to_underlying(rrf_rt_reg_qword),
                                           nullptr, static_cast<void *>(&value), &buffer_size));
    }

    void get_value(wcstring_view sub_key, wcstring_view name, unsigned long long &value)
    {
        unsigned long buffer_size = static_cast<unsigned long>(sizeof(value));
        check_throw(export32::RegGetValueW(hKey_, null_or(sub_key), null_or(name), to_underlying(rrf_rt_reg_qword),
                                           nullptr, static_cast<void *>(&value), &buffer_size));
    }

    void delete_key(wcstring_view sub_key = {}, registry_access sam_desired = {})
    {
        check_throw(export32::RegDeleteKeyExW(hKey_, null_or(sub_key), to_underlying(sam_desired), 0u));
        hKey_ = nullptr;
    }

    void rename_key(wcstring_view sub_key, wcstring_view new_key_name)
    {
        check_throw(export32::RegRenameKey(hKey_, null_or(sub_key), null_or(new_key_name)));
    }

    void delete_value(wcstring_view value_name)
    {
        check_throw(export32::RegDeleteValueW(hKey_, null_or(value_name)));
    }

    void delete_key_value(wcstring_view sub_key, wcstring_view value_name)
    {
        check_throw(export32::RegDeleteKeyValueW(hKey_, null_or(sub_key), null_or(value_name)));
    }

    void delete_tree(wcstring_view sub_key)
    {
        check_throw(export32::RegDeleteTreeW(hKey_, null_or(sub_key)));
    }

    void copy_tree(wcstring_view sub_key, registry_key dest_key)
    {
        check_throw(export32::RegCopyTreeW(hKey_, null_or(sub_key), dest_key.hKey_));
    }
};
} // namespace win32::inline registry