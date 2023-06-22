#pragma once
#ifndef LOGIN_H
#define LOGIN_H
#include "Usuario.h"
#include "helpers.h"

class Login {
    Usuario& user;
public:
    Login() = default;
    Login(Usuario& usuario) : user(usuario) {};
    void login();
};
#endif