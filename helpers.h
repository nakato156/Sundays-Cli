#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <math.h>

class GeneradorPrimos {
private:
	int n_primo = 2;
public:
	GeneradorPrimos() = default;
	GeneradorPrimos(int random) {
		/*
		@param random: 0 para generar aleatoriamente, cualquier otro valor para setear el primo
		*/
		if (random == 0) {
			n_primo = next_(2 + rand() % 1000000000);
		}
		else if (esPrimo(random)) n_primo = random;
		else { n_primo = next_(random); }

	}

	class Iterator {
	private:
		int* num_primo;
	public:
		using difference_type = std::ptrdiff_t;

		Iterator() : num_primo(nullptr) {}
		Iterator(int* num) {
			num_primo = num;
		}

		int operator*() const {
			return *num_primo;
		}

		int* operator->() const {
			return num_primo;
		}

		Iterator operator+(difference_type n) {
			int* nuevo_primo = num_primo;
			for (int i = 0; i < n; i++) {
				nuevo_primo = new int(next_(*nuevo_primo));
			}
			return Iterator(nuevo_primo);
		}

		Iterator operator++() {
			num_primo = new int(next_(*num_primo));
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const Iterator& otro) const {
			return num_primo == otro.num_primo;
		}

		bool operator!=(const Iterator& otro) const {
			return !(*this == otro);
		}
	};

	int next() {
		n_primo = next_(n_primo);
		return n_primo;
	}

	int current() { return n_primo; }
	Iterator begin() { return Iterator(new int(n_primo)); }

	friend std::ostream& operator<<(std::ostream& os, const GeneradorPrimos& gen) {
		os << gen.n_primo;
		return os;
	}
private:
	static int next_(int n) {
		while (true) {
			if (esPrimo(++n)) return n;
		}
	}
	static bool esPrimo(int num) {
		if (num <= 1) return false;

		for (int i = 2; i <= sqrt(num); i++) {
			if (num % i == 0) return false;
		}
		return true;
	}

};
#endif