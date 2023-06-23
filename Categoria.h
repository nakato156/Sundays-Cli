#pragma once
#ifndef CATEGORIA_H
#define CATEGORIA_H
#include <string>
class Categoria {

    std::string nombre;
    

public:
    struct CategoriaComparer {
        bool operator()(const Categoria& cat1, const Categoria& cat2) const {
            return cat1.getNombre() < cat2.getNombre();
        }
    };
    Categoria(std::string name = "") : nombre(name) {}

    std::string getNombre() const { return nombre; }

    bool operator==(const Categoria& cat) const {
        return nombre == cat.nombre;
    }
};
#endif 
