#include <iostream>

class Auto
{
private:
    std::string znacka;
    int rokVyroby;

public:
    Auto();
    Auto(std::string znacka, int rokVyroby);
    void nastavHodnoty(std::string znacka, int rokVyroby);
    void vypisInfo()
    {
        std::cout << "Vozidlo se znackou: " << znacka << " a rokem vyroby: " << rokVyroby << std::endl;
    }
    ~Auto();
};

class Produkt
{
private:
    std::string nazev;
    double cena;

public:
    Produkt(std::string nazev, double cena);
    ~Produkt();
};

int main()
{

    Produkt produkt1("Telefon", 5999.99);
    {
        Produkt produkt2("Televize", 15999.99);
    }
    Produkt *produkt3 = new Produkt("PC", 10999.99);

    delete produkt3;

    // Auto auto1("Skoda", 2010);
    // {
    //     Auto auto2("Fiat", 2005);
    // }

    // auto1.vypisInfo();
    // auto1.nastavHodnoty("Ford", 2015);
    // auto1.vypisInfo();

    return 0;
}

Auto::Auto()
{
    this->znacka = "";
    this->rokVyroby = 0;
}

Auto::Auto(std::string znacka, int rokVyroby)
{
    this->znacka = znacka;
    this->rokVyroby = rokVyroby;
}

void Auto::nastavHodnoty(std::string znacka, int rokVyroby)
{
    this->znacka = znacka;
    this->rokVyroby = rokVyroby;
}

Auto::~Auto()
{
    std::cout << znacka << " s rokem vyroby " << rokVyroby << " smazana" << std::endl;
}

Produkt::Produkt(std::string nazev, double cena)
{
    std::cout << "Vytvořen produkt: " << nazev << std::endl;
    this->nazev = nazev;
    this->cena = cena;
}

Produkt::~Produkt()
{
    std::cout << "Odstranen produkt: " << nazev << std::endl;
}
