#pragma once

#include "Vybaveni.h"

class BalistickaOchrana : public Vybaveni {
private:
    int tridaOdolnosti;

public:
    BalistickaOchrana(const std::string& kod, double hmotnost, int tridaOdolnosti);
    
    void pripravKAkci() override;
};
