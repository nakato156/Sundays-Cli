#include <iostream>
#include "App.h"

using namespace std;


int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Usuario usuario;
    App app(hConsole, usuario);

    app.init();

    system("cls");
    if (!usuario.isLogged()) {
        cout << "Ha ocurrido un error" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
