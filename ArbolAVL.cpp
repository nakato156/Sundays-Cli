#include <iostream>
#include <time.h>
#include <functional>
#include <string>
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
	void(*procesar)(T); //puntero a función
	void(*procesar2)(K); //puntero a función 

	int _altura(Nodo<T>* nodo) { //de un nodo X
		if (nodo == nullptr) return 0;
		return nodo->altura;
	}

	void _rotarDerecha(Nodo<T>*& nodo) {
		Nodo<T>* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		//Actualizamos la altura
		nodo = p;
	}

	void _rotarIzquierda(Nodo<T>*& nodo) {

		Nodo<T>* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		//Actualizamos la altura
		nodo = p;
	}

	void _balanceo(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;

		if (fb > 1) { //rotar a la izq
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotación
				_rotarDerecha(nodo->der);
			}
			_rotarIzquierda(nodo);
		}

		if (fb < -1) { //rotar a la der
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) {//verificar si aplica doble rotación 
				_rotarIzquierda(nodo->izq);
			}
			_rotarDerecha(nodo);
		}
		//Actualizar la altura del nodo raiz
		hizq = _altura(nodo->izq);
		hder = _altura(nodo->der);
		nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
	}

	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			//Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else if (e == nodo->elemento) { return false; }
		else if (e < nodo->elemento) { _insertar(nodo->izq, e); }
		else if (e > nodo->elemento) { _insertar(nodo->der, e); }
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

	int _obtenerAltura(Nodo<T>* nodo) {      //de todo el arbol
		if (nodo == nullptr) return 0;
		int alturaIzq = _altura(nodo->izq);
		int alturaDer = _altura(nodo->der);
		return max(alturaIzq, alturaDer) + 1; //se le suma uno para contar el nivel 0 o la raiz  
	}

	int _contadorNodos(Nodo <T>* nodo) {
		if (nodo == nullptr) return 0;
		return _contadorNodos(nodo->izq) + _contadorNodos(nodo->der) + 1; //se le suma uno por la raiz
	}

	bool _isPerfect(Nodo<T>* nodo) {          //arbol con hijos completos
		int alturaArbol = _obtenerAltura(nodo);
		int nodos = _contadorNodos(nodo);
		int nodosEsperados = pow(2, alturaArbol) - 1;          //formula matematica para hallar los nodos esperados de un arbol 
		return nodos == nodosEsperados;
	}

	void _isComplete() {                                    //si es perfecto, es un arbol completo
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
	ArbolAVL(void(*nuevaFuncion)(T), void(*Funcion2)(K)) {
		this->procesar = nuevaFuncion;
		this->procesar2 = Funcion2;
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
	cout << " " << e;
}
void imprimirInt(int e) {
	cout << " " << e;
}