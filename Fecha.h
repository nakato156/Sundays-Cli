#include <string>
#include <iostream>
#ifndef FECHA_H
#define FECHA_H
using namespace std;

class Fecha {
private:
	int dia, mes, anio;
	int hora, minuto, seg;
public:
	Fecha() = default;
	//recibe la fecha del CSV por parametro
	Fecha(string fecha) {
		string data[] = { "0", "0", "0", "0", "0", "0" };
		for (int i = 0; i < 3; i++) {
			int index = fecha.find("/");
			data[i] = fecha.substr(0, index);
			fecha = fecha.substr(index + 1);
		}

		for (int i = 0; i < 3; i++) {
			int index = fecha.find(":");
			data[i + 3] = fecha.substr(0, index);
			fecha = fecha.substr(index + 1);
		}

		try {
			anio = stoi(data[0]);
			mes = stoi(data[1]);
			dia = stoi(data[2]);

			hora = stoi(data[3]);
			minuto = stoi(data[4]);
			seg = stoi(data[5]);
		}
		catch (const exception&) {
			throw invalid_argument("La fecha no es válida");
		}
	}

	Fecha(int d, int m, int a, int H, int M, int S) : dia(d), mes(m), anio(a), hora(H), minuto(M), seg(S) {};

	operator string() const {
		return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio) + " "
			+ to_string(hora) + ":" + to_string(minuto) + ":" + to_string(seg);
	}

	friend ostream& operator<<(ostream& os, const Fecha& fecha) {
		os << fecha.anio << "/" << fecha.mes << "/" << fecha.dia <<
			" " << fecha.hora << ":" << fecha.minuto << ":" << fecha.seg;
		return os;
	}
};
#endif