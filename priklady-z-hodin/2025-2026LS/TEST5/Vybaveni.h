#pragma once

#include <string>
#include <iostream>

class Vybaveni {
private:
    std::string kodOznaceni;
    double hmotnost;
    static int pocetKusu;

public:
    Vybaveni(const std::string& kod, double hmotnost);
    virtual ~Vybaveni();

    static int getPocetKusu();
    virtual void pripravKAkci() = 0;

    std::string getKodOznaceni() const;
    double getHmotnost() const;

    friend std::ostream& operator<<(std::ostream& os, const Vybaveni& vybaveni);
};
