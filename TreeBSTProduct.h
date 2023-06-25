#pragma once
#include "ArbolBST.h"
#include "constantes.h"
#include "DataFrame.h"
#include "Producto.h"
using namespace std;

class TreeBSTProduct {
	friend class Test; 
	DataFrame data;  
	ArbolB<Producto>* treeBST;  
public: 
	TreeBSTProduct(){}
	~TreeBSTProduct(){}

	void simulateBSTtree() {
		treeBST = new ArbolB<Producto>; 
		data.read_csv(filenameComida);
		double precio = 0;
		for (int i = 0; i < data.size(); i++) {
			auto fila = data[i];
			Producto producto = Producto(fila["Id"], fila["Nombre"], fila["Tipo"], precio);
			treeBST->insertar(producto);
			//cout << i << "" << producto.getNombre() << " " << producto.getCategoria() << "" << producto.getPrecio() << endl;   
		}
	}
	/*void menuTreeBST() {
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
			treeBST.enOrden();
			break;
		}
		case 2: {
			int precio;
			cout << "Ingrese el precio del producto que desea eliminar: "; cin >> precio;
			treeBST.eliminarNodo(Producto("", "", "", precio));
			break;
		}
		case 3: {
			int precio;
			cout << "Ingrese el precio del producto que desea buscar: "; cin >> precio;
			treeBST.binSearch(Producto("", "", "", precio));
			break;
		}
		case 4: {
			treeBST.obtenerProfundidad();
			break;
		}
		}
	}*/

	void initBST() {
		simulateBSTtree(); 
	}
};