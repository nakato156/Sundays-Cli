#pragma once
#ifndef HASH_H
#define HASH_H
#include "Hashing.h"

using namespace std;

template <class K, class V>
class HashEntidad {
private:
	K key;
	V value;
public:
	HashEntidad(K key, V value) {
		this->key = key;
		this->value = value;
	}
	K getKey() { return key; }
	V getValue() { return value; }
};

template<class K, class V>
class HashTabla {
private:
	GeneradorPrimos genradorPrimos = GeneradorPrimos(37);
	HashEntidad<K, V>** tabla;
	int numElementos = 0;
	int TABLE_SIZE;
	size_t(*hashear)(const K, int) = [](const K key, int size_) {
		return Hashing().dinamicHashing<K>(key, size_);
	};

public:
	HashTabla(size_t(*hasher)(const K, int) = nullptr) {
		TABLE_SIZE = genradorPrimos.current();
		tabla = new HashEntidad<K, V>* [TABLE_SIZE];

		if (hasher != nullptr) 
			hashear = hasher;

		for (int i = 0; i < TABLE_SIZE; ++i)
			tabla[i] = nullptr;

	}
	~HashTabla() {
		vaciarTabla();
	}

	//Direccionamiento según Prueba Lineal
	void insertar(const K& key, V value) {
		size_t base, hash;
		int step;

		if (numElementos == TABLE_SIZE) resize();

		base = hashear(key, TABLE_SIZE);
		hash = base;
		step = 0;

		while (tabla[hash] != nullptr)
		{
			step++;
			hash = (base + step) % TABLE_SIZE;
		}

		tabla[hash] = new HashEntidad<K, V>(key, value);
		numElementos++;
	}

	void eliminar(const K& key) {
		int index = buscar(key);

		if (index != -1) {
			tabla[index] = nullptr;
			delete tabla[index];
			numElementos--;

			auto hashActual = hashear(key, TABLE_SIZE);
			if (hashActual != index) reorganizar(index);
			else if (hashear(tabla[index + 1]->getKey()) == hashActual) reorganizar(index);
		}
	}
	int sizeTabla() { return TABLE_SIZE; }
	int size() const { return numElementos; }

	int buscar(const K& key) {
		int step = 0;
		size_t i, base;
		i = base = hashear(key, TABLE_SIZE);

		while (true) {
			if (tabla[i] == nullptr) 
				return -1;
			else if (tabla[i]->getKey() == key) 
				return i;
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}

	V get(K key) {
		int i = buscar(key);
		if (i != -1)								//revisar si la clave a buscar existe en la tabla
			return tabla[i]->getValue();			//si existe, que retorne el valor.
		else
			throw std::runtime_error("¡Se ha producido un error!");		//si no existe, error
	}
	//imprimri el hashtahle 
	void imprimir() const {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (tabla[i] != nullptr) {
				cout << "Clave: " << tabla[i]->getKey()
					<< ", Valor: " << tabla[i]->getValue() << endl;
			}
			else cout << i << "\n";
		}
	}

	void imprimir(void(*func)(V val)) const {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if(tabla[i] != nullptr) func(tabla[i]->getValue());
		}
	}

private:
	void vaciarTabla() {
		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}

	void resize() {
		int nuevo_size = genradorPrimos.next();																	//2
		HashEntidad<K, V>** nueva_tabla = new HashEntidad<K, V>* [nuevo_size];	   //2
		for (int i = 0; i < nuevo_size; ++i)																//1+n(1+interna+2)->1 +n(1+2+2) ->1+5n
			nueva_tabla[i] = nullptr;												//2
		for (int i = 0; i < TABLE_SIZE; ++i) {							//1 + n(1 + interna + 2) - >1+n(1+10+2)->1+13n
			if (tabla[i] != nullptr) {												//3 + max interna->3 + 7 = 10
				K key = tabla[i]->getKey();									//3
				V value = tabla[i]->getValue();							   //3
				size_t  hash = hashear(key, nuevo_size);			 //2
				size_t base = hash;												//1
				int step = 0;															//1
				// Manejar colisiones utilizando prueba lineal
				while (nueva_tabla[hash] != nullptr) {				//3+maxinterna->3 +4=7
					hash = (base + (++step)) % nuevo_size;			//4
				}
				nueva_tabla[hash] = new HashEntidad<K, V>(key, value);//3
				tabla[i] = nullptr;																//2
			}
		}
		TABLE_SIZE = nuevo_size;									//1
		tabla = nueva_tabla;												//1
	}																			//TOTAL: 1 +5n + 1 + 13n + 2 = 18n + 4


	void reorganizar(int index) {
		int nextIndex = (index + 1) % TABLE_SIZE;					//3	
		while (tabla[nextIndex] != nullptr) {									//3+MAX INTERNA->3 + 4 = 7
			HashEntidad<K, V>* temp = tabla[nextIndex];			   //2
			tabla[nextIndex] = nullptr;												//2
			numElementos--;																//2
			if (numElementos < TABLE_SIZE) {							//1 + max interna->1+3=4
				insertar(temp->getKey(), temp->getValue());				//3
			}
			delete temp;	
			nextIndex = (nextIndex + 1) % TABLE_SIZE;			//3
		}
	}																				//TOTAL 7
};
#endif