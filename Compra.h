#pragma once
#ifndef COMPRA_H
#define COMPRA_H

#include "Usuario.h"
#include "Carrito.h"
#include "Crypt.h"
#include "DataFrame.h"
#include <functional>

class Compra {
protected:
	string filename = "historial.csv";
	float monto = 0;
	std::string UUID, fecha;
	Usuario cliente;
	CarritoDeCompras carrito;
	static Compra load(Lista<Producto>&, const std::string[]);
public:
	Compra();
	Compra(Usuario client, const CarritoDeCompras&);
	void Guardar();
};
#endif