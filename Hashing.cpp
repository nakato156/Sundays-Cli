#include "Hashing.h"

template <typename T>
size_t Hashing::dinamicHashing(const T& key, int size){
	size_t hash = 0;
	size_t tamBytesKey = sizeof(T);
	const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);

	for (int i = 0; i < tamBytesKey; i++)
		hash ^= data[i];

	return hash % size;
}

size_t Hashing::basicHashing(const char* key, int size) {
	unsigned long long hash = 0;

	for (int i = 0; i < strlen(key); i++) {
		hash = (hash * genPrimos.current()) + key[i];
	}
	return hash % size;
}

// Algoritmo de Hashing Basico de Division por Bloques
size_t Hashing::AHBDB(long long int key, int size) {
	GeneradorPrimos c = GeneradorPrimos(37);
	int i = sizeof(key) * 8 - size;
	long long int block = ((key * c.current()) >> i) & ((1 << (key * c.current())) - 1);

	GeneradorPrimos num_veces = GeneradorPrimos(block + c.current());
	i -= size;
	size_t hash = num_veces.current();
	for (; i >= 0; i -= size) {
		for (int veces = 1; veces < num_veces.current(); veces++) {
			block ^= ((key >> i) * c.next()) & ((1 << key) - 1) * c.current(); 
		}
		hash ^= (1 << block) - 1; 
	}
	return hash;
}

size_t Hashing::AHBDB(const char* key, int size) {
	try {
		return AHBDB(std::stoi(key), size);
	}
	catch (const std::exception&){
		std::string resultado;
		for (const char* c = key; *c; ++c) {
			int numero = static_cast<int>(*c) - static_cast<int>('0');
			resultado += std::to_string(numero);
		}
		return AHBDB(std::stoi(resultado), size);
	}
}