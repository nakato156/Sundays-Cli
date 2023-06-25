#pragma once
#ifndef DESCUENTO_H
#define DESCUENTO_H
#include <string>
#include <unordered_map>

static const std::unordered_map<std::string, int> descuentos = {
	{"desc10", 10}, {"descA", 30}, {"descC", 50}, {"descJ", 20}
};

class Descuento {
	int porcentaje;
	std::string codigo;

public:
	Descuento(std::string cod) : codigo(cod) {
		if (descuentos.find(cod) != descuentos.end())
			porcentaje = descuentos.at(cod);
	}
	Descuento(int percent = 0, std::string cod = "") : porcentaje(percent), codigo(cod) {};

	float aplicar(float precio) {
		return precio - (precio * porcentaje / 100);
	}

	static bool validar(std::string cod) {
		return descuentos.find(cod) != descuentos.end();
	}
};

#endif 