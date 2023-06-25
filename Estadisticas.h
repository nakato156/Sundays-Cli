#pragma once
#ifndef STATS_H
#define STATS_H
#include "DataFrame.h"
#include "Categoria.h"
#include <unordered_map>

class Estadisticas {
	Estadisticas() = default;

	void resume() {
		DataFrame file;
		file.read_csv("historial.csv");

		int total_peidos = file.size();
		std::unordered_map<Categoria, int> group_by_cat; 
		// cuentas la cantidad de platos vendidos por categoria
		// cuentas los clientes que hay en total (solamente los únicos)
		// Cual es el plato mas vendido
		// promedio de consumo por cliente


		for (int i = 0; i < total_peidos; i++) {
			file[i]["pedido"];
		}

	}
};

#endif