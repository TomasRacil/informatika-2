#include "PalnaZbran.h"

PalnaZbran::PalnaZbran(const std::string& kod, double hmotnost, int kadence)
    : Vybaveni(kod, hmotnost), kadence(kadence) {}

void PalnaZbran::pripravKAkci() {
    std::cout << "* Nabijeni zbrane " << getKodOznaceni() 
              << ", nastaveni kadence na " << kadence << " ran/min. *" << std::endl;
}

PalnaZbran PalnaZbran::operator+(const PalnaZbran& other) const {
    return PalnaZbran(
        getKodOznaceni() + " a " + other.getKodOznaceni(),
        getHmotnost() + other.getHmotnost(),
        kadence + other.kadence
    );
}
