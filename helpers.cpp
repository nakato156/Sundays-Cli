#include "helpers.h"

map<string, Categoria> categorias = {
	{"Entrada", Categoria::ENTRADA},
	{"Entrante", Categoria::ENTRANTE},
	{"Acompanamientos", Categoria::ACOMPANAMIENTO},
	{"Plato principal", Categoria::PLATO_PRINCIPAL},
	{"Desayuno", Categoria::DESAYUNO}
};

Categoria determinarCategoria(const string& categoriaStr) {
	if (categorias.count(categoriaStr) > 0) {
		return categorias[categoriaStr];
	}
	else {
		return Categoria::ENTRADA; // Si no se reconoce la categor�a, se devuelve la categor�a "Entrada" por defecto
	}
}
Plato buscarPlatoPorCodigo(const string& codigo, const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	string linea;

	while (getline(archivo, linea)) {
		stringstream ss(linea);
		string platoCodigo, platoNombre, categoriaStr;
		if (getline(ss, platoCodigo, ',') && getline(ss, platoNombre, ',') && getline(ss, categoriaStr, ',')) {
			if (platoCodigo == codigo) {
				archivo.close();
				return { platoCodigo, platoNombre, determinarCategoria(categoriaStr) };
			}
		}
	}

	archivo.close();
	return { "", "", Categoria::ENTRADA }; // Si no se encuentra el plato, se devuelve una entrada vac�a con categor�a "Entrada"
}
void clasificarPlatos(Lista<Plato>& platosPrincipales, Lista<Plato>& entradas, Lista<Plato>& entrantes, Lista<Plato>& acompanamientos, Lista<Plato>& desayuno) {
	// Leer la informaci�n de los platos desde el archivo y clasificarlos en las listas correspondientes
	Lista<Plato> platosTemp;
	ifstream archivo(filenameComida);
	string linea;

	while (getline(archivo, linea)) {
		stringstream ss(linea);
		string platoCodigo, platoNombre, categoriaStr;
		if (getline(ss, platoCodigo, ',') && getline(ss, platoNombre, ',') && getline(ss, categoriaStr, ',')) {
			Categoria categoria = determinarCategoria(categoriaStr);
			platosTemp.push_back({ platoCodigo, platoNombre, categoria });
		}
	}

	archivo.close();

	for (const Plato& plato : platosTemp) {
		switch (plato.categoria) {
		case Categoria::PLATO_PRINCIPAL:
			platosPrincipales.push_back(plato);
			break;
		case Categoria::ENTRADA:
			entradas.push_back(plato);
			break;
		case Categoria::ENTRANTE:
			entrantes.push_back(plato);
			break;
		case Categoria::ACOMPANAMIENTO:
			acompanamientos.push_back(plato);
			break;

		case Categoria::DESAYUNO:
			desayuno.push_back(plato);
			break;
		}
	}

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