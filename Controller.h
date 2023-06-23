#pragma once
#include "TreeAVLProduct.h"
#include "TreeBSTProduct.h"

class Controller {
public:
	Controller() = default;
	TreeAVLProduct tp; 
	TreeBSTProduct BST; 
	void runAVLTree() {
		int eleccion; 
		cout << "Desea probar con: " << endl;
		cout << "1) ALV TREE: " << endl;
		cout << "2) BST TREE: " << endl;
		cin >> eleccion; 
		if (eleccion == 1) {
			tp.init();  
		}
		else {
			BST.initBST();  
		}
	}
};