#include <string>
#include <vector>
#include <iostream>
//#include <memory>
#include "memory.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
// using std::shared_ptr;
// using std::weak_ptr;
using heubdpp::shared_ptr;
using heubdpp::weak_ptr;


class Person
{
public:
    string nombre;
    shared_ptr<Person> madre;
    shared_ptr<Person> padre;
    vector<weak_ptr<Person>> hijos;

    Person(string const& n, shared_ptr<Person> m = nullptr, shared_ptr<Person> p = nullptr)
        : nombre{n}
        , madre{m}
        , padre{p}
    {}

    ~Person()
    {
        cout << "Eliminando persona: " << nombre << endl;
    }
};

auto creaFamilia(string const& nombre)
{
    shared_ptr<Person> madre{new Person{"Madre de: " + nombre}};
    shared_ptr<Person> padre{new Person{"Padre de: " + nombre}};
    shared_ptr<Person> persona{new Person{nombre, madre, padre}};
    madre->hijos.push_back(persona);
    padre->hijos.push_back(persona);
    return persona;
}

int main()
{
    auto p = creaFamilia("Dylan");

    cout << "Dylan está referenciado: " << p.use_count() << " veces" << endl;

    p = nullptr;
    weak_ptr<Person> pd{p};
    if(!pd.expired() )
        cout << "Se puede utilizar el weak ptr" << endl;

    cout << "Adios" << endl;
}