#include <iostream>
#include <memory>
#include "memory.h"

using namespace heubdpp;

auto fclose2(FILE* ptr)
{
    std::cout << "Destruyendo archivo\n";
    return fclose(ptr);
}

int main()
{
    heubdpp::unique_ptr<int> ptr{new int};
    //heubdpp::unique_ptr<int> ptr2{ptr};
    //heubdpp::unique_ptr<int> ptr3 = ptr;

    //heubdpp::unique_ptr<int> ptr{new int};

    unique_ptr<int> ptr2 {new int};
    unique_ptr<int> ptr3{std::move(ptr2)};

    if( !ptr2.get() ) {
        std::cout << "ptr2 ya no es propietario de nada\n";
    }

    unique_ptr<int> ptr4 {new int};
    unique_ptr<int> ptr5;
    ptr5 = std::move(ptr4);
    ptr5 = nullptr;

    auto entero = ptr3.release();
    if( !ptr3.get()) {
        std::cout << "ptr3 ya no es propietario de nada\n";
    }

    delete entero;

    *ptr = 44;
    std::cout << "Número: " << *ptr << std::endl;

    struct Punto
    {
        int x;
        int y;
    };

    unique_ptr<Punto> pt{new Punto};
    pt->x = 10;
    (*pt).y = 20;
    std::cout << "x: " << pt->x << " y: " << pt->y << std::endl;

    class MiEliminador 
    {
    public:
        auto operator()(int* ptr) noexcept
        {
            std::cout << "Eliminador de enteros\n";
            delete ptr;
        }
    };

    unique_ptr<int, MiEliminador> yyyy{new int};

    unique_ptr<int, void(*)(int*)> zzz{new int, [](int* ptr)
    {
        std::cout << "Eliminador de enteros desde lambda\n";
        delete ptr;
    }};

    unique_ptr<FILE, int(*)(FILE*)> archivo{ fopen("prueba.txt", "r"), fclose2};
}