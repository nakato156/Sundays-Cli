#pragma once
#ifndef HIST_H
#define HIST_H

#include "ArbolAVL.h"
#include "Compra.h"
#include "Usuario.h"
#include "DataFrame.h"

class HistorialCompras : public Compra {
	Lista<Compra> historial;
public:
	HistorialCompras() = default;
	HistorialCompras(Usuario client, const CarritoDeCompras& carrito) :Compra(client, carrito) {}
	Lista<Compra> load(ArbolAVL<Producto>& productos, Usuario cliente) { //cargar al historial de compras
		DataFrame file;
		file.read_csv(filename);
		//historial csv
		int size = file.size();
		for (int i = 0; i < size; i++) {
			auto fila = file[i];
			if (fila["uuid"] != cliente.getUUID()) continue;
			std::string data[] = { fila["uuid"],
				fila["cliente_uuid"],
				fila["productos"],
				fila["monto"],
				fila["fecha"]
			};
			historial.push_back(Compra::load(productos, data));
		}
		return historial;
	}
};
#endif