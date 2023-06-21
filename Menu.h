#pragma once
#include <iostream>   
#include <Windows.h>

#ifndef MENU_H
#define MENU_H
#include "Lista.h" 
#include "DataFrame.h"  
#include "Producto.h"
#include "constantes.h"
#include "helpers.h"

using namespace std;

class Menu {
	float precios[6] = { 25.90f, 28.50f, 18.30f, 30.49f, 35.20f, 9.90f };
	DataFrame data;
	Lista<Producto> list_prod;
	COORD coordenadas;
	void _gotoxy(int x, int y) {
		gotoxy(x, y, coordenadas);
	}
public:
	Menu();
	~Menu(); 
	DataFrame cargarDatos(); 

	Lista<Producto> generarMenu(DataFrame data); 

	void mostrarMenuLista(Lista<Producto>& menu); 

	Lista<Producto> MenuUserV2(DataFrame data);

	void initMenu();
	int selectOpcion();
};
#endif