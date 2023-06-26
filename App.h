#pragma once
#include <Windows.h>
#include "Login.h"
#include "Registro.h"
#include "Menu.h"
#include "Vistas.h"

class App : virtual public Login, virtual public Registro {
	HANDLE hConsole;
	Usuario& usuario;
	CarritoDeCompras carrito;
	ArbolAVL<Producto> productos;
	void mostrarOpciones(HANDLE, int select = 0);
public:
	App() = default;
	App(HANDLE hConsole_, Usuario& user) : hConsole(hConsole_), Login(user), Registro(user), usuario(user) {
		auto comparador = [](Producto a, Producto b) ->short {
			if (a.getNombre().compare(b.getNombre()) < 0) return -1;
			else if (a.getNombre().compare(b.getNombre()) > 0) return 1;
			else return 0; 
		};
		auto funcImprimir = [](Producto p)->void {cout << p.getNombre() << "\t" << p.getCategoria() << "\t" << p.getPrecio() << endl;  };
		productos = ArbolAVL<Producto>(funcImprimir, comparador);
	};
	void cargarDatos();
	void init();
};