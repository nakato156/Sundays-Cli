#pragma once
#include "Usuario.h"
#include "Carrito.h"
//#include "Lista.h"
#include <iostream>
#include <string>
#include <functional>

class Compra {
protected:
	string filename = "historial.csv";
	float monto = 0;
	std::string UUID, fecha;
	Usuario cliente;
	CarritoDeCompras carrito;
	static Compra load(MiVector<Producto>&, const std::string[]);
public:
	Compra();
	Compra(Usuario client, const CarritoDeCompras&);
	void Guardar();
};