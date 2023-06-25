#include "helpers.h"


MapadeCate clasificarPlatos() {
	MapadeCate categoriasPlatos; // Mapa para almacenar las listas de platos por categoría

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
Categoria buscarCategoriaPorCodigo(const MapadeCate& categoriasPlatos, const string& codigo) {
	for (const auto& categoria : categoriasPlatos) {
		const Lista<Producto>& listaPlatos = categoria.second;
		for (const Producto& plato : listaPlatos) {
			if (plato.getCodigo() == codigo) {
				return categoria.first;  // Se encontró el plato, se devuelve la categoría
			}
		}
	}
}

string inputPassword() {
	char caracter;
	string password;
	while (true) {
		caracter = _getch();
		if (caracter == ENTER) break;
		if (caracter != BACKSPACE) {
			password.push_back(caracter);
			cout << "*";
		}
		else if (caracter == BACKSPACE && password.length() > 0) {
			cout << "\b \b";
			password.pop_back();
		}
	}
	return password;
}

void printSelectLine(const HANDLE hConsole, const vector<string> lineas, const int selectedLine, const WORD color) {
	for (int i = 0; i < lineas.size(); i++) {
		if(i == selectedLine) SetConsoleTextAttribute(hConsole, color);
		cout << lineas.at(i) << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
}
void printColoredLine(const HANDLE hConsole, const vector<pair<string, WORD>> lineas) {
	for (int i = 0; i < lineas.size(); i++) {
		SetConsoleTextAttribute(hConsole, lineas.at(i).second);
		cout << lineas.at(i).first << endl;
		SetConsoleTextAttribute(hConsole, 7);
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
		case ABAJO:
			return TECLA::K_ABAJO;
		case IZQR:
			return TECLA::k_IZQ;
		case DERECHA:
			return TECLA::K_DER;
		case ENTER:
			return TECLA::K_ENTER;
		case BACKSPACE:
			return TECLA::K_BACKSPACE;
		default:
			break;
		}
	}
}

pair<int, int> selectOpcion(int min_x, int max_x, int min_y, int max_y) {
	int x = 0, y = 0;

	while (true) {
		TECLA tecla = getTecla();
		if (tecla == TECLA::K_ABAJO && y + 1 < max_y) y++;
		else if (tecla == TECLA::K_ARRIBA && y - 1 >= min_y) y--;
		else if (tecla == TECLA::K_DER && x + 1 < max_x) x++;
		else if (tecla == TECLA::k_IZQ && x - 1 > min_x) x++;
		else if (tecla == TECLA::K_ENTER) return make_pair(x, y);
		gotoxy(x, y);
	}
}