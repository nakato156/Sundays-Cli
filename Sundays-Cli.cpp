#include <iostream>
#include "helpers.h"
#include "constantes.h"
#include "Menu.h"

using namespace std;

void mostrarOpciones(HANDLE hConsole, int select = 0) {
    gotoxy(0, 0);
    printSelectLine(hConsole, { "> Iniciar Sesion", "> Registro" }, select, 10);
}

int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mostrarOpciones(hConsole);

    int y = 0, pos_y_login = 0, pos_y_reg = 1;
    gotoxy(2, y);

    while (true){
        TECLA tecla = getTecla();
        if (tecla == TECLA::K_ABAJO) {
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
    //Menu menu;
    //menu.initMenu();
    return 0;
}
