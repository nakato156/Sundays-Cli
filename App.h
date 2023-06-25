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
	void mostrarOpciones(HANDLE, int select = 0);
public:
	App() = default;
	App(HANDLE hConsole_, Usuario& user) : hConsole(hConsole_), Login(user), Registro(user), usuario(user) {};
	void init();
};