#include "Test.h"

TreeAVLProduct Test::llenarAVLP() {  
	TreeAVLProduct AVLtreeP;
	AVLtreeP.simulateTreeP();
	return AVLtreeP;
}
TreeAVLProduct Test::llenarAVLN() {
	TreeAVLProduct AVLtreeN;
	AVLtreeN.simulateTreeN();
	return AVLtreeN;
}
TreeBSTProduct Test::llenarBST() {
	TreeBSTProduct BSTtree;
	BSTtree.simulateBSTtree();
	return BSTtree;
}
void Test::exportar(string sufijo, chrono::duration<double>tiempo1, chrono::duration<double>tiempo2, chrono::duration<double>tiempo3) {
	ofstream archivo("resultados" + sufijo + ".txt");
	if (archivo.is_open()) {
		archivo << "Tiempo1: " << tiempo1.count() << endl;
		archivo << "Tiempo2: " << tiempo2.count() << endl;
		archivo << "Tiempo3: " << tiempo3.count() << endl;
		archivo << "Insercion: " << tipoComparacion << endl;
		archivo << "Cant. de datos: " << cantDatos << endl;
		archivo.close();
	}
}
//INSERCION ENTRE LOS DOS TIPOS DE ARBOLES
void Test::compararInsercion() {
	cout << "Insertando: " << endl; 
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3;
	//insercion en AVL por nombre
	start1 = chrono::system_clock::now();
	treeP = llenarAVLN(); 
	end1 = chrono::system_clock::now();
	//insercion en AVL por precio
	start2 = chrono::system_clock::now();
	treeP = llenarAVLP();
	end2 = chrono::system_clock::now();
	//insercion en BST
	start3 = chrono::system_clock::now();
	bstP = llenarBST(); 
 	end3 = chrono::system_clock::now();

	chrono::duration<double> tiempo1 = end1 - start1;
	chrono::duration<double> tiempo2 = end2 - start2;
	chrono::duration<double> tiempo3 = end3 - start3;
	tipoComparacion = "Insercion NombreAVL vs PrecioAVL vs BST";
	exportar("_inser", tiempo1, tiempo2, tiempo3);
}

void Test::compararBusqueda(Producto producto) {
	cout << "comparando" << endl; 
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3;
	//busqueda en AVL de nombre
	start1 = chrono::system_clock::now();
	avlTreeN.binSearch(producto);
	end1 = chrono::system_clock::now();
	//busqueda en AVL de precio
	start2 = chrono::system_clock::now();
	avlTreeP.binSearch(producto);
	end2 = chrono::system_clock::now();
	//busqueda en BST
	start3 = chrono::system_clock::now();
	bstTree.binSearch(producto);
	end3 = chrono::system_clock::now();

	chrono::duration<double> tiempo1 = end1 - start1;
	chrono::duration<double> tiempo2 = end2 - start2;
	chrono::duration<double> tiempo3 = end3 - start3;
	tipoComparacion = "Binsearch en NombreAVL vs PrecioAVL vs BST";
	exportar("_busq", tiempo1, tiempo2, tiempo3);
}

void Test::init() {
	int i = rand() % vectorBST.size();  
	auto producto = vectorBST.at(i);  
	compararInsercion(); 
	compararBusqueda(producto);  
}