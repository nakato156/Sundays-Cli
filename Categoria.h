#pragma once
#ifndef CATEGORIA_H
#define CATEGORIA_H
#include <string>

class Categoria {
	std::string nombre;
public:
	Categoria(std::string name = "") : nombre(name) {};
	std::string getNombre() { return nombre; };
};

#endif 
