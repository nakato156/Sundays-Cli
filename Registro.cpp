#include "Registro.h"

void Registro::registro() {
    std::string email, nombre, pass;
    std::cout << "Nombres: "; getline(cin, nombre);
    std::cout << "Email: "; cin >> email;
    pass = inputPassword();

    user.registro(email, nombre, pass, 0);
}