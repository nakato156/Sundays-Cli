#include <string>
#include <iostream>

using namespace std;

class Fecha {
private:
	int dia, mes, anio;

public:
	Fecha() = default;
	//recibe la fecha del CSV por parametro
	Fecha(string fecha) {
		string data[] = { "0", "0", "0" };
		//divide las filas y lo pasa a cada variable correspondiente
		for (int i = 0; i < 3; i++) {
			int index = fecha.find("/"); //que busque el / para poder identificar las fechas y division
			data[i] = fecha.substr(0, index);
			fecha = fecha.substr(index + 1);
		}
		//Intenta la expresion dentro
		try {
			anio = stoi(data[0]);
			mes = stoi(data[1]);
			dia = stoi(data[2]);
		}
		//si hay error entra al catch y manda el mensaje
		catch (const exception&) {
			throw invalid_argument("La fecha no es válida");
		}
	}
	Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

	//SOBRECARGA DE OPERADORES PARA LA CLASE FECHA

	bool operator==(const Fecha& otraFecha) const {
		return (dia == otraFecha.dia && mes == otraFecha.mes && anio == otraFecha.anio);
	}
	bool operator!=(const Fecha& otraFecha) const {
		return !(*this == otraFecha);
	}
	bool operator<(const Fecha& otraFecha) const {
		if (anio < otraFecha.anio)
			return true;
		else if (anio > otraFecha.anio)
			return false;
		else {
			if (mes < otraFecha.mes)
				return true;
			else if (mes > otraFecha.mes)
				return false;
			else
				return (dia < otraFecha.dia);
		}
	}
	bool operator>(const Fecha& otraFecha) const {
		return (otraFecha < *this);
	}

	bool operator<=(const Fecha& otraFecha) const {
		return (*this < otraFecha || *this == otraFecha);
	}

	bool operator>=(const Fecha& otraFecha) const {
		return (*this > otraFecha || *this == otraFecha);
	}
	operator string() const {
		return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
	}
	friend ostream& operator<<(ostream& os, const Fecha& fecha) {
		os << fecha.anio << "/" << fecha.mes << "/" << fecha.dia;
		return os;
	}
};
