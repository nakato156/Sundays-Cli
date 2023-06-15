#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <functional>
#include <algorithm>
#include "Producto.h"
using namespace std;

template<class T>

class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	int altura;

	Nodo() {
		izq = nullptr;
		der = nullptr;
		altura = 0;
	}
	~Nodo() {}
};

template<class T, class K>

class ArbolAVL {
private:
	Nodo<T>* raiz;
	short (*comparar)(T, T);//puntero a funci�n- en vez de utilizar un functor
	void(*procesar)(T); //puntero a funci�n
	void(*procesar2)(K); //puntero a funci�n 

	int _altura(Nodo<T>* nodo) {
		if (nodo == nullptr) return -1;
		return nodo->altura;
	}

	void _actualizarAltura(Nodo<T>* nodo) {
		if (nodo != nullptr) {
			int hizq = _altura(nodo->izq);
			int hder = _altura(nodo->der);
			nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
		}
	}

	void _rotarDerecha(Nodo<T>*& nodo) {
		Nodo<T>* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		//Actualizamos la altura
		_actualizarAltura(nodo);
		nodo = p;
		_actualizarAltura(nodo);
	}

	void _rotarIzquierda(Nodo<T>*& nodo) {

		Nodo<T>* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		//Actualizamos la altura
		_actualizarAltura(nodo);
		nodo = p;
		_actualizarAltura(nodo);
	}

	void _balanceo(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;

		if (fb > 1) { //rotar a la izq
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotaci�n
				_rotarDerecha(nodo->der);
			}
			_rotarIzquierda(nodo);
		}

		else if (fb < -1) { //rotar a la der
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) {//verificar si aplica doble rotaci�n 
				_rotarIzquierda(nodo->izq);
			}
			_rotarDerecha(nodo);
		}
		else _actualizarAltura(nodo);
	}

	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			//Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else if (comparar(e, nodo->elemento) == 0) {
			_insertar(nodo->der, e);
		}
		else if (comparar(e, nodo->elemento) == -1) {
			_insertar(nodo->izq, e);
		}
		else if (comparar(e, nodo->elemento) == 1) {
			_insertar(nodo->der, e);
		}
		_balanceo(nodo);
		return true;
	}

	void _inOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrden(nodo->izq);
		procesar(nodo->elemento);
		_inOrden(nodo->der);
	}

	void _inOrdenH(Nodo<T>* nodo) {

		if (nodo == nullptr) return;
		_inOrdenH(nodo->izq);
		procesar2(nodo->altura);
		_inOrdenH(nodo->der);
	}

	int _obtenerBalance(Nodo<T>* nodo) {
		if (nodo == nullptr) return 0;
		return _altura(nodo->der) - _altura(nodo->izq);
	}

	bool _isBalance(Nodo<T>* nodo) {
		if (nodo == nullptr) return true;
		int valorBalance = _obtenerBalance(nodo);
		if (valorBalance > 1 || valorBalance < -1) return false;
		return _isBalance(nodo->der) && _isBalance(nodo->izq);
	}

	void _isAVL() {
		bool valor = _isBalance(raiz);
		if (valor == true) cout << "Es un arbol AVL" << endl;
		else cout << "No es un Arbol ALV" << endl;
	};

	int _obtenerAltura(Nodo<T>* nodo) {
		if (nodo == nullptr) return 0;
		int alturaIzq = _altura(nodo->izq);
		int alturaDer = _altura(nodo->der);
		return max(alturaIzq, alturaDer) + 1; //se le suma uno para contar el nivel 0 o la raiz  
	}

	int _contadorNodos(Nodo <T>* nodo) {
		if (nodo == nullptr) return 0;
		return _contadorNodos(nodo->izq) + _contadorNodos(nodo->der) + 1; //se le suma uno por la raiz
	}

	bool _isPerfect(Nodo<T>* nodo) {
		int alturaArbol = _obtenerAltura(nodo);
		int nodos = _contadorNodos(nodo);
		int nodosEsperados = pow(2, alturaArbol) - 1;          //formula matematica para hallar los nodos esperados de un arbol 
		return nodos == nodosEsperados;
	}

	void _isComplete() {
		bool completo = _isPerfect(raiz);
		if (completo == true) cout << "Es un arbol completo" << endl;
		else cout << "No es un arbol completo" << endl;
	}

	Nodo<T>* _busqueda(Nodo<T>* nodo, function <bool(T)>condition) {
		if (nodo == nullptr) return nullptr;
		if (condition(nodo->elemento)) return nodo;
		else if (condition(nodo->elemento)) { return _busqueda(nodo->izq, condition); }
		else return _busqueda(nodo->der, condition);
	}

public:
	ArbolAVL(void(*nuevaFuncion)(T), void(*Funcion2)(K), short(*Comparador)(T, T)) {
		this->procesar = nuevaFuncion;
		this->procesar2 = Funcion2;
		this->comparar = Comparador;
		this->raiz = nullptr;
	}
	int altura() { return _altura(raiz); }

	bool Insertar(T e) { return _insertar(raiz, e); }

	void inOrden() { _inOrden(raiz); }

	void inOrdenH() { _inOrdenH(raiz); }

	int obtenerBalance(Nodo<T>* nodo) { return _obtenerBalance(nodo); }

	void  isBalance() {
		bool answer = _isBalance(raiz);
		if (answer == true) cout << "Esta balanceado" << endl;
		else cout << "No esta balanceado" << endl;
	}

	void isAVL() { _isAVL(); }

	int obtenerAltura() { return _obtenerAltura(raiz); }

	int contadorNodos() { return _contadorNodos(raiz); }

	void isPerfect() {
		bool perfect = _isPerfect(raiz);
		if (perfect == true) cout << "El arbol es perfecto " << endl;
		else cout << "El arbol no es perfecto" << endl;
	}

	void isComplete() { _isComplete(); }

	Nodo<T>* busqueda(function <bool(T)>condition) {
		return _busqueda(raiz, condition);
	}
};

template<typename T>
void imprimir(T e) {
	cout << "" << e;
}
void imprimirInt(int e) {
	cout << "" << e;
}

void menu(ArbolAVL<Producto, int>* tree) {
	int eleccion;
	cout << "Ingrese la opcion que desee realizar: " << endl;
	cout << "1) Impresion inOrden de elementos: " << endl;
	cout << "2) Impresion inOrden de alturas: " << endl;
	cout << "3) Esta balanceado el arbol? " << endl;
	cout << "4) Es un arbol AVL? " << endl;
	cout << "5) El arbol es perfecto? " << endl;
	cout << "6) El arbol esta completo? " << endl;
	cout << "7) Buscar " << endl;
	cin >> eleccion;
	switch (eleccion) {
	case 1: {
		tree->inOrden();
		break;
	}
	case 2: {
		tree->inOrdenH();
		break;
	}
	case 3: {
		tree->isBalance();
		break;
	}
	case 4: {
		tree->isAVL();
		break;
	}
	case 5: {
		tree->isPerfect();
		break;
	}
	case 6: {
		tree->isComplete();
		break;
	}
	case 7: {
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

int main()
{
	srand(time(NULL));
	int cant = 5 + rand() % 8;
	ArbolAVL<Producto, int>* tree;
	int insercion;
	cout << "Seleccione el tipo de insercion que desee hacer: " << endl;
	cout << "1) Por Nombre " << endl;
	cout << "2) Por Categoria " << endl;
	cout << "3) Por Precio " << endl;

	cin >> insercion;
	if (insercion == 1) {
		auto lambdaCmpName = [](Producto a, Producto b) ->short {
			if (a.getNombre().compare(b.getNombre()) < 0) return -1;
			else if (a.getNombre().compare(b.getNombre()) > 0) return 1;
			else return 0;
		};
		tree = new ArbolAVL<Producto, int>(imprimir, imprimirInt, lambdaCmpName);
		//CARGA DE ARCHIVOS
		//Init(tree, cant);
		menu(tree);
	}
	else if (insercion == 2) {
		auto lambdaCmpCategoria = [](Producto a, Producto b)->short {
			if (a.getCategoria().compare(b.getCategoria()) < 0) return -1;
			else if (a.getCategoria().compare(b.getCategoria()) > 0) return -1;
			else return 0;
		};
		tree = new ArbolAVL<Producto, int>(imprimir, imprimirInt, lambdaCmpCategoria);
		//CARGA DE ARCHIVOS
		//Init(tree, cant);
		menu(tree);
	}
	else {
		auto lambdaCmpPrecio = [](Producto a, Producto b)-> short {
			if (a.getPrecio() < b.getPrecio()) return -1;
			else if (a.getPrecio() > b.getPrecio()) return 1;
			else return 0;
		};
		tree = new ArbolAVL<Producto, int>(imprimir, imprimirInt, lambdaCmpPrecio);
		//CARGA DE ARCHIVOS
		//Init(tree, cant);
		menu(tree);
	}
	return 0;
}
