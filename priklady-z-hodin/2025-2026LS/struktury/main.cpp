#include <iostream>
#include <string>

struct Kniha {
    std::string nazev;
    std::string autor;
    int rokVydani;
    double cena;
};

void vypisKnihu(Kniha k) {
    std::cout << "  Nazev: " << k.nazev << std::endl;
    std::cout << "  Autor: " << k.autor << std::endl;
    std::cout << "  Rok vydani: " << k.rokVydani << std::endl;
    std::cout << "  Cena: " << k.cena << " CZK" << std::endl<<std::endl;
}

int main() {
    Kniha knihy[3] = {
        {"Hobit", "J.R.R. Tolkien", 1937, 299.0},
        {"1984", "George Orwell", 1949, 249.5},
        {"Maly princ", "Antoine de Saint-Exupery", 1943, 400.0}
    };


    std::cout << "\nSeznam vsech knih" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Kniha " << i + 1 << ":" << std::endl;
        vypisKnihu(knihy[i]);
    }

    std::cout << "\nHledani nejdrazsi knihy" << std::endl;
    if (sizeof(knihy) / sizeof(knihy[0]) == 0) {
        std::cout << "Pole knih je prázdné." << std::endl;
    } else {
        Kniha nejdrazsiKniha = knihy[0];

        for (int i = 1; i < 3; ++i) {
            if (knihy[i].cena > nejdrazsiKniha.cena) {
                nejdrazsiKniha = knihy[i];
            }
        }

        std::cout << "Nejdrazsi kniha je:" << std::endl;
        vypisKnihu(nejdrazsiKniha);
    }

    return 0;
}
