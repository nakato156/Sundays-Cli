#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Fila {
	vector<string> columnas;
	vector<string> vals;

public:
	Fila() = default;
	Fila(const vector<string>& cols) : columnas(cols) {};
	int size() { return columnas.size(); }
	void push(const string& val) { vals.push_back(val); }
	bool set(const string& col, const string& val) {
		int pos = 0;
		for (auto it = columnas.begin(); it != columnas.end(); it++) {
			if (col == *it) {
				vals[pos] = val;
				return true;
			}
			pos++;
		}
		return false;
	}

	string operator[](const string col) const {
		auto it = columnas.begin();
		int pos = 0;

		for (; it != columnas.end(); it++) {
			if (col == *it)
				return vals[pos];
			pos++;
		}
	}

	const string operator[](unsigned int valuePosition) const {
		if (valuePosition < vals.size())
			return vals[valuePosition];
	}

	friend ostream& operator<<(ostream& os, Fila fila) {
		for (int i = 0; i < fila.size(); i++) {
			os << fila.columnas[i] << ": " << fila[i] << endl;
		}
		return os;
	}
};

class DataFrame {
	vector<string> columnas;
	vector<Fila> filas;
	vector<string> data;
	char separador = ',';
	int length = 0;

public:
	DataFrame() = default;
	int size() { return length; }
	void read_csv(const string filename, const char sep = ',') {
		separador = sep;
		ifstream archivo(filename);

		if (!archivo.is_open()) {
			cerr << "No se pudo leer el archivo" << endl;
			return;
		}

		string linea;
		while (getline(archivo, linea)) {
			if (linea != "") {
				data.push_back(linea);
				length++;
			}
		}
		archivo.close();

		parseHeader();
		length--;
		parseContenido();
	}

	Fila getRow(int i) const { return filas[i]; }
	Fila& operator[](int i) { return filas[i]; }

private:
	void parseHeader() {
		auto it = data.begin();
		vector<string> header = procesarLinea(*it);
		this->columnas = header;
	}

	vector<string> procesarLinea(string linea) {
		vector<string> fila;
		int pos;
		while ((pos = linea.find(separador)) != string::npos) {
			string campo = linea.substr(0, pos);
			fila.push_back(campo);
			linea.erase(0, pos + 1);
		}
		fila.push_back(linea);
		return fila;
	}

	void parseContenido() {
		auto it = data.begin();
		it++;
		for (; it != data.end(); it++) {
			string linea = *it;
			Fila fila(columnas);
			auto row = procesarLinea(linea);
			for (auto campo : row)
				fila.push(campo);

			filas.push_back(fila);
		}
	}
};