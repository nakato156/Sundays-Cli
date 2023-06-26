#include "Test.h"

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
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3;
	//insercion en AVL por nombre
	start1 = chrono::system_clock::now();
	coleccionAVL.simulateTreeN(); 
	end1 = chrono::system_clock::now();
	//insercion en AVL por precio
	start2 = chrono::system_clock::now();
	coleccionAVL.simulateTreeP();  
	end2 = chrono::system_clock::now();
	//insercion en BST
	start3 = chrono::system_clock::now();
	coleccionBST.simulateBSTtree();  
 	end3 = chrono::system_clock::now();

	chrono::duration<double> tiempo1 = end1 - start1;
	chrono::duration<double> tiempo2 = end2 - start2;
	chrono::duration<double> tiempo3 = end3 - start3;
	tipoComparacion = "Insercion NombreAVL vs PrecioAVL vs BST";
	exportar("_inser", tiempo1, tiempo2, tiempo3);
}

void Test::compararBusqueda(Producto producto) {
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3;
	//busqueda en AVL de nombre
	start1 = chrono::system_clock::now();
	coleccionAVL.treeName.binSearch(producto);
	end1 = chrono::system_clock::now();
	//busqueda en AVL de precio
	start2 = chrono::system_clock::now();
	coleccionAVL.treePrecio.binSearch(producto); 
	end2 = chrono::system_clock::now();
	//busqueda en BST
	start3 = chrono::system_clock::now();
	coleccionBST.treeBST->binSearch(producto); 
	end3 = chrono::system_clock::now();

	chrono::duration<double> tiempo1 = end1 - start1;
	chrono::duration<double> tiempo2 = end2 - start2;
	chrono::duration<double> tiempo3 = end3 - start3;
	tipoComparacion = "Binsearch en NombreAVL vs PrecioAVL vs BST";
	exportar("_busq", tiempo1, tiempo2, tiempo3);
}

void Test::init() {
	coleccionAVL.simulateTreeN();  
	coleccionAVL.treeName.ALVtoVector(); 
	vectorAVL = coleccionAVL.treeName.getVctor(); 
	cantDatos = vectorAVL.size(); 
	int i = rand() % cantDatos;
	auto producto = vectorAVL.at(i);   
	compararInsercion(); 
	compararBusqueda(producto);  
}