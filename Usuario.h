#pragma once
#include "Crypt.h"
#include <iostream>
#include <string>

class Usuario{
	std::string filename = "usuarios.csv";
	std::string email, password, nombre, UUID;
	int rol = -1;
public:
	Usuario();
	Usuario(string uuid, string name, string email_) : UUID(uuid), nombre(name), email(email_) {};
	std::string getUUID();
	std::string getNombre();
	bool isLogged();
	bool isAdmin();
	bool login(std::string email, std::string pass);
	bool registro(std::string email, std::string name, std::string password, int rol);
};