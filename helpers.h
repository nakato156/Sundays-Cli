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
#include "Producto.h"

using namespace std;



map<string, Lista<Producto>> clasificarPlatos();
void gotoxy(int x, int y);
void gotoxy(int x, int y, COORD&);
TECLA getTecla();
#endif