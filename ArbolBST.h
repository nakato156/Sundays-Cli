#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std; 

template <class T>
class NodoT { 
public:
	T e;
	NodoT* izquierda; 
	NodoT* dererecha; 
	NodoT() = default;   
	NodoT(T e) { 
		izquierda = nullptr;
		dererecha = nullptr;
		this->e = e; 
	}
};

template <class T>
class ArbolB {
private:
	NodoT<T>* raiz;
	vector<T> vec;

	bool _insertar(NodoT<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new NodoT<T>();
			nodo->e = e;
		}
		else if (e < nodo->e) {
			return _insertar(nodo->izquierda, e);
		}
		else if (e >= nodo->e) {
			return _insertar(nodo->dererecha, e);
		}
	}

	void _enOrden(NodoT<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izquierda);
		cout << nodo->e << " ";
		_enOrden(nodo->dererecha);
	}
	void _BSTtreeToVector(NodoT<T>* nodo) {					
		if (nodo != nullptr) {												//1 + MAX INTERNO->1 + 2 = 3
			vec.push_back(nodo->e);									//2
			_BSTtreeToVector(nodo->izquierda);				//2
			_BSTtreeToVector(nodo->dererecha);				//2
		}																				//TOTAL: 3
	}

	vector<T> _getVector() {
		return vec;
	}

	int _binSearch(NodoT<T>* nodo, T e) {
		if (nodo == nullptr) {						
			return -1;
		}

		if (e == nodo->e) {//si se encuentra se devuelve 1 
			return 1;
		}

		if (e < nodo->e) { //en caso sea menor revisa a la izquierda con recursividad 
			int result = _binSearch(nodo->izquierda, e);
			if (result != -1) {
				return result;
			}
		}
		else {
			int result = _binSearch(nodo->dererecha, e);//lo mismo pa la derecha
			if (result != -1) {
				return result;
			}
		}
		return -1;
	}

	int _obtenerProfundidad(NodoT<T>* nodo) {//caso0 
		if (nodo == nullptr) { return 0; } //en caso de que el arbol este vacio
		else
		{
			int profizquierda = _obtenerProfundidad(nodo->izquierda);
			int profderecha = _obtenerProfundidad(nodo->dererecha);
			if (profizquierda > profderecha) { return 1 + profizquierda; }
			else { return 1 + profderecha; }

		}
	}

	NodoT<T>* _eliminarNodo(NodoT<T>* nodo, T valor) {
		//en caso de que el elemento a eliminar sea la raiz o sea hoja
		if (nodo == nullptr) {														//primero confirmamos que el arbol no este vacio (raiz)
			return nullptr;																//si es asi retorna vacio
		}
		if (valor < nodo->e) {											//primero comparamos si el valor es menor que el elemento del primer nodo
			nodo->izquierda = _eliminarNodo(nodo->izquierda, valor);			//si es menor, recursividad en caso del hijo izquierdo. 
			//Si el hijo izquierdo es hoja, se re asigna su puntero a nullptr
		}
		else if (valor > nodo->e) {									//si el valor es mayor que el elemento del nodo
			nodo->dererecha = _eliminarNodo(nodo->dererecha, valor);			//recursividad en caso del hijo derecho. 
			//Si el hijo derecho es hoja, se re asigna su puntero a nullptr
		}

		//en caso de que el elemento a eliminar tenga 1 hijo

		else {
			if (nodo->izquierda == nullptr) {											//si el puntero izquierdo es nullptr, quiere decir que tiene hijo derecho
				NodoT<T>* temp = nodo->dererecha;								//asignamos el derecho a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo izquierdo al arbol
			}
			else if (nodo->dererecha == nullptr) {									//si el puntero derecho es nullptr, quiere decir que tiene hijo izquierdo
				NodoT<T>* temp = nodo->izquierda;								//asignamos el izquierdo a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo derecho al arbol
			}
			//en caso de que el elemento a eliminar tenga 2 hijos
			NodoT<T>* sucesor = _encontrarSiguiente(nodo->dererecha);					//siempre se tomara el hijo derecho ya que estos suelen ser mayores que el padre
			nodo->e = sucesor->e;											//asignamos los valores	
			nodo->dererecha = _eliminarNodo(nodo->dererecha, sucesor->e);		//eliminamos el nodo
		}
		return nodo;
	}
	//metodo que nos servira para encontrar al siguiente
	NodoT<T>* _encontrarSiguiente(NodoT<T>* nodo) { 
		NodoT<T>* actual = nodo;
		while (actual->izquierda != nullptr) {
			actual = actual->izquierda;
		}
		return actual;
	}

	NodoT<T>* _busquedaBST(NodoT<T>* nodo, function <bool(T)>condition) {
		if (nodo == nullptr) return nullptr;																						//2
		if (condition(nodo->e)) return nodo;																					//2
		else if (condition(nodo->e)) { return _busquedaBST(nodo->izquierda, condition); }		//3
		else return _busquedaBST(nodo->dererecha, condition);													//2
	}																										//TOTAL: 2 + 2 + 3 + 3 = 9

public:
	ArbolB() { raiz = nullptr; }

	bool insertar(T e) { return _insertar(raiz, e); }

	void enOrden() { _enOrden(raiz); }

	
	void BSTtreeToVector() { _BSTtreeToVector(raiz); }

	vector<T> getVector() { return _getVector(); }

	NodoT<T>* busquedaBST(function<bool(T)>buscador) { return _busquedaBST(raiz, buscador); }

	void binSearch(T e) {
		int resultado = _binSearch(raiz, e);
		if (resultado == -1) cout << "Elemento no encontrado " << endl;
		else cout << "Elemento encontrado " << endl;
	}

	void obtenerProfundidad() {
		int profundidad = _obtenerProfundidad(raiz) - 1;
		cout << "Profundidad del arbol: " << profundidad << endl;
	}

	NodoT<T>* encontrarSiguiente() { return _encontrarSiguiente(raiz); }

	NodoT<T>* eliminarNodo(T eliminar) { return _eliminarNodo(raiz, eliminar); }

};
