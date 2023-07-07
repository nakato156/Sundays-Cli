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
		string uuidCliente = cliente.getUUID();
		int size = file.size();
		for (int i = 0; i < size; i++) {
			auto fila = file[i];
			cout << fila["client_uuid"] << endl;
			//if (fila["client_uuid"].compare(uuidCliente) != 0) continue;
			//std::string data[] = { fila["uuid"],
			//	fila["client_uuid"],
			//	fila["productos"],
			//	fila["monto"],
			//	fila["fecha"]
			//};
			//historial.push_back(Compra::load(productos, data));
		}
		return historial;
	}
	Lista<Compra> getLista() { return historial; }
};
#endif