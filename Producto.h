#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream> 
using namespace std;
class Producto {
private:
	float precio = 0;
	string nombre = "";
	string categoria = "";
	string codigo; 
public:
	Producto() {}
	Producto(string codigo,string nombre, string categoria, float precio) {
		this->codigo = codigo; 
		this->nombre = nombre;
		this->categoria = categoria;
		this->precio = precio;
	}
	~Producto() {}
	string getCodigo();
	string getNombre();
	string getCategoria();
	float getPrecio()const ; 

	//SOBRECARGAS DE OPERADORES

	//sobrecarga para el ==

	bool operator==(const Producto& otroProducto) const {
		return (precio == otroProducto.precio);
	}

	//sobrecarga para el <
	bool operator<(const Producto& otroProducto) const {
		return precio < otroProducto.precio;
	}
	//sobrecarga para el >
	bool operator>(const Producto& otroProducto) const {
		return precio > otroProducto.precio;
	}
	//sobrecarga para coutear
	friend ostream& operator<<(ostream& os, const Producto& producto) {
		os << producto.nombre << " " << producto.categoria << " " << producto.precio << endl;
		return os;
	}
};
#endif