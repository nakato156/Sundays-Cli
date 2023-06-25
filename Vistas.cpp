#include "Vistas.h"
#include "Descuento.h"

int Vistas::pagar(HANDLE hConsole, CarritoDeCompras& carrito) {
	system("cls");
	printColoredLine(hConsole, { make_pair("Carrito de compras\n", 6) });
	Lista<Item> productos = carrito;

	for (int i = 0; i < productos.getSize(); i++) {
		int cant = productos.at(i).cant;
		std::cout << cant; gotoxy(10, i + 1);
		std::cout << productos.at(i).producto.getNombre(); gotoxy(30, i + 1);
		std::cout << productos.at(i).producto.getPrecio() * cant << "\n\r";
	}
	std::cout << "-------------------------------------------------\n\r"
		<< "Total\t\t\t" << carrito.total() << "\n\r";
	std::cout << std::endl;

	float total = carrito.total();
	string cod_desc;
	cout << "Ingrese un cupon de descuento: "; cin >> cod_desc;
	if (cod_desc != "\n") {
		Descuento descuento(cod_desc);
		if (!descuento.validar(cod_desc)) 
			cout << "Descuento no válido";
		else {
			total = descuento.aplicar(total);
			cout << "Total: " << total << endl;
		}
	}
	return total;
}