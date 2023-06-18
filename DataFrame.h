#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
 
using namespace std;

class DataFrameError : public exception {
private:
	string msg;
public:
	DataFrameError(); 
	DataFrameError(string msg_) : msg(msg_) {};
	const char* what() const throw(); 
};

class Fila {
	vector<string> columnas;
	vector<string> vals;

public:
	Fila(); 
	Fila(const vector<string>& cols) : columnas(cols) {};
	int size(); 

	void push(const string& val); 

	bool set(const string& col, const string& val); 

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
	string filename;
public: 
	DataFrame(); 
	int size(); 

	void read_csv(const string filename, const char sep = ','); 

	void addRow(vector<string> data); 

	void save(); 
	Fila getRow(int i); 
	Fila& operator[](int i) { return filas[i]; }

private:
	void parseHeader();

	vector<string> procesarLinea(string linea);

	void parseContenido(); 
};