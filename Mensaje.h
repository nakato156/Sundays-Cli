#include <iostream>
#include <fstream>
#include <string>

class Mensaje {
private:
    std::string reclamo;

public:
    Mensaje(const std::string& reclamo) : reclamo(reclamo) {}
    void guardarReclamo();
    
};
