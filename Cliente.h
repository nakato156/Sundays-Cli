#pragma once
#include <iostream>
#include <string>

class Cliente {
	std::string filename = "usuarios.csv";
	std::string email, password, nombre, UUID;
public:
	Cliente();
	std::string getUUID();
	std::string getNombre();
	bool login(std::string email, std::string pass);
	bool registro(std::string email, std::string name, std::string password);
};