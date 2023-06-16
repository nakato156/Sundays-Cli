#include "Lista.h" 
#include "DataFrame.cpp"
#include "Producto.h" 
#include <time.h>
using namespace std;
 
float precios[] = { 25.90f, 28.50f, 18.30f, 30.49f, 35.20f, 9.90f }; 

DataFrame cargarDatos()
{
	DataFrame data;
	data.read_csv("comida.csv");
	return data;
}

Lista<Producto> generarMenu(DataFrame data) {
	Lista<Producto> menu;
	for (int i = 0; i < 5; i++) {
		auto fila = data[i];
		menu.push_back(Producto(fila["Id"], fila["Nombre"], fila["Tipo"], precios[i]));
	}
	return menu;
}

void mostrarMenuLista(Lista<Producto>& menu) {
	cout << "Menu de hoy: " << endl;
	cout << "Plato " << "\t\tPrecio" << endl;
	for (int i = 0; i < menu.getSize(); i++) {
		cout << menu.at(i).getNombre() << "\t\t" << menu.at(i).getPrecio() << endl;
	}
	cout << menu.getSize() + 1 << ") Salir " << endl;
}

Lista<Producto> MenuUserV2(DataFrame data) {
	Lista<Producto> lista;
	Lista<Producto> menu = generarMenu(data);

	int eleccion;
	do {
		mostrarMenuLista(menu);
		cin >> eleccion;
		if (eleccion >= 1 && eleccion <= menu.getSize()) {
			lista.push_back(menu.at(eleccion - 1));
		}
	} while (eleccion != menu.getSize() + 1);
	return  lista;
}

//int main()
//{
//	srand(time(NULL)); 
//	Lista<Producto> lista_prod;
//	DataFrame data = cargarDatos();
//	lista_prod = MenuUserV2(data); cout << endl;
//	lista_prod.print();
//	return 0;
//}