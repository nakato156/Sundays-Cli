#include "helpers.h"


map<string, Lista<Producto>> clasificarPlatos() {
	map<string, Lista<Producto>> categoriasPlatos; // Mapa para almacenar las listas de platos por categoría

	ifstream archivo("comida.csv");
	string linea;

	while (getline(archivo, linea)) {
		stringstream ss(linea);
		string platoCodigo, platoNombre, categoriaStr;
		if (getline(ss, platoCodigo, ',') && getline(ss, platoNombre, ',') && getline(ss, categoriaStr, ',')) {
			Producto plato{ platoCodigo, platoNombre,categoriaStr, };

			// Verificar si la categoría ya existe en el mapa, si no, se crea una nueva lista para esa categoría
			if (categoriasPlatos.count(categoriaStr) == 0) {
				categoriasPlatos[categoriaStr] = Lista<Producto>();
			}

			categoriasPlatos[categoriaStr].push_back(plato);
		}
	}

	archivo.close();
	return categoriasPlatos;


}

void gotoxy(int x, int y, COORD& coords) {
	coords.X = x;
	coords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}
void gotoxy(int x, int y) {
	COORD coords{x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}

TECLA getTecla() {
	while (true) {
		int key = _getch();

		switch (key) {
		case ARRIBA:
			return TECLA::K_ARRIBA;
			break;
		case ABAJO:
			return TECLA::K_ABAJO;
			break;
		case IZQR:
			return TECLA::k_IZQ;
		case DERECHA:
			return TECLA::K_DER;
		case ENTER:
			return TECLA::K_ENTER;
			break;
		default:
			break;
		}
	}
}