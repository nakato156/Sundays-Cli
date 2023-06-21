#pragma once
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

using namespace std;
map<string, Lista<Producto>> clasificarPlatos();
void printSelectLine(HANDLE hConsole, vector<string>, int selectedLine = 0, int color = 7);
void gotoxy(int x, int y);
void gotoxy(int x, int y, COORD&);
TECLA getTecla();
#endif