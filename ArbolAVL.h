#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <functional>
#include <algorithm>
#include "Producto.h"
using namespace std;

template<class T>

class Node {
public:
	T elemento;
	Node* izq;
	Node* der;
	int altura;

	Node() {
		izq = nullptr;
		der = nullptr;
		altura = 0;
	}
	~Node() {}
};

template<class T>
class ArbolAVL {
private:
	Node<T>* raiz;
	short (*criterio)(T, T);//puntero a función- en vez de utilizar un functor 
	void(*impresionArbol)(T); //puntero a función 
	vector<T> AVLvec;   
	int _altura(Node<T>* nodo) {
		if (nodo == nullptr) return -1;
		return nodo->altura;
	}

	void _actualizarAltura(Node<T>* nodo) {
		if (nodo != nullptr) {
			int hizq = _altura(nodo->izq);
			int hder = _altura(nodo->der);
			nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
		}
	}

	void _rotarDerecha(Node<T>*& nodo) {
		Node<T>* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		//Actualizamos la altura
		_actualizarAltura(nodo);
		nodo = p;
		_actualizarAltura(nodo);
	}

	void _rotarIzquierda(Node<T>*& nodo) {

		Node<T>* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		//Actualizamos la altura
		_actualizarAltura(nodo);
		nodo = p;
		_actualizarAltura(nodo);
	}

	void _balanceo(Node<T>*& nodo) {
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

		else if (fb < -1) { //rotar a la der
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) {//verificar si aplica doble rotación 
				_rotarIzquierda(nodo->izq);
			}
			_rotarDerecha(nodo);
		}
		else _actualizarAltura(nodo);
	}

	bool _insertar(Node<T>*& nodo, T e) {
		if (nodo == nullptr) {
			//Nuevo elemento
			nodo = new Node<T>();
			nodo->elemento = e;
			return true;
		}
		else if (criterio(e, nodo->elemento) == 0) {
			_insertar(nodo->der, e);
		}
		else if (criterio(e, nodo->elemento) == -1) {
			_insertar(nodo->izq, e);
		}
		else if (criterio(e, nodo->elemento) == 1) {
			_insertar(nodo->der, e);
		}
		_balanceo(nodo);
		return true;
	}

	void _inOrden(Node<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrden(nodo->izq);
		impresionArbol(nodo->elemento);
		_inOrden(nodo->der);
	}

	int _obtenerBalance(Node<T>* nodo) {
		if (nodo == nullptr) return 0;
		return _altura(nodo->der) - _altura(nodo->izq);
	}

	bool _isBalance(Node<T>* nodo) {
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

	int _obtenerAltura(Node<T>* nodo) {
		if (nodo == nullptr) return 0;
		int alturaIzq = _altura(nodo->izq);
		int alturaDer = _altura(nodo->der);
		return max(alturaIzq, alturaDer) + 1; //se le suma uno para contar el nivel 0 o la raiz  
	}

	int _contadorNodos(Node <T>* nodo) {
		if (nodo == nullptr) return 0;
		return _contadorNodos(nodo->izq) + _contadorNodos(nodo->der) + 1; //se le suma uno por la raiz
	}

	bool _isPerfect(Node<T>* nodo) {
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

	Node<T>* _busqueda(Node<T>* nodo, function <bool(T)>condition) {
		if (nodo == nullptr) return nullptr;
		if (condition(nodo->elemento)) return nodo;
		else if (condition(nodo->elemento)) { return _busqueda(nodo->izq, condition); }
		else return _busqueda(nodo->der, condition);
	}

	void _AVLtreeToVector(Node<T>* node) {
		if (node != nullptr) {
			_AVLtreeToVector(node->izq);
			AVLvec.push_back(node->elemento); 
			_AVLtreeToVector(node->der);
		}
	}
	int _binSearch(Node<T>* nodo, T e) {
		if (nodo == nullptr) {//sino se encuentra se devuelve -1
			return -1;
		}

		if (e == nodo->elemento) {//si se encuentra se devuelve 1  
			return 1;
		}

		if (e < nodo->elemento) { //en caso sea menor revisa a la izquierda con recursividad 
			int result = _binSearch(nodo->izq, e);
			if (result != -1) {
				return result;
			}
		}
		else {
			int result = _binSearch(nodo->der, e);//lo mismo pa la derecha
			if (result != -1) {
				return result;
			}
		}
		return -1;
	}
public:
	ArbolAVL() = default; 
	ArbolAVL(void(*nuevaFuncion)(T), short(*Comparador)(T, T)) {
		this->impresionArbol = nuevaFuncion;
		this->criterio = Comparador;
		this->raiz = nullptr;
	}
	int altura() { return _altura(raiz); }
	void ALVtoVector() { _AVLtreeToVector(raiz); }
	vector<T> getVctor() { return AVLvec; } 
	bool Insertar(T e) { return _insertar(raiz, e); }

	void inOrden() { _inOrden(raiz); }

	int obtenerBalance(Node<T>* nodo) { return _obtenerBalance(nodo); }

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

	Node<T>* busqueda(function <bool(T)>condition) {
		return _busqueda(raiz, condition);
	}
	
	int binSearch(T e) { return _binSearch(raiz, e); }

};