#include "BalistickaOchrana.h"

BalistickaOchrana::BalistickaOchrana(const std::string& kod, double hmotnost, int tridaOdolnosti)
    : Vybaveni(kod, hmotnost), tridaOdolnosti(tridaOdolnosti) {}

void BalistickaOchrana::pripravKAkci() {
    std::cout << "* Kontrola celistvosti balisticke ochrany " << getKodOznaceni()
              << " (trida odolnosti: T" << tridaOdolnosti << "). *" << std::endl;
}
