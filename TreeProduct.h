#pragma once
#include "ArbolAVL.h"  
#include "Producto.h"
using namespace std;

class TreeProduct {
	ArbolAVL<Producto>* treeName;
	ArbolAVL<Producto>* treePrecio;
	void(*imprimir)(Producto);
	short(*criterioN)(Producto, Producto); //nombre
	short(*criterioP)(Producto, Producto); //precio
	short(*criterioC)(Producto, Producto); //categoria
public:
	TreeProduct() {
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
		treeName = new ArbolAVL<Producto>(imprimir, criterioN);
		treePrecio = new ArbolAVL<Producto>(imprimir, criterioP);
	}

	void simulateTreeN() {//cambiar al funcionamiento del DATAFRAME
		treeName->Insertar(Producto("23456", "Pollo", "Principal", 29));
		treeName->Insertar(Producto("24656", "Malteada", "Bebida", 39));
		treeName->Insertar(Producto("23956", "Granizado", "Bebida", 32));
		treeName->Insertar(Producto("23236", "Gaseosa", "Bebida", 10));
		treeName->Insertar(Producto("23596", "Cerdo", "Principal", 20));
		treeName->Insertar(Producto("20956", "Pato", "Principal", 35));
	}
	void simulateTreeP() {//cambiar al funcionamiento del DATAFRAME
		treePrecio->Insertar(Producto("23456", "Pollo", "Principal", 29));
		treePrecio->Insertar(Producto("24656", "Malteada", "Bebida", 39));
		treePrecio->Insertar(Producto("23956", "Granizado", "Bebida", 32));
		treePrecio->Insertar(Producto("23236", "Gaseosa", "Bebida", 10));
		treePrecio->Insertar(Producto("23596", "Cerdo", "Principal", 20));
		treePrecio->Insertar(Producto("20956", "Pato", "Principal", 35));
	}

	void menuArboles(ArbolAVL<Producto>* tree) {
		int seleccion;
		cout << "Ingrese la opcion que desee realizar: " << endl;
		cout << "1) Impresion inOrden de elementos: " << endl;
		cout << "2) Esta balanceado el arbol? " << endl;
		cout << "3) Es un arbol AVL? " << endl;
		cout << "4) El arbol es perfecto? " << endl;
		cout << "5) El arbol esta completo? " << endl;
		cout << "6) Buscar " << endl; 
		cout << "7) Ejecturar Tests " << endl; 
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
		case 7: {
			//ACA VA LA CLASE TEST
			cout << "TEST" << endl;
			break;
		}
		}
	}

	void init() {
		int eleccion;
		cout << "Con que arbol desea trabajar? " << endl;
		cout << "1) Arbol insertado por precio: " << endl;
		cout << "2) Arbol insertado por nombre: " << endl; cin >> eleccion;
		if (eleccion == 1) {
			menuArboles(treePrecio);
		}
		else { menuArboles(treeName); }
	}
};