#include "App.h"

void App::mostrarOpciones(HANDLE hConsole, int select) {
    gotoxy(0, 0);
    printSelectLine(hConsole, { "> Iniciar Sesion", "> Registro" }, select, 10);
}

void App::init() {
    mostrarOpciones(hConsole);
    int y = 0, pos_y_login = 0, pos_y_reg = 1;
    gotoxy(2, y);

    while (true) {
        TECLA tecla = getTecla();
        if (tecla == TECLA::K_ENTER) break;
        else if (tecla == TECLA::K_ABAJO)   y = pos_y_reg;
        else if (tecla == TECLA::K_ARRIBA)  y = pos_y_login;

        mostrarOpciones(hConsole, y);
        gotoxy(2, y);
    }

    system("cls");
    string msg = y ? "Registrate\n" : "Iniciar sesion\n";
    printColoredLine(hConsole, { make_pair(msg, FOREGROUND_RED | FOREGROUND_INTENSITY), make_pair("Ingrese sus datos", 6) });
    
    if (y) registro();
    else login();
    
    system("cls");

    if (usuario.isAdmin()) {
        Menu menu;
        menu.initMenu(carrito);
    }
    
    system("cls");

    cout << "Pagar\t\t    Salir" << endl;
    y = 0;
    while (true) {
        TECLA tecla = getTecla();
        if (tecla == TECLA::K_ENTER) break;
        y = tecla == TECLA::K_DER ? 1 : 0;
        y ? gotoxy(20, 0) : gotoxy(0, 0);
    }
    if (y) exit(EXIT_SUCCESS);
    Vistas::pagar(hConsole, carrito);
}