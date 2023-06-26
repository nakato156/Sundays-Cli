#pragma once
#ifndef TEST_H
#define TEST_H
#include "TreeBSTProduct.h"
#include "TreeAVLProduct.h" 
#include <iostream>
#include <chrono>
#include <time.h> 

class Test {
private:
	TreeAVLProduct coleccionAVL; 											//COLECCIONADORA AVL
	TreeBSTProduct coleccionBST; 												//COLECCIONADORA BST
	string tipoComparacion; 
	vector<Producto> vectorBST;								//VECTOR PARA BST
	int cantDatos;
public:
	Test() = default;  

	void exportar(string sufijo, chrono::duration<double>tiempo1, chrono::duration<double>tiempo2, chrono::duration<double>tiempo3);
	void compararInsercion(); 
	void compararBusqueda(Producto product); 

	void init();
};

#endif