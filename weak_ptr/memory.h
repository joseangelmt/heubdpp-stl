#pragma once

#include <functional>

namespace heubdpp
{
    template<typename T>
    class weak_ptr;

    template<typename T>
    class shared_ptr
    {
        using pointer = T*;
        using element_type = T;
        using deleter_type = std::function<void(pointer)>;

        friend class weak_ptr<T>;

        struct contenedor
        {
            pointer _ptr;
            unsigned _ref;
            unsigned _weakref;
            deleter_type _deleter{ [](pointer ptr) { delete ptr;}};

            auto referencias() const noexcept { return _ref + _weakref; }
            auto incrementaRef() noexcept { ++_ref;}
            auto incrementaWeakRef() noexcept{ ++_weakref;}
            auto decrementaRef() noexcept
            {
                --_ref;

                if( 0 == _ref) 
                    _deleter(_ptr);

                if( 0 == referencias() )
                    delete this;
            }

            auto decrementaWeakRef() noexcept
            {
                --_weakref;

                if( 0 == referencias() )
                    delete this;
            }
        }* _contenedor{};

        shared_ptr(contenedor* contenedor)
            : _contenedor{contenedor}
        {
            _contenedor->incrementaRef();
        }
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

            _contenedor->decrementaRef();
            _contenedor = nullptr;
        }

        auto use_count() const noexcept { return _contenedor ? _contenedor->_ref : 0; }
        auto unique() const noexcept { return use_count() == 1; }
        auto operator()() { return unique(); }
        auto get() const noexcept  -> pointer { return _contenedor ? _contenedor->_ptr : nullptr; }
        auto operator->() { return _contenedor->_ptr; }
        auto operator*() -> element_type& { return *_contenedor->_ptr; }
    };


    template<typename T>
    class weak_ptr
    {
        using element_type = T;
        using contenedor = typename shared_ptr<T>::contenedor;
        contenedor* _contenedor{};

    public:
        weak_ptr() = default;
        weak_ptr(nullptr_t) 
        {}

        weak_ptr(shared_ptr<T> sp)
            : _contenedor{sp._contenedor}
        {
            if( _contenedor )
                _contenedor->incrementaWeakRef();
        }

        weak_ptr(weak_ptr const& wp)
            : _contenedor{wp._contenedor}
        {
            if( _contenedor )
                _contenedor->incrementaWeakRef();
        }

        ~weak_ptr()
        {
            reset();
        }

        auto operator=(weak_ptr const& wp)
        {
            reset();
            _contenedor = wp._contenedor;
            _contenedor->incrementaWeakRef();
            return *this;
        }

        auto operator=(shared_ptr<T> const& sp)
        {
            reset();
            _contenedor = sp._contenedor;
            _contenedor->incrementaWeakRef();
            return *this;
        }

        auto reset() noexcept
        {
            if( !_contenedor )
                return;

            _contenedor->decrementaWeakRef();
            _contenedor = nullptr;
        }

        auto use_count() const noexcept { return _contenedor ? _contenedor->_ref : 0; }
        auto expired() const noexcept { return 0 == use_count(); }

        auto lock()
        {
            if( !_contenedor )
                return shared_ptr<T>();

            return shared_ptr<T>(contenedor);
        }
    };
}