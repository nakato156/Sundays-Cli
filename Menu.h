#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>   
#include "Lista.h" 
#include "DataFrame.h"  
#include "Producto.h" 

using namespace std;

class Menu {
	float precios[6] = { 25.90f, 28.50f, 18.30f, 30.49f, 35.20f, 9.90f };
	DataFrame data;
	Lista<Producto> list_prod;
public:
	Menu();
	~Menu(); 
	DataFrame cargarDatos(); 

	Lista<Producto> generarMenu(DataFrame data); 

	void mostrarMenuLista(Lista<Producto>& menu); 

	Lista<Producto> MenuUserV2(DataFrame data);

	void initMenu();
};
#endif