#pragma once
#ifndef VISTAS_H
#define VISTAS_H
#include <Windows.h>
#include "Carrito.h"
#include "helpers.h"
#include "Admin.h"
#include "Descuento.h"
#include "Compra.h"
#include "Historial.h"

namespace Vistas {
	void pagar(HANDLE, CarritoDeCompras&, Usuario&);
	void admin(HANDLE, Admin);
	void historial(HANDLE, Usuario&, ArbolAVL<Producto>&);
}

#endif