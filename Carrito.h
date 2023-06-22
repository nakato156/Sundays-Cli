#pragma once
#include "Producto.h"
#include "Lista.h" // cambiar por lista
#include <iostream>

struct Item {
	Producto producto;
	int cant = 1;
	bool operator==(const Item& item) const { // sirve apra compara el producto y no tenenr varios productos iguales
		return item.producto == producto;
	}
};

class CarritoDeCompras {
private:
	Lista<Item> productos;
public:
	CarritoDeCompras();
	CarritoDeCompras(Lista<Item> productos) {
		this->productos = productos;
	}
	static CarritoDeCompras load(Lista<Producto>& productos, std::string data);
	void agregar(const Producto&);
	void agregar(const Item&);
	void eliminarProd(const Producto&);
	std::string exportar();
	float total() const;
	operator Lista<Item>() const {
		return productos;
	}
};