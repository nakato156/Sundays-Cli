#pragma once
#pragma once
#ifndef FUNCS_H
#define FUNCS_H
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Lista.h"
#include "constantes.h"

using namespace std;
enum class Categoria {
	ENTRADA,
	ENTRANTE,
	ACOMPANAMIENTO,
	PLATO_PRINCIPAL,
	DESAYUNO
};

struct Plato {
	string codigo;
	string nombre;
	Categoria categoria;
};

Categoria determinarCategoria(const string& categoriaStr);
Plato buscarPlatoPorCodigo(const string& codigo, const string& nombreArchivo);
void clasificarPlatos(Lista<Plato>& platosPrincipales, Lista<Plato>& entradas, Lista<Plato>& entrantes, Lista<Plato>& acompanamientos, Lista<Plato>& desayuno);
void gotoxy(int x, int y);
void gotoxy(int x, int y, COORD&);
TECLA getTecla();
#endif