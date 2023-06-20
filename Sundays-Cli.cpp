#include <iostream>
//#include "helpers.h"
#include "Menu.h"

using namespace std;

int main() {
    srand(time(NULL));
    //cout << "\tIniciar sesion \t\t Registro" << endl;
    Menu menu;
    menu.initMenu();
    return 0;
}
