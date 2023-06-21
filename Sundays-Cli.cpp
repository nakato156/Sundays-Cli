#include <iostream>
#include "helpers.h"
#include "constantes.h"
#include "Menu.h"
#include "Usuario.h"

using namespace std;

void mostrarOpciones(HANDLE hConsole, int select = 0) {
    gotoxy(0, 0);
    printSelectLine(hConsole, { "> Iniciar Sesion", "> Registro" }, select, 10);
}

void login(HANDLE hConsole, Usuario& usuario) {
    printSelectLine(hConsole, { make_pair("Iniciar sesion\n", FOREGROUND_RED | FOREGROUND_INTENSITY), make_pair("Ingrese sus datos", 6) });
    
    string email;
    cout << "Email: "; cin >> email;
    cout << "Password: ";

    string password = inputPassword();
    
    usuario.login(email, password);
    if (!usuario.isLogged()) cout << "Datos incorrectos\n";
}

void registro(HANDLE hConsole, Usuario& usuario) {
    printSelectLine(hConsole, { make_pair("Registro\n", FOREGROUND_RED | FOREGROUND_INTENSITY), make_pair("Ingrese sus datos", 6) });

    string email, nombre, pass;
    cout << "Nombres: "; getline(cin, nombre);
    cout << "Email: "; cin >> email;
    pass = inputPassword();

    usuario.registro(email, nombre, pass, 0);
}

int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mostrarOpciones(hConsole);

    int y = 0, pos_y_login = 0, pos_y_reg = 1;
    gotoxy(2, y);

    while (true){
        TECLA tecla = getTecla();
        if (tecla == TECLA::K_ENTER) break;
        else if (tecla == TECLA::K_ABAJO) {
            if (y != pos_y_login)
                y = pos_y_login;
        }
        else if (tecla == TECLA::K_ARRIBA) {
            if (y != pos_y_reg)
                y = pos_y_reg;
        }

        mostrarOpciones(hConsole, (int)!y);
        gotoxy(2, !y);
    }

    system("cls");
    Usuario usuario;
    if (y == 0) login(hConsole, usuario);
    else registro(hConsole, usuario);
    
    system("cls");
    if (usuario.isLogged())
        cout << "Bienvenido " << usuario.getNombre() << "!" << endl;
    else {
        cout << "Ha ocurrido un error" << endl;
        exit(EXIT_FAILURE);
    }

    if (!usuario.isAdmin()) {
        Menu menu;
        menu.initMenu();
    }

    return 0;
}
