#pragma once
#include "ArbolBST.h"
#include "Producto.h"
using namespace std;

class TreeBSTProduct {
	ArbolB<Producto>* treeBST;  
public:
	TreeBSTProduct(){}
	~TreeBSTProduct(){}

	void simulateBSTtree() {
		treeBST->insertar(Producto("23456", "Pollo", "Principal", 29));
		treeBST->insertar(Producto("24656", "Malteada", "Bebida", 39)); 
		treeBST->insertar(Producto("23956", "Granizado", "Bebida", 32)); 
		treeBST->insertar(Producto("23236", "Gaseosa", "Bebida", 10));
		treeBST->insertar(Producto("23596", "Cerdo", "Principal", 20)); 
		treeBST->insertar(Producto("20956", "Pato", "Principal", 35)); 
	}

	void menuTreeBST() {
		int eleccion;
		cout << "Ingrese la opcion que desee realizar: " << endl; 
		cout << "1) Impresion inOrden de elementos: " << endl;
		cout << "2) Quiero eliminar un nodo" << endl; 
		cout << "3) Quiero buscar un nodo" << endl; 
		cout << "4) Quiero saber la profundidad " << endl; 
		cin >> eleccion; 
		switch (eleccion) 
		{
		case 1: {
			treeBST->enOrden();  
			break;
		}
		case 2: {
			int precio;  
			cout << "Ingrese el precio del producto que desea eliminar: "; cin >> precio; 
			treeBST->eliminarNodo(Producto("","","", precio));  
			break; 
		}
		case 3: {
			int precio; 
			cout << "Ingrese el precio del producto que desea buscar: "; cin >> precio;
			treeBST->binSearch(Producto("", "", "", precio));  
			break; 
		}
		case 4: {
			treeBST->obtenerProfundidad(); 
			break; 
		}
		}
	}
	void initBST() {
		simulateBSTtree(); 
		menuTreeBST(); 
	}
};