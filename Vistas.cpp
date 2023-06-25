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
			cout << "Descuento no v�lido";
		else {
			total = descuento.aplicar(total);
			cout << "Total: " << total << endl;
		}
	}
	return total;
}

void Vistas::admin(HANDLE hConsole, Admin admin) {
	cout << "1) Ver estadisticas" << endl
		<< "2) Agregar admin" << endl
		<< "3) Ver admins" << endl
		<< "4) Ejecutar test" << endl
		<< "5) Salir";
	gotoxy(0, 0);

	pair<int, int> posicion = selectOpcion(0, 0, 0, 4);
	int opcion = posicion.second + 1;

	if (opcion == 5) exit(EXIT_SUCCESS);
	
	if (opcion == 1) admin.estadisticas();
	else if (opcion == 2) {
		system("cls");
		string nombre, email, pass;
		cout << "Ingrese los datos\n";
		cout << "Nombre: "; cin >> nombre;
		cout << "email: "; cin >> email;
		cout << "pass: "; pass = inputPassword();
		admin.agregarAdmin(email, nombre, pass);
	}
	else if (opcion == 3) admin.verAdmins();
	else if (opcion == 4) admin.test();