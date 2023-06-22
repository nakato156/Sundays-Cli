#pragma once
#include <Windows.h>
#include "Login.h"
#include "Registro.h"

class App : virtual public Login, virtual public Registro {
	HANDLE hConsole;
	void mostrarOpciones(HANDLE, int select = 0);
public:
	App() = default;
	App(HANDLE hConsole_, Usuario& user) : hConsole(hConsole_), Login(user), Registro(user) {};
	void init();
};