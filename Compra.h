#pragma once
#ifndef COMPRA_H
#define COMPRA_H

#include "Usuario.h"
#include "Carrito.h"
#include "Crypt.h"
#include "DataFrame.h"
#include <functional>
#include "ArbolAVL.h"
#include "Fecha.h"

class Compra {
protected:
	string filename = "historial.csv";
	float monto = 0;
	std::string UUID;
	Fecha fecha;
	Usuario cliente;
	CarritoDeCompras carrito;
	static Compra load(ArbolAVL<Producto>&, const std::string[]);
public:
	Compra();
	Compra(Usuario& client, const CarritoDeCompras&);
	void Guardar();
	friend ostream& operator<<(ostream& os, const Compra& compra) {
		Lista<Item> prods = compra.carrito;
		os << "Fecha:" << compra.fecha << endl;
		for (int i = 0; i < prods.getSize(); i++) {
			os << prods.at(i).producto << "\t(" << prods.at(i).cant << ")" << endl;
		}
		os << "---------------------------------------\n" << compra.carrito.total();
		return os;
	}
};
#endif