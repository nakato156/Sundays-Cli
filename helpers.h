#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <conio.h>
#include "Lista.h"
using namespace std;

enum class Categoria {
	ENTRADA,
	ENTRANTE,
	ACOMPANAMIENTO,
	PLATO_PRINCIPAL,
	DESAYUNO
};

map<string, Categoria> categorias = {
	{"Entrada", Categoria::ENTRADA},
	{"Entrante", Categoria::ENTRANTE},
	{"Acompanamientos", Categoria::ACOMPANAMIENTO},
	{"Plato principal", Categoria::PLATO_PRINCIPAL},
	{"Desayuno", Categoria::DESAYUNO}
};

struct Plato {
	string codigo;
	string nombre;
	Categoria categoria;

};


Categoria determinarCategoria(const string& categoriaStr) {
	if (categorias.count(categoriaStr) > 0) {
		return categorias[categoriaStr];
	}
	else {
		return Categoria::ENTRADA; // Si no se reconoce la categoría, se devuelve la categoría "Entrada" por defecto
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
	return { "", "", Categoria::ENTRADA }; // Si no se encuentra el plato, se devuelve una entrada vacía con categoría "Entrada"
}
void clasificarPlatos(Lista<Plato>& platosPrincipales, Lista<Plato>& entradas, Lista<Plato>& entrantes, Lista<Plato>& acompanamientos, Lista<Plato>& desayuno) {
	// Leer la información de los platos desde el archivo y clasificarlos en las listas correspondientes
	Lista<Plato> platosTemp;
	ifstream archivo("comida.csv");
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
class GeneradorPrimos {
private:
	int n_primo = 2;
public:
	GeneradorPrimos() = default;
	GeneradorPrimos(int random) {
		/*
		@param random: 0 para generar aleatoriamente, cualquier otro valor para setear el primo
		*/
		if (random == 0) {
			n_primo = next_(2 + rand() % 1000000000);
		}
		else if (esPrimo(random)) n_primo = random;
		else { n_primo = next_(random); }

	}

	class Iterator {
	private:
		int* num_primo;
	public:
		using difference_type = std::ptrdiff_t;

		Iterator() : num_primo(nullptr) {}
		Iterator(int* num) {
			num_primo = num;
		}

		int operator*() const {
			return *num_primo;
		}

		int* operator->() const {
			return num_primo;
		}

		Iterator operator+(difference_type n) {
			int* nuevo_primo = num_primo;
			for (int i = 0; i < n; i++) {
				nuevo_primo = new int(next_(*nuevo_primo));
			}
			return Iterator(nuevo_primo);
		}

		Iterator operator++() {
			num_primo = new int(next_(*num_primo));
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const Iterator& otro) const {
			return num_primo == otro.num_primo;
		}

		bool operator!=(const Iterator& otro) const {
			return !(*this == otro);
		}
	};

	int next() {
		n_primo = next_(n_primo);
		return n_primo;
	}

	int current() { return n_primo; }
	Iterator begin() { return Iterator(new int(n_primo)); }

	friend std::ostream& operator<<(std::ostream& os, const GeneradorPrimos& gen) {
		os << gen.n_primo;
		return os;
	}
private:
	static int next_(int n) {
		while (true) {
			if (esPrimo(++n)) return n;
		}
	}
	static bool esPrimo(int num) {
		if (num <= 1) return false;

		for (int i = 2; i <= sqrt(num); i++) {
			if (num % i == 0) return false;
		}
		return true;
	}

};
#endif