#include "Producto.h"
using namespace std;
string Producto::getCodigo() { return codigo; }  
string Producto::getNombre() { return nombre; }
string Producto::getCategoria() { return categoria; }
float Producto::getPrecio() const { return precio; } 
