#include <iostream>
#include <fstream>
#include <string>

class Mensaje {
private:
    std::string reclamo;

public:
    Mensaje() = default;
    void guardarReclamo(const std::string& nuevoReclamo) {
        std::ofstream archivo("reclamo.txt", std::ios_base::app); // para que los nuevos reclamos puedan ser ingresados al final del archivo

        if (archivo.is_open()) {
            archivo << nuevoReclamo << "\n";
            archivo.close();
            std::cout << "Reclamo guardado correctamente." << std::endl;
        }
        else {
            std::cout << "No se pudo abrir el archivo para guardar el reclamo." << std::endl;
        }
    }

    
};
