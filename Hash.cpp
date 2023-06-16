#include "helpers.h"
#include "Hashing.cpp"

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
	int size() { return numElementos; }

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
	void imprimir() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (tabla[i] != nullptr) {
				cout << "Clave: " << tabla[i]->getKey()
					<< ", Valor: " << tabla[i]->getValue() << endl;
			}
			else cout << i << "\n";
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
		int nuevo_size = genradorPrimos.next();
		HashEntidad<K, V>** nueva_tabla = new HashEntidad<K, V>* [nuevo_size];

		for (int i = 0; i < nuevo_size; ++i)
			nueva_tabla[i] = nullptr;

		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				K key = tabla[i]->getKey();
				V value = tabla[i]->getValue();
				size_t  hash = hashear(key, nuevo_size);
				size_t base = hash;
				int step = 0;
				// Manejar colisiones utilizando prueba lineal
				while (nueva_tabla[hash] != nullptr) {
					hash = (base + (++step)) % nuevo_size;
				}

				nueva_tabla[hash] = new HashEntidad<K, V>(key, value);
				tabla[i] = nullptr;
			}
		}

		TABLE_SIZE = nuevo_size;
		tabla = nueva_tabla;
	}


	void reorganizar(int index) {
		// Reorganiza la tabla si es necesario, para evitar los huecos en la tabla
		int nextIndex = (index + 1) % TABLE_SIZE;			//calcula el siguiente indice
		while (tabla[nextIndex] != nullptr) {				//se sigue ejecutando cuando next index no sea null ptr
			HashEntidad<K, V>* temp = tabla[nextIndex];		//se crea un puntero temp que apunta al siguiente elemento
			tabla[nextIndex] = nullptr;
			numElementos--;
			if (numElementos < TABLE_SIZE) {
				insertar(temp->getKey(), temp->getValue());	//se inserta el elemento temp en la tabla
			}
			delete temp;
			nextIndex = (nextIndex + 1) % TABLE_SIZE;
		}
	}
};

