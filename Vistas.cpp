#include "Vistas.h"


void Vistas::ingresarReclamo(HANDLE hConsole) {
	system("cls");
	printColoredLine(hConsole, { {"Ingresar reclamo\n", 14} });
	std::string reclamo;
	//std::getline(std::cin, reclamo); no permite leer los datos ingresados por el ususario
	cin >> reclamo;//bug en el getline , no funciona si le ponemos getline solo con el cin
	Mensaje mensaje;
	mensaje.guardarReclamo(reclamo);
}
void Vistas::pagar(HANDLE hConsole, CarritoDeCompras& carrito, Usuario& usuario) {
	system("cls");
	printColoredLine(hConsole, { make_pair("Carrito de compras\n", 6) });
	Lista<Item> productos = carrito;

	for (int i = 0; i < productos.getSize(); i++) {
		int cant = productos.at(i).cant;
		std::cout << "\r" << cant; gotoxy(10, i + 1);
		std::cout << productos.at(i).producto.getNombre(); gotoxy(50, i + 1);
		std::cout << productos.at(i).producto.getPrecio() * cant << "\n\r";
	}
	std::cout << "-------------------------------------------------\n\r"
		<< "Total\t\t\t" << carrito.total() << "\n\r\n";

	float total = carrito.total();
	if (!total) return;

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
	Compra compra(usuario, carrito);
	compra.Guardar();
}

void Vistas::admin(HANDLE hConsole, Admin admin) {
	cout << "1) Ver estadisticas" << endl
		<< "2) Agregar admin" << endl
		<< "3) Ver admins" << endl
		<< "4) Ejecutar test" << endl
		<< "5) Salir";
	gotoxy(0, 0);

	pair<int, int> posicion = selectOpcion(0, 0, 0, 5,1);
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
}

void Vistas::historial(HANDLE hConsole, Usuario& usuario, ArbolAVL<Producto>& productos) {
	HistorialCompras historial;
	historial.load(productos, usuario);

	printColoredLine(hConsole, { {"Historial de compras\n", 10} });

}