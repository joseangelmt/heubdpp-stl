#include <iostream>
#include <memory>
#include "memory.h"

using namespace heubdpp;
int main()
{
    shared_ptr<int> ptr{new int};

    std::cout << "Referencias: " << ptr.use_count() << std::endl;

    auto copia{ptr};
    std::cout << "Referencias (ptr): " << ptr.use_count() << std::endl;
    std::cout << "Referencias (copia): " << copia.use_count() << std::endl;

    shared_ptr<int> copia2;
    copia2 = ptr;
    std::cout << "Referencias: " << ptr.use_count() << std::endl;

    copia = nullptr;
    std::cout << "Referencias (ptr): " << ptr.use_count() << std::endl;

    ptr = nullptr;
    std::cout << "Referencias (ptr): " << ptr.use_count() << std::endl;

    ptr = shared_ptr<int>{new int};
    std::cout << "Referencias (ptr): " << ptr.use_count() << std::endl;
    copia = std::move(ptr);
    std::cout << "Referencias (ptr): " << ptr.use_count() << std::endl;
    std::cout << "Referencias (copia): " << copia.use_count() << std::endl;

    auto copia3{std::move(copia)};
    std::cout << "Referencias (copia): " << copia.use_count() << std::endl;
    std::cout << "Referencias (copia3): " << copia3.use_count() << std::endl;

    shared_ptr<int> ptrLambda{new int, [](int* ptr)
    {
        std::cout << "Eliminando entero\n";
        delete ptr;
    }};

    class Eliminador
    {
    public:
        auto operator()(int* ptr)
        {
            std::cout << "Eliminando desde la clase\n";
            delete ptr;
        }
    };

    shared_ptr<int> ptrClase{new int, Eliminador()};
 }