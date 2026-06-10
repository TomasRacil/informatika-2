#include "Vybaveni.h"

int Vybaveni::pocetKusu = 0;

Vybaveni::Vybaveni(const std::string& kod, double hmotnost)
    : kodOznaceni(kod), hmotnost(hmotnost) {
    pocetKusu++;
}

Vybaveni::~Vybaveni() {
    pocetKusu--;
}

int Vybaveni::getPocetKusu() {
    return pocetKusu;
}

std::string Vybaveni::getKodOznaceni() const {
    return kodOznaceni;
}

double Vybaveni::getHmotnost() const {
    return hmotnost;
}

std::ostream& operator<<(std::ostream& os, const Vybaveni& vybaveni) {
    os << vybaveni.kodOznaceni << " (hmotnost: " << vybaveni.hmotnost << " kg)";
    return os;
}
