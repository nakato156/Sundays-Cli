#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class Promociones {
public:
    Promociones() {}
    ~Promociones() {}
    vector <string> meses = { "Enero",  "Febrero", "Marzo", "Abril",  "Mayo", "Junio", "Julio", "Agosto", "Setiembre", "Octubre", "Noviembre", " Diciembre" };
    vector <string> prom = { "2da bebida gratis", "2da hamburguesa a mitad de precio", "Barra libre a 60", "15% de descuento en Alitas BBQ", "3X2 en cervezas artesanales", "10% de descuento en desayunos", "Happy Hour de 3 a 4 pm" };
    void promocionDelDia() {
        int dia = 1 + rand() % 31;
        string mes = meses[rand() % 12];
        string promo = prom[rand() % 7];
        cout << "Hoy " << dia << " de " << mes << " la promocion es " << promo;
    }
};

class AboutUs {
public:
    AboutUs() {}
    ~AboutUs() {}
    void Nosotros() {
        cout << "Desde que inauguramos el primer Sundays en Lima, en 2005 en el distrito de San Miguel, los momentos relajados y reconfortantes tenian su lugar de encuentro. En Sundays, cada dia de la semana se siente como un domingo. " << endl;
        cout << "Gracias a la calida acogida que recibimos, hemos expandido nuestros locales a diferentes puntos de la ciudad, incluyendo San Isidro, Barranco y Surco." << endl;
        cout << "En 2010, decidimos llevar la experiencia Sundays a otras ciudades del pais y abrimos nuestras puertas en Iquitos y Cajamarca, brindando el mismo ambiente acogedor y deliciosos platos" << endl;
        cout << "Hoy en dia, Sundays se ha convertido en el lugar favorito para aquellos que buscan relajarse, disfrutar de exquisitos platos y deleitarse con nuestra atención excepcional. " << endl;
        cout << endl;
    }
};


int main()
{
    srand(time(NULL));
    Promociones prom;
    AboutUs descripcion;
    descripcion.Nosotros();
    prom.promocionDelDia();
    return 0;
}
