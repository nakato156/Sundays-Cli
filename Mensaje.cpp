#include "Mensaje.h"
void Mensaje::guardarReclamo() {
    std::ofstream archivo("reclamo.txt");
    if (archivo.is_open()) {
        archivo << reclamo;
        archivo.close();
        std::cout << "Reclamo guardado correctamente en reclamo.txt" << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo para guardar el reclamo." << std::endl;
    }
}
