#pragma once
#include <iostream>
#include <string>

class Usuario{
	std::string filename = "usuarios.csv";
	std::string email, password, nombre, UUID;
	int rol;
public:
	Usuario();
	std::string getUUID();
	std::string getNombre();
	bool login(std::string email, std::string pass);
	bool registro(std::string email, std::string name, std::string password, int rol);
};