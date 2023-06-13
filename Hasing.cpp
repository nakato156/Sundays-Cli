#include <cstring>
#include "helpers.cpp"

class Hashing {
private:
	GeneradorPrimos genPrimos = GeneradorPrimos(0);
public:
	Hashing() = default;

	template <typename T>
	size_t dinamicHashing(const T& key, int size){
		size_t hash = 0;
		size_t tamBytesKey = sizeof(T);
		const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);

		for (int i = 0; i < tamBytesKey; i++)
			hash ^= data[i];

		return hash % size;
	}

	size_t basicHashing(const char* key, int size) {
		unsigned long long hash = 0;

		for (int i = 0; i < strlen(key); i++) {
			hash = (hash * genPrimos.current()) + key[i];
		}
		return hash % size;
	}


	static size_t bcrypt(const char* key, int size, const char* salt) {

	}
};