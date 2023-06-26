#include "Compra.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Compra::Compra() = default;

Compra::Compra(Usuario& client, const CarritoDeCompras& carrito_) : cliente(client), carrito(carrito_) {};

void Compra::Guardar() {
	DataFrame file;
	file.read_csv(filename);
	UUID = Cripto::generateUUID();	//generamos el codigo de compra

	auto t = std::time(nullptr);
	std::tm tm;
	localtime_s(&tm, &t);	//para saber la hora actual

	// REFERENCIA https://es.stackoverflow.com/questions/32046/mostrar-fecha-y-hora-actual-en-c
	ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");	//para formatear la fecha cada vez que se haga una nueva compra
	fecha = Fecha(oss.str());

	auto row = { UUID, cliente.getUUID(), carrito.exportar(), to_string(carrito.total()), string(fecha) }; //agregar a la fila todos los datos

	file.addRow(row);	//se agrega la fila creada anteriormente
	file.save();		//se agrega todos los datos al archivo
}

Compra Compra::load(ArbolAVL<Producto>& productos, string const data[]) {
	string uuid_cliente = data[1];
	Usuario cliente = Usuario();
	return Compra(cliente, CarritoDeCompras::load(productos, data[2]));
}