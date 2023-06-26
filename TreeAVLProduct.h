#pragma once
#include "ArbolAVL.h"
#include "Producto.h"
#include "DataFrame.h" 
#include "constantes.h" 
#include <fstream>
#include <sstream>
using namespace std;

class TreeAVLProduct {
	friend class Test;
	ArbolAVL<Producto> treeName;
	ArbolAVL<Producto> treePrecio;
	DataFrame data;
	void(*imprimir)(Producto);
	short(*criterioN)(Producto, Producto); //nombre
	short(*criterioP)(Producto, Producto); //precio
	short(*criterioC)(Producto, Producto); //categoria
public:
	TreeAVLProduct() { 
		imprimir = [](Producto p)->void {cout << p.getNombre() << "\t" << p.getCategoria() << "\t" << p.getPrecio() << endl;  };
		criterioN = [](Producto a, Producto b) ->short {
			if (a.getNombre().compare(b.getNombre()) < 0) return -1;
			else if (a.getNombre().compare(b.getNombre()) > 0) return 1;
			else return 0; };
		criterioC = [](Producto a, Producto b)->short {
			if (a.getCategoria().compare(b.getCategoria()) < 0) return -1;
			else if (a.getCategoria().compare(b.getCategoria()) > 0) return -1;
			else return 0;
		};
		criterioP = [](Producto a, Producto b)-> short {
			if (a.getPrecio() < b.getPrecio()) return -1;
			else if (a.getPrecio() > b.getPrecio()) return 1;
			else return 0;
		};
		treeName = ArbolAVL<Producto>(imprimir, criterioN);
		treePrecio = ArbolAVL<Producto>(imprimir, criterioP);
	}

	void simulateTreeN() {
		data.read_csv(filenameComida);
		for (int i = 0; i < data.size(); i++) {
			auto fila = data[i];
			treeName.Insertar(Producto(fila["Id"], fila["Nombre"], fila["Tipo"], stof(fila["precio"])));
		}
	}
	void simulateTreeP() {//cambiar al funcionamiento del DATAFRAME
		DataFrame data2;
		data2.read_csv(filenameComida);  
		for (int i = 0; i < data2.size(); i++) { 
			auto fila = data2[i]; 
			treePrecio.Insertar(Producto(fila["Id"], fila["Nombre"], fila["Tipo"], stof(fila["precio"])));
		}
	}

	void menuArbolAVL(ArbolAVL<Producto>* tree) {
		int seleccion;
		cout << "Ingrese la opcion que desee realizar: " << endl;
		cout << "1) Impresion inOrden de elementos: " << endl;
		cout << "2) Esta balanceado el arbol? " << endl;
		cout << "3) Es un arbol AVL? " << endl;
		cout << "4) El arbol es perfecto? " << endl;
		cout << "5) El arbol esta completo? " << endl;
		cout << "6) Buscar " << endl; 
		cin >> seleccion;
		switch (seleccion) {
		case 1: {
			cout << "Impresion en orden de elementos: " << endl;
			tree->inOrden(); cout << endl;
			break;
		}
		case 2: {
			tree->isBalance();
			break;
		}
		case 3: {
			tree->isAVL();
			break;
		}
		case 4: {
			tree->isPerfect();
			break;
		}
		case 5: {
			tree->isComplete();
			break;
		}
		case 6: {
			int tipo;
			cout << "1) Buscar por nombre: " << endl;
			cout << "2) Buscar por categoria: " << endl;
			cout << "3) Buscar por precio: " << endl;
			cin >> tipo;
			if (tipo == 1) {
				string nombre{};
				cout << "Ingrese el nombre del producto: " << endl;
				cin.ignore();
				getline(cin, nombre);
				transform(nombre.begin(), nombre.end(), nombre.begin(), ::toupper);
				auto resultado = tree->busqueda([&nombre](Producto producto) {return producto.getNombre() == nombre; });
				if (resultado == nullptr) cout << "No se encontraron coincidencias" << endl;
				else { cout << resultado->elemento.getNombre() << " " << resultado->elemento.getCategoria() << " " << resultado->elemento.getPrecio() << endl; }
			}
			else if (tipo == 2) {
				string cat{};
				cout << "Ingrese la categoria que desee buscar: " << endl;
				cin.ignore();
				getline(cin, cat);
				transform(cat.begin(), cat.end(), cat.begin(), ::toupper);
				auto resultado = tree->busqueda([&cat](Producto producto) {return producto.getCategoria() == cat; });
				if (resultado == nullptr) cout << "No se encontraron coincidencias" << endl;
				else cout << resultado->elemento.getNombre() << " " << resultado->elemento.getCategoria() << " " << resultado->elemento.getPrecio() << endl;
			}
			else {
				int precio;
				cout << "Ingrese su precio a buscar: " << endl; cin >> precio;
				auto resultado = tree->busqueda([&precio](Producto producto) {return producto.getPrecio() == precio; });
				if (resultado == nullptr) cout << "No se encontraron coincidencias" << endl;
				else cout << resultado->elemento.getNombre() << " " << resultado->elemento.getCategoria() << " " << resultado->elemento.getPrecio() << endl;
			}
			break;
		}
		}
	}

	void init() {
		simulateTreeP(); 
		simulateTreeN(); 
	}
};