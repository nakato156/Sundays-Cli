#include "Carrito.h"
#include <sstream>
using namespace std;

CarritoDeCompras::CarritoDeCompras() = default;

CarritoDeCompras CarritoDeCompras::load(Lista<Producto>& productos, string data) { // para leer el historial y generar el carrito de compras
	istringstream iss(data);
	string linea;
	CarritoDeCompras carrito;
	while (getline(iss, linea, ';')) {		//separe cada linea hasta que encuentre un ;
		stringstream ss(linea);

		string codigo, cant_str;
		getline(ss, codigo, '/');			//guardar el codigo el texto hasta /
		getline(ss, cant_str);				//guardar la cantidad el texto restante

		int cant = stoi(cant_str);			//convertir el string cantidad a int
		Producto producto = productos.buscador([codigo](Producto prod) -> bool { return prod.getCodigo() == codigo; });
		//buscar el producto por su codigo y que nos retorne todo el producto
		carrito.agregar(Item{ producto, cant }); //agregar dicho producto al carrito
	}
	return carrito;
}

void CarritoDeCompras::agregar(const Item& item) {//agregar
	productos.push_back(item);
}

void CarritoDeCompras::agregar(const Producto& prod) { //const hace que el objeto no cambie su valor
	Item item{ prod, 1 };
	auto res = productos.find(item, [](Item& elemento, Item& buscado) {
		return elemento.producto.getCodigo() == buscado.producto.getCodigo();
	});
	if (res == productos.end())
		productos.push_back(item);
	else 
		(*res).cant++;
}

void CarritoDeCompras::eliminarProd(const Producto& prod) {      //eliminar producto
	Item item{ prod };
	auto res = productos.find(item, [](Item& elemento, Item& buscado) {
		return elemento.producto.getCodigo() == buscado.producto.getCodigo();
	});
	//if (res != productos.end()) {
	//	if (res->cant == 1)
	//		productos.remove(item);
	//	else res->cant--;
	//}
}

float CarritoDeCompras::total() const {				//retornar la suma de montos de los productos en el carrito
	int size = productos.getSize();
	float monto_total = 0;
	for (int i = 0; i < size; i++)
		monto_total += productos.at(i).cant * productos.at(i).producto.getPrecio();
	return monto_total;
}

string CarritoDeCompras::exportar() {									//exportar los datos del carrito
	int size = productos.getSize();
	string data;
	for (int i = 0; i < size; i++) {
		Item item = productos.at(i);
		Producto prod = item.producto;
		data += prod.getCodigo() + "/" + to_string(item.cant) + ";";
	}
	return data;
}