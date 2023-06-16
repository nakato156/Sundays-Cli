#include "Usuario.h"
#include "Crypt.h"
#include "DataFrame.cpp"

using namespace std;

Usuario::Usuario() = default;

string Usuario::getUUID() { return UUID; }
string Usuario::getNombre() { return nombre; }

bool Usuario::login(string email, string pass) {
	DataFrame file;								//usuarios csv						2
	file.read_csv(filename);
	int size = file.size();					//tamanio fila						2
	pass = Cripto::SHA256(pass).toString();		//la contrasea encriptada a string	3
	for (int i = 0; i < size; i++) {			//									1+n(1+intena+2)
		if (file[i]["email"] == email && file[i]["password"] == pass) {	//			7 + maxinterna
			//chequeamos si los datos insertados son iguales a los almacenados
			nombre = file[i]["nombre"];			//3
			UUID = file[i]["uuid"];				//3
			this->email = file[i]["email"];		//4
			password = file[i]["password"];		//3
			rol = stoi(file[i]["rol"]);			//4
			return true;
		}
	}
	return false;
}

bool Usuario::registro(string email, string name, string pass, int rol) {
	try {
		UUID = Cripto::generateUUID();									//generacion del codigo
		DataFrame file;
		file.read_csv(filename);										
		pass = Cripto::SHA256(pass).toString();							
		int size = file.size();											

		vector<string> data = { UUID, email, name, pass };				//se asigna los datos al vector data
		file.addRow(data);												//se agrega a la fila los datos obtenidos
		file.save();													// guarda los datos en el csv de usuarios				

		nombre = name, password = pass;									
		this->email = email;

		return true;
	}
	catch (const DataFrameError& e) {
		std::cout << e.what() << std::endl;								//error si no se pudo hacer el registro
		return false;
	}
}