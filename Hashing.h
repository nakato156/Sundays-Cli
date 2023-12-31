#pragma once
#ifndef HASHING_H
#define HASHING_H

#include <cstring>
#include <string>
#include "GenPrimos.h"

class Hashing {
private:
	GeneradorPrimos genPrimos = GeneradorPrimos(0);
public:
	Hashing() = default;

	template <typename T>
	size_t dinamicHashing(const T& key, int size) {
		size_t hash = 0;
		size_t tamBytesKey = sizeof(T);
		const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);

		for (int i = 0; i < tamBytesKey; i++)
			hash ^= data[i];

		return hash % size;
	}

	size_t basicHashing(const char* key, int size);

	// Algoritmo de Hashing Basico de Division por Bloques
	size_t AHBDB(long long int key, int size);

	size_t AHBDB(const char* key, int size);
};

#endif // !HASHING_H
