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
	DataFrame df;
	ArbolAVL<Producto> avlTreeN;                             //ARBOL AVL NOMBRE
	ArbolAVL<Producto> avlTreeP;							//ARBOL AVL PRECIO
	ArbolB<Producto> bstTree;									//ARBOL BST
	TreeAVLProduct treeP;											//COLECCIONADORA AVL
	TreeBSTProduct bstP;												//COLECCIONADORA BST
	string tipoComparacion; 
	vector<Producto> vectorBST;								//VECTOR PARA BST
	int cantDatos;
public:
	Test() = default;
	Test(TreeAVLProduct& treeP, TreeBSTProduct& bstP) {
		this->treeP = treeP;
		this->bstP = bstP; 																
		treeP.simulateTreeP();
		bstP.simulateBSTtree();
		bstTree = bstP.treeBST;  
		avlTreeN = treeP.treeName;  
		avlTreeP = treeP.treePrecio; 
		bstTree.BSTtreeToVector(); 
		vectorBST = bstTree.getVector();
		cantDatos = vectorBST.size();
	}

	TreeAVLProduct llenarAVLP(); 
	TreeAVLProduct llenarAVLN();
	TreeBSTProduct llenarBST(); 

	void exportar(string sufijo, chrono::duration<double>tiempo1, chrono::duration<double>tiempo2, chrono::duration<double>tiempo3);
	void compararInsercion(); 
	void compararBusqueda(Producto product); 

	void init();
};

#endif