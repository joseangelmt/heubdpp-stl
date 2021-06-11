#pragma once

namespace heubdpp
{
    template<typename T>
    class default_delete
    {
    public:
        auto operator()(T* objeto) noexcept
        {
            delete objeto;
        }
    };

    template<typename T, typename D=default_delete<T>>
    class unique_ptr
    {
        using pointer = T*;
        using element_type = T;
        using deleter_type = D;

        pointer _ptr;
        deleter_type _deleter;
    public:
        unique_ptr(pointer ptr = nullptr) noexcept
        : _ptr{ptr}
        {}

        unique_ptr(pointer ptr, deleter_type deleter ) noexcept
            : _ptr{ptr}
            , _deleter{deleter}
        {}

        unique_ptr(unique_ptr&) = delete;

        unique_ptr(unique_ptr&& otro) noexcept
            : _ptr{otro._ptr}
        {
            otro._ptr = nullptr;
        }

        ~unique_ptr()
        {
            reset();
        }

        unique_ptr& operator=(unique_ptr const&) = delete;

        unique_ptr& operator=(unique_ptr&& otro) noexcept
        {
            reset();

            _ptr = otro._ptr;
            otro._ptr = nullptr;
            return *this;
        }

        unique_ptr& operator=(nullptr_t) noexcept
        {
            reset();
            return *this;
        }

        auto get() const noexcept { return _ptr; }

        auto reset() noexcept
        {
            _deleter(_ptr);
            _ptr = nullptr;
        }

        auto release() noexcept
        {
            auto copia = _ptr;
            _ptr = nullptr;
            return copia;
        }

        auto operator*() noexcept -> T& { return *_ptr;}
        auto operator->() noexcept { return _ptr; }
    };

    template<typename T>
    class default_delete<T[]>
    {
    public:
        auto operator()(T* objeto) noexcept
        {
            delete[] objeto;
        }
    };

    template<typename T, typename D>
    class unique_ptr<T[], D>
    {
        using pointer = T*;
        using element_type = T;
        using deleter_type = D;

        pointer _ptr;
        deleter_type _deleter;
    public:
        unique_ptr(pointer ptr = nullptr) noexcept
        : _ptr{ptr}
        {}

        unique_ptr(pointer ptr, deleter_type deleter ) noexcept
            : _ptr{ptr}
            , _deleter{deleter}
        {}

        unique_ptr(unique_ptr&) = delete;

        unique_ptr(unique_ptr&& otro) noexcept
            : _ptr{otro._ptr}
        {
            otro._ptr = nullptr;
        }

        ~unique_ptr()
        {
            reset();
        }

        unique_ptr& operator=(unique_ptr const&) = delete;

        unique_ptr& operator=(unique_ptr&& otro) noexcept
        {
            reset();

            _ptr = otro._ptr;
            otro._ptr = nullptr;
            return *this;
        }

        unique_ptr& operator=(nullptr_t) noexcept
        {
            reset();
            return *this;
        }

        auto get() const noexcept { return _ptr; }

        auto reset() noexcept
        {
            _deleter(_ptr);
            _ptr = nullptr;
        }

        auto release() noexcept
        {
            auto copia = _ptr;
            _ptr = nullptr;
            return copia;
        }

        auto operator[](size_t index) -> T& { return _ptr[index]; }
    };

}
