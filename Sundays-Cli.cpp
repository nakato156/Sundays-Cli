#include <iostream>
#include "helpers.h"
#include "constantes.h"
#include "Menu.h"

using namespace std;

int main() {
    srand(time(NULL));
    cout << "\tIniciar sesion \t\t Registro" << endl;
    int x = 0, pos_x_reg = 20;
    while (true){
        TECLA tecla = getTecla();
        if (tecla == TECLA::k_IZQ) {
            if (x != 0) {
                x = 0;
                gotoxy(0, 0);
            }
        }
        else if (tecla == TECLA::K_DER) {
            if (x != pos_x_reg) {
                x = pos_x_reg;
                gotoxy(pos_x_reg, 0);
            }
        }
    }
    //Menu menu;
    //menu.initMenu();
    return 0;
}
