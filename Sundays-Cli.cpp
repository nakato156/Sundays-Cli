#include <iostream>
#include "App.h"

using namespace std;


int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Usuario usuario;
    App app(hConsole, usuario);

    app.init();
    return 0;
}
