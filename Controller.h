#pragma once
#include "TreeProduct.h"

class Controller {
public:
	Controller() = default;
	TreeProduct tp;
	void runAVLTree() {
		tp.simulateTreeN(); 
		tp.simulateTreeP(); 
		tp.init(); 
	}
};