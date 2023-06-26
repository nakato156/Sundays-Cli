#include "DataFrame.h" 
using namespace std;

//DataFrameError
DataFrameError::DataFrameError() = default; 
DataFrameError::DataFrameError(string msg_) : msg(msg_){}
const char* DataFrameError::what() const throw() {
	return msg.c_str();
}

//Fila
Fila::Fila() = default;
Fila::Fila(const vector<string>& cols) : columnas(cols) {}; 
int Fila::size() { return columnas.size(); }
void Fila::push(const string& val) { vals.push_back(val); }
bool Fila::set(const string& col, const string& val) {
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


//DataFrame
DataFrame::DataFrame() = default; 
int DataFrame::size() { return length; } 

void DataFrame::read_csv(const string filename, const char sep){
	separador = sep; 
	this->filename = filename; 
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

void DataFrame::addRow(vector<string> data) {
	if (data.size() != columnas.size()) 
		throw DataFrameError("La columna agregada no tiene el tamano adecuado"); //error 
	
	Fila nueva_fila = Fila(columnas); 
	for (auto campo : data)
		nueva_fila.push(campo); 
	filas.push_back(nueva_fila);
	length++;
}

void DataFrame::save() {
	ofstream archivo(filename); 
	if (!archivo.is_open()) throw DataFrameError("No se pudo guardar el archivo");
	//para el header
	for (int c = 0; c < columnas.size(); c++)
		archivo << columnas[c] << (c + 1 == columnas.size() ? '\n' : separador);

	for (int i = 0; i < length; i++) { 
		Fila fila = filas[i]; 
		//para el contenido
		for (int c = 0; c < fila.size(); c++) {
			cout << fila[c] << endl;
			archivo << fila[c] << (c + 1 == fila.size() ? '\n' : separador);
		}
	}
}

Fila DataFrame::getRow(int i) { return filas[i]; }  

void DataFrame::parseHeader() { 
	auto it = data.begin();  
	vector<string> header = procesarLinea(*it); 
	this->columnas = header; 
}
vector<string> DataFrame::procesarLinea(string linea) {
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
void DataFrame::parseContenido() {
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