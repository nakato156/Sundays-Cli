#pragma once
#include "Hash.h"
#include "Producto.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
	void leerDesdeArchivo(const std::string& nombreArchivo) {
		std::ifstream archivo(nombreArchivo);
		std::string linea;

		while (std::getline(archivo, linea)) {
			std::stringstream ss(linea);
			std::string codigo, nombre, categoria;
			double precio;

			if (std::getline(ss, codigo, ',') && std::getline(ss, nombre, ',') &&
				std::getline(ss, categoria, ',') && ss >> precio) {
				Producto plato(codigo, nombre, categoria, precio);
				append(plato);
			}
		}

		archivo.close();
	}
};