#pragma once
#ifndef VISTAS_H
#define VISTAS_H
#include <Windows.h>
#include "Carrito.h"
#include "helpers.h"

namespace Vistas {
	int pagar(HANDLE, CarritoDeCompras&);
}

#endif