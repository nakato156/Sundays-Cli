#include <iostream> 
using namespace std;
class Producto {
private:
	int precio = 0;
	string nombre = "";
	string categoria = "";
public:
	Producto() {}
	Producto(string nombre, string categoria, int precio) {
		this->nombre = nombre;
		this->categoria = categoria;
		this->precio = precio;
	}
	~Producto() {}
	string getNombre() { return nombre; }
	string getCategoria() { return categoria; }
	int getPrecio() { return precio; }

	//SOBRECARGAS DE OPERADORES

	//sobrecarga para el ==

	bool operator==(const Producto& otroProducto) const {
		return (precio == otroProducto.precio);
	}

	//sobrecarga para el <
	bool operator<(const Producto& otroProducto) const {
		return precio < otroProducto.precio;
	}
	//sobrecarga para el >
	bool operator>(const Producto& otroProducto) const {
		return precio > otroProducto.precio;
	}
	//sobrecarga para coutear
	friend ostream& operator<<(ostream& os, const Producto& producto) {
		os << producto.nombre << " " << producto.categoria << " " << producto.precio << endl;
		return os;
	}
};