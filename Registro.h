#pragma once
#ifndef REGISTRO_H
#define REGISTRO_H
#include "Usuario.h"
#include "helpers.h"

class Registro {
    Usuario& user;
public:
    Registro() = default;
    Registro(Usuario& usuario) : user(usuario) {};
    void registro();
};

#endif
