#pragma once
#include "Producto.cpp"
#include <vector> // cambiar por lista
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
	std::vector<Item> productos;
public:
	CarritoDeCompras();
	CarritoDeCompras(std::vector<Item> productos) {
		this->productos = productos;
	}
	static CarritoDeCompras load(std::vector<Producto>& productos, std::string data);
	void agregar(const Producto&);
	void agregar(const Item&);
	void eliminarProd(const Producto&);
	std::string exportar();
	float total() const;
	operator std::vector<Item>() const {
		return productos;
	}
};