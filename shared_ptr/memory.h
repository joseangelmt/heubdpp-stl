#pragma once

#include <functional>

namespace heubdpp
{
    template<typename T>
    class shared_ptr
    {
        using pointer = T*;
        using element_type = T;
        using deleter_type = std::function<void(pointer)>;

        struct contenedor
        {
            pointer _ptr;
            unsigned _ref;
            deleter_type _deleter{ [](pointer ptr) { delete ptr;}};

            ~contenedor()
            {
                std::cout << "destruyendo el objeto\n";
                _deleter(_ptr);
            }
        }* _contenedor{};
    public:
        shared_ptr() noexcept = default;

        shared_ptr(nullptr_t) noexcept 
            : _contenedor{}
        {}

        shared_ptr(pointer ptr)
            : _contenedor{new contenedor{ptr, 1}}
        {}

        shared_ptr(pointer ptr, deleter_type deleter)
            : _contenedor{new contenedor{ptr, 1, deleter}}
        {}

        shared_ptr(shared_ptr& otro) noexcept
            : _contenedor{otro._contenedor}
        {
            if( _contenedor )
                _contenedor->_ref++;
        }

        shared_ptr(shared_ptr&& otro) noexcept
            : _contenedor{otro._contenedor}
        {
            otro._contenedor = nullptr;
        }

        ~shared_ptr()
        {
            reset();
        }

        auto operator=(shared_ptr& otro) noexcept -> shared_ptr&
        {
            reset();
            _contenedor = otro._contenedor;
            if( _contenedor )
                _contenedor->_ref++;

            return *this;
        }

        auto operator=(shared_ptr&& otro) noexcept -> shared_ptr&
        {
            reset();
            _contenedor = otro._contenedor;
            otro._contenedor = nullptr;
            return *this;
        }

        auto operator=(nullptr_t) noexcept -> shared_ptr&
        {
            reset();
            return *this;
        }

        auto reset() noexcept
        {
            if( !_contenedor )
                return;

            _contenedor->_ref--;
            if( _contenedor->_ref == 0) {
                delete _contenedor;
            }
            _contenedor = nullptr;
        }

        auto use_count() const noexcept { return _contenedor ? _contenedor->_ref : 0; }
        auto unique() const noexcept { return use_count() == 1; }
        auto operator()() { return unique(); }
        auto get() const noexcept  -> pointer { return _contenedor ? _contenedor->_ptr : nullptr; }
        auto operator->() { return _contenedor->_ptr; }
        auto operator*() -> element_type& { return *_contenedor->_ptr; }
    };
}