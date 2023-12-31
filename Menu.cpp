#include "Menu.h"

using namespace std; 

Menu::Menu() = default; 
Menu::~Menu() = default;  

DataFrame Menu::cargarDatos() {    
	data.read_csv(filenameComida);
	return data;
} 
Lista<Producto> Menu::generarMenu(DataFrame data) {
	Lista<Producto> menu;
	for (int i = 0; i < 5; i++) {
		auto fila = data[i];
		menu.push_back(Producto(fila["Id"], fila["Nombre"], fila["Tipo"], precios[i]));
	}
	return menu;
 }
void Menu::mostrarMenuLista(Lista<Producto>& menu) {
	cout << "Menu de hoy: " << endl;
	cout << "Plato " << "\t\t\t\tCategoria" << "\t\tPrecio" << endl;
	for (int i = 0; i < menu.getSize(); i++) {
		cout << i + 1 << ") " << menu.at(i).getNombre() << "\t\t\t" << menu.at(i).getCategoria() << "\t\t" << menu.at(i).getPrecio() << endl;
	}
	cout << menu.getSize() + 1 << ") Salir " << endl;
}
int Menu::selectOpcion() {
	int x = 0, y = this->coordenadas.Y != 0 ? this->coordenadas.Y : 2;
	_gotoxy(x, y);
	while (true) {
		int key = _getch();

		switch (key) {
		case ARRIBA:
			y - 1 < 2 ? 0 : y--;
			break;
		case ABAJO:
			y + 1 > 7 ? 0 : y++;
			break;
		case ENTER:
			return y - 1;
			break;
		default:
			break;
		}
		_gotoxy(x, y);
	}
}

CarritoDeCompras Menu::MenuUserV2(DataFrame data) {
	CarritoDeCompras lista;
	Lista<Producto> menu = generarMenu(data);

	int eleccion;
	mostrarMenuLista(menu);
	do {
		eleccion = selectOpcion();
		if (eleccion >= 1 && eleccion <= menu.getSize()) {
			lista.agregar(menu.at(eleccion - 1));
		}
	} while (eleccion != menu.getSize() + 1);
	return  lista;
}
void Menu::initMenu(CarritoDeCompras& carrito) {
	data = cargarDatos();
	list_prod = MenuUserV2(data); cout << endl;
	carrito = list_prod;
}
