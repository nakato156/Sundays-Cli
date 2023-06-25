#pragma once
#ifndef VISTAS_H
#define VISTAS_H
#include <Windows.h>
#include "Carrito.h"
#include "helpers.h"
#include "Admin.h"
#include "Descuento.h"

namespace Vistas {
	int pagar(HANDLE, CarritoDeCompras&);
	void admin(HANDLE, Admin);
}

#endif