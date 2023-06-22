#pragma once
#include "Hash.h"
#include "Producto.h"

class HashProduct {
	HashTabla<string, Producto> tablaHash;
	void(*print)(const Producto);
public:
	HashProduct() {
		print = [](const Producto prod) -> void {
			std::cout << prod.getCodigo() << "\t\t" << prod.getNombre() << "\t\t" << prod.getPrecio() << std::endl;
		};
	}

	void append(Producto& prod) {
		tablaHash.insertar(prod.getCodigo(), prod);
	}
	Producto get(const std::string& cod) {
		return tablaHash.get(cod);
	}

	size_t size() const { return tablaHash.size(); }

	void imprimir() const {
		tablaHash.imprimir(print);
	}
};