#include "Usuario.h"
#include "Crypt.h"
#include "CSVparser.hpp"

using namespace std;

Usuario::Usuario() = default;

string Usuario::getUUID() { return UUID; }
string Usuario::getNombre() { return nombre; }

bool Usuario::login(string email, string pass) {
	csv::Parser file = csv::Parser(filename);	//usuarios csv						2
	int size = file.rowCount();					//tamanio fila						2
	pass = Cripto::SHA256(pass).toString();		//la contrasea encriptada a string	3
	for (int i = 0; i < size; i++) {			//									1+n(1+intena+2)
		if (file[i]["email"] == email && file[i]["password"] == pass) {	//			7 + maxinterna
			//chequeamos si los datos insertados son iguales a los almacenados
			nombre = file[i]["nombre"];			//3
			UUID = file[i]["uuid"];				//3
			this->email = file[i]["email"];		//4
			password = file[i]["password"];		//3
			rol = file[i]["rol"];				//3
			return true;
		}
	}
	return false;
}

bool Usuario::registro(string email, string name, string pass, int rol) {
	try {
		UUID = Cripto::generateUUID();									//generacion del codigo
		csv::Parser file = csv::Parser(filename);						//usuarios csv
		pass = Cripto::SHA256(pass).toString();							//contrasenia a string
		int size = file.rowCount();										//tamanio filas del archiv

		vector<string> data = { UUID, email, name, pass };				//se asigna los datos al vector data
		file.addRow(size, data);										//se agrega a la fila los datos obtenidos
		file.sync();													// guarda los datos en el csv de usuarios				

		nombre = name, password = pass;									//asignamos valores a variables
		this->email = email;

		return true;
	}
	catch (const csv::Error& e) {
		std::cout << e.what() << std::endl;								//error si no se pudo hacer el registro
		return false;
	}
}