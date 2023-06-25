#pragma once
#ifndef FUNCS_H
#define FUNCS_H
#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Lista.h"
#include "constantes.h"
#include "Producto.h"
#include "Categoria.h"

using namespace std;
using MapadeCate = std::map<Categoria, Lista<Producto>, Categoria::CategoriaComparer>;
MapadeCate clasificarPlatos();
Categoria buscarCategoriaPorCodigo(const MapadeCate& categoriasPlatos, const string& codigo);
string inputPassword();
void printSelectLine(const HANDLE hConsole, const vector<string>, const int selectedLine = 0, const WORD color = 7);
void printColoredLine(const HANDLE hConsole, const vector<pair<string, WORD>>);
void gotoxy(int x, int y);
void gotoxy(int x, int y, COORD&);
TECLA getTecla();
pair<int, int> selectOpcion(int min_x = 0, int max_x = 0, int min_y = 0, int max_y = 0);
#endif