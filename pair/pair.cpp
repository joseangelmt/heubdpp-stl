#include <iostream>
#include <tuple>
#include "tuple.h"

//using namespace std;
using namespace heubdpp;
using std::cout;
using std::endl;

struct MaxMin
{
    int ancho;
    int alto;
};

auto calculaMaxMin(int xmin, int xmax, int ymin, int ymax)
{
    return MaxMin{xmax - xmin, ymax - ymin};
}

template <typename T>
auto calculaMaxMinPar(T xmin, T xmax, T ymin, T ymax)
{
    return std::pair<T, T>{xmax - xmin, ymax - ymin};
}

class ClaseMovible
{
public:
    ClaseMovible() = default;
    ClaseMovible(ClaseMovible &&otro)
    {
        cout << "Instanciando por movimiento" << endl;
    }
};

int main()
{
    /*    auto mm = calculaMaxMin(2, 5, 0, 10);

    auto mm2 = calculaMaxMinPar(2, 5, 0, 10);
    auto mm3 = calculaMaxMinPar(2.0, 5.0, 0.0, 10.0);
*/
    pair<int, int> p1;

    int const i1 = 10;
    float const f1 = 2.0f;
    pair<int, float> p2{i1, f1};

    pair<int, int> p3{12, 13};
    pair<int, int> p4{12.5, 44.6f};

    pair<int, int> p5{p3};

    pair<float, float> p6{1.0f, 2.0f};
    pair<int, int> p7{p6};

    ClaseMovible cm;
    pair<int, ClaseMovible> p8{10, std::move(cm)};

    pair<int, int> p9 = p3;

    cout << p9.first << endl;
    p9.first = 111;
    cout << p9.first << endl;

    cout << get<0>(p9) << endl;
    get<0>(p9) = -1;
    cout << p9.first << endl;
    get<1>(p9) = -1;
    cout << p9.second << endl;

    pair<int, int> p10{1, 2};
    pair<int, int> p11{2, -1};

    if (p10 < p11)
        cout << "p10 es menor que p11" << endl;

    auto p12 = make_pair(2, 4);
}