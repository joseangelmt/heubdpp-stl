#include <iostream>
#include <functional>

void func(int x, int y)
{
    std::cout << "función\n";
}

auto l = [](int x, int y)
{
    std::cout << "lambda\n";   
};

class ClaseA
{
public:
    void operator()(int x, int y)
    {
        std::cout << "clase\n";
    }
};

int main()
{
    ClaseA a;

    std::bind(func, 10, 20)();
    std::bind(l, 10, 20)();
    std::bind(a, 10, 20)();
}