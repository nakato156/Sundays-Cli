#include "App.h"

void App::mostrarOpciones(HANDLE hConsole, int select) {
    gotoxy(0, 0);
    printSelectLine(hConsole, { "> Iniciar Sesion", "> Registro" }, select, 10);
}

void App::cargarDatos() {
    DataFrame file;
    file.read_csv(filenameComida);
    for (int i = 0; i < 200; i++) {
        Fila fila = file[i];
        productos.Insertar( Producto(fila["Id"], fila["Nombre"], fila["Tipo"], stof(fila["precio"]) ));
    }
}

void App::init() {
    cargarDatos();
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
    if (!usuario.isLogged()) {
        cout << "Datos incorrectos" << endl;
        exit(EXIT_FAILURE);
    }
    if (usuario.isAdmin()) {
        Vistas::admin(hConsole, usuario);
        exit(EXIT_SUCCESS);
    }
    Menu menu;
    menu.initMenu(carrito);
    
    system("cls");

    cout << "Pagar\t\t    Historial\t\t Reclamo\t\tSalir" << endl;

    pair<int, int> pos = selectOpcion(0, 4, 0, 0, 20);
    int opcion = pos.first;
    if (opcion == 3) exit(EXIT_SUCCESS);
    else if (opcion == 2) Vistas::ingresarReclamo(hConsole);
    else if (opcion == 1) Vistas::historial(hConsole, usuario, productos);
    else if(opcion == 0) Vistas::pagar(hConsole, carrito, usuario);
}