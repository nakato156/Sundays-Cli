#pragma once
#ifndef TEST_H
#define TEST_H
//#include "HashProduct.h"
#include "ArbolAVL.h"
#include"ArbolBST.h"
#include "DataFrame.h"
#include "Producto.h"
#include "TreeBSTProduct.h"
#include "TreeAVLProduct.h" 
#include <iostream>
#include <chrono>
#include<time.h> 
class Test {
private:
	DataFrame df;
	ArbolAVL<Producto> avlTreeN;
	ArbolAVL<Producto> avlTreeP;
	ArbolB<Producto> bstTree;
	TreeAVLProduct treeP;
	TreeBSTProduct bstP; 
	string tipoComparacion; 
	vector<Producto> vectorBST;
	int cantDatos;
public:
	Test() = default;
	Test(TreeAVLProduct& treeP, TreeBSTProduct& bstP) {
		this->treeP = treeP;
		this->bstP = bstP; 	
		bstTree = bstP.treeBST;  
		avlTreeN = treeP.treeName;  
		treeP.simulateTreeN(); 
		treeP.simulateTreeP(); 
		bstP.simulateBSTtree(); 
		avlTreeN = treeP.treePrecio;  
		bstTree.BSTtreeToVector(); 
		vectorBST = bstTree.getVector();
		cantDatos = vectorBST.size();
	}

	void exportar(string sufijo, chrono::duration<double>tiempo1, chrono::duration<double>tiempo2, chrono::duration<double>tiempo3);
	void compararInsercion(); 
	void compararBusqueda(Producto product); 

	void init();
};

#endif