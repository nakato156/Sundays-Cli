#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std; 

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	Nodo(T elemento) {
		izq = nullptr;
		der = nullptr;
		this->elemento = elemento;
	}
};

template <class T>
class ArbolB {
private:
	Nodo<T>* raiz;
	vector<T> vec;

	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>(e);
		}
		else if (e < nodo->elemento) {
			return _insertar(nodo->izq, e);
		}
		else if (e >= nodo->elemento) {
			return _insertar(nodo->der, e);
		}
	}

	void _enOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		cout << nodo->elemento << " ";
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo<T>* nodo) {
		if (nodo != nullptr) {											//primero confirmamos que el arbol no este vacio (raiz)
			cout << nodo->elemento << " ";						//imprimimos el elemento
			_preOrden(nodo->izq);						//recursividad pero ahora comparando el hijo izquierdo. 
			_preOrden(nodo->der);						//recursividad con el hijo derecho
			//Se sigue el algoritmo original, RAIZ-IZQUIERDA-DERECHA
		}
	}

	void _postOrden(Nodo<T>* nodo) {
		if (nodo != nullptr) {										//primero confirmamos que el arbol no este vacio (raiz)
			_postOrden(nodo->izq);				//recursividad pero ahora comparando el hijo izquierdo. 
			_postOrden(nodo->der);				//recursividad con el hijo derecho
			cout << nodo->elemento << " ";					//imprimimos el elemento
			//Se sigue el algoritmo original, IZQUIERDA-DERECHA-RAIZ
		}
	}

	void _BSTtreeToVector(Nodo<T>* nodo) {
		if (nodo != nullptr) {
			vec.push_back(nodo->elemento);
			_BSTtreeToVector(nodo->izq);
			_BSTtreeToVector(nodo->der);
		}
	}
	void _printVector(const std::vector<T>& vec) {
		cout << "[";
		for (size_t i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i != vec.size() - 1) {
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
	vector<T> _getVector() {
		return vec;
	}
	bool _vacio() {
		return raiz == nullptr;
	}

	int _cantidad() {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha
		Nodo<T>* nodo = raiz;
		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}
	}

	int _altura() {
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario
		Nodo<T>* nodo = raiz;
		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}

	int _binSearch(Nodo<T>* nodo, T e) {
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

	int _interpolation_search(int n, T X)
	{
		int lo = 0;
		int hi = n - 1;
		int mid;

		while ((vec[hi] != vec[lo]) && (X >= vec[lo]) && (X <= vec[hi])) {
			mid = lo + ((X - vec[lo]) * (hi - lo) / (vec[hi] - vec[lo]));

			if (vec[mid] < X)
				lo = mid + 1;
			else if (X < vec[mid])
				hi = mid - 1;
			else
				return mid;
		}

		if (X == vec[lo])
			return lo;
		else
			return -1;
	}

	int _obtenerProfundidad(Nodo<T>* nodo) {//caso0 
		if (nodo == nullptr) { return 0; } //en caso de que el arbol este vacio
		else
		{
			int profizquierda = _obtenerProfundidad(nodo->izq);
			int profderecha = _obtenerProfundidad(nodo->der);
			if (profizquierda > profderecha) { return 1 + profizquierda; }
			else { return 1 + profderecha; }

		}
	}

	Nodo<T>* _eliminarNodo(Nodo<T>* nodo, T valor) {
		//en caso de que el elemento a eliminar sea la raiz o sea hoja
		if (nodo == nullptr) {														//primero confirmamos que el arbol no este vacio (raiz)
			return nullptr;																//si es asi retorna vacio
		}
		if (valor < nodo->elemento) {											//primero comparamos si el valor es menor que el elemento del primer nodo
			nodo->izq = _eliminarNodo(nodo->izq, valor);			//si es menor, recursividad en caso del hijo izquierdo. 
			//Si el hijo izquierdo es hoja, se re asigna su puntero a nullptr
		}
		else if (valor > nodo->elemento) {									//si el valor es mayor que el elemento del nodo
			nodo->der = _eliminarNodo(nodo->der, valor);			//recursividad en caso del hijo derecho. 
			//Si el hijo derecho es hoja, se re asigna su puntero a nullptr
		}

		//en caso de que el elemento a eliminar tenga 1 hijo

		else {
			if (nodo->izq == nullptr) {											//si el puntero izquierdo es nullptr, quiere decir que tiene hijo derecho
				Nodo<T>* temp = nodo->der;								//asignamos el derecho a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo izquierdo al arbol
			}
			else if (nodo->der == nullptr) {									//si el puntero derecho es nullptr, quiere decir que tiene hijo izquierdo
				Nodo<T>* temp = nodo->izq;								//asignamos el izquierdo a un temporal
				delete nodo;																//eliminamos el nodo
				return temp;																//volvemos a unir el hijo derecho al arbol
			}
			//en caso de que el elemento a eliminar tenga 2 hijos
			Nodo<T>* sucesor = _encontrarSiguiente(nodo->der);					//siempre se tomara el hijo derecho ya que estos suelen ser mayores que el padre
			nodo->elemento = sucesor->elemento;											//asignamos los valores	
			nodo->der = _eliminarNodo(nodo->der, sucesor->elemento);		//eliminamos el nodo
		}
		return nodo;
	}
	//metodo que nos servira para encontrar al siguiente
	Nodo<T>* _encontrarSiguiente(Nodo<T>* nodo) {
		Nodo<T>* actual = nodo;
		while (actual->izq != nullptr) {
			actual = actual->izq;
		}
		return actual;
	}
	int _nextGap(int gap)
	{
		// Shrink gap by Shrink factor
		gap = (gap * 10) / 13;

		if (gap < 1)
			return 1;
		return gap;
	}

	void _combSort(int n, function<bool(T, T)> comparador) {  // n es la cantidad de elementos que tiene el vector
		// Initialize gap
		int gap = n;

		// Initialize swapped as true to make sure that
		// loop runs
		bool swapped = true;

		// Keep running while gap is more than 1 and last
		// iteration caused a swap
		while (gap != 1 || swapped == true)
		{
			// Find next gap
			gap = _nextGap(gap);

			// Initialize swapped as false so that we can
			// check if swap happened or not
			swapped = false;

			// Compare all elements with current gap
			for (int i = 0; i < n - gap; i++)
			{
				if (comparador(vec[i], vec[i + gap]))
				{
					swap(vec[i], vec[i + gap]);
					swapped = true;
				}
			}
		}
	}

	int _partition(int low, int high, function<bool(T, T)> comparador) {
		T pivote = vec[high];
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++) {
			if (comparador(vec[j], pivote)) {
				i++;
				swap(vec[i], vec[j]);
			}
		}
		swap(vec[i + 1], vec[high]);
		return (i + 1);
	}

	void _quickSort(int low, int high, function<bool(T, T)> comparador) {
		if (low < high) {
			int pi = _partition(vec, low, high, comparador);

			_quickSort(vec, low, pi - 1, comparador);
			_quickSort(vec, pi + 1, high, comparador);
		}
	}

	void _merge(int left, int mid, int right, function<bool(T, T)> comparador) {
		int n1 = mid - left + 1;
		int n2 = right - mid;

		vector<T> leftArr(n1);
		vector<T> rightArr(n2);

		for (int i = 0; i < n1; i++) {
			leftArr[i] = vec[left + i];
		}

		for (int j = 0; j < n2; j++) {
			rightArr[j] = vec[mid + 1 + j];
		}

		int i = 0, j = 0, k = left;
		while (i < n1 && j < n2) {
			if (comparador(leftArr[i], rightArr[j])) {
				vec[k] = leftArr[i];
				i++;
			}
			else {
				vec[k] = rightArr[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			vec[k] = leftArr[i];
			i++;
			k++;
		}

		while (j < n2) {
			vec[k] = rightArr[j];
			j++;
			k++;
		}
	}

	void _mergeSort(int left, int right, function<bool(T, T)> comparador) {
		if (left < right) {
			int mid = left + (right - left) / 2;

			_mergeSort(left, mid, comparador);
			_mergeSort(mid + 1, right, comparador);
			_merge(left, mid, right, comparador);
		}
	}

	int _binarySearch(int lo, int hi, T x)
	{
		while (lo <= hi) {
			int m = lo + (hi - lo) / 2;
			if (vec[m] == x)
				return m;
			if (vec[m] < x)
				lo = m + 1;
			else
				hi = m - 1;
		}
		return -1;
	}

	int _exponentialSearch(int n, T x)
	{
		if (vec[0] == x)
			return 0;
		int i = 1;
		while (i < n && vec[i] <= x)
			i = i * 2;

		return _binarySearch(i / 2, min(i, n - 1), x);
	}
	Nodo<T>* _busquedaBST(Nodo<T>* nodo, function <bool(T)>condition) {  
		if (nodo == nullptr) return nullptr;
		if (condition(nodo->elemento)) return nodo;
		else if (condition(nodo->elemento)) { return _busquedaBST(nodo->izq, condition); }  
		else return _busquedaBST(nodo->der, condition); 
	}

public:
	ArbolB() { raiz = nullptr; }

	bool insertar(T e) { return _insertar(raiz, e); }

	void enOrden() { _enOrden(raiz); }

	void preOrden() { _preOrden(raiz); }

	void BSTtreeToVector() { _BSTtreeToVector(raiz); }

	vector<T> getVector() { return _getVector(); }

	int cantidad() { return _cantidad(raiz); }

	int altura() { return _altura(raiz); }

	void postOrden() { _postOrden(raiz); }

	Nodo<T>* busquedaBST(function<bool(T)>buscador) { return _busquedaBST(raiz, buscador); }  

	int binarySearch(int low, int high, T x) {
		return _binarySearch(low, high, x);
	}

	int exponencialSearch(int n, T x) {
		return _exponentialSearch(n, x);
	}

	int ternarySearch(int left, int right, T target) {
		if (right >= left) {
			int mid1 = left + (right - left) / 3;
			int mid2 = right - (right - left) / 3;

			if (vec[mid1] == target) {
				return mid1;
			}

			if (vec[mid2] == target) {
				return mid2;
			}

			if (target < vec[mid1]) {
				return ternarySearch(left, mid1 - 1, target);
			}
			else if (target > vec[mid2]) {
				return ternarySearch(mid2 + 1, right, target);
			}
			else {
				return ternarySearch(mid1 + 1, mid2 - 1, target);
			}
		}
		return -1;
	}

	void binSearch(T e) {
		int resultado = _binSearch(raiz, e);
		if (resultado == -1) cout << "Elemento no encontrado " << endl;
		else cout << "Elemento encontrado " << endl;
	}

	int interpolarSearch(T X) {
		return _interpolation_search(vec.size(), X);
	}

	void obtenerProfundidad() {
		int profundidad = _obtenerProfundidad(raiz) - 1;
		cout << "Profundidad del arbol: " << profundidad << endl;
	}

	Nodo<T>* encontrarSiguiente() { return _encontrarSiguiente(raiz); }

	Nodo<T>* eliminarNodo(T eliminar) { return _eliminarNodo(raiz, eliminar); }
	int nextGap(int gap) { return _nextGap(gap); }

	void combSort(int n, function<bool(T, T)> comparador) { _combSort(n, comparador); }

	int partition(int low, int high, function<bool(T, T)> comparador) { _partition(low, high, comparador); }

	void quickSort(int low, int high, function<bool(T, T)> comparador) {
		_quickSort(low, high, comparador);		//low es 0, high es tamanio del arreglo - 1 y el comparador el operador		
	}

	void merge(int left, int mid, int right, function<bool(T, T)> comparador) { _merge(left, mid, right, comparador); }

	void mergeSort(int left, int right, function<bool(T, T)> comparador) { _mergeSort(left, right, comparador); }

	void printVector() { _printVector(vec); }
};
