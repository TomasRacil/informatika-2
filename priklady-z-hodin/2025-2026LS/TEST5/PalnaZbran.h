#pragma once

#include "Vybaveni.h"

class PalnaZbran : public Vybaveni {
private:
    int kadence;

public:
    PalnaZbran(const std::string& kod, double hmotnost, int kadence);
    
    void pripravKAkci() override;
    
    PalnaZbran operator+(const PalnaZbran& other) const;
};
