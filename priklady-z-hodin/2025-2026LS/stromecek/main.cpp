#include <iostream>
#include <stdlib.h>
#include <ctime>

void stromek(int vyska, int sirka_kmene, int vyska_kmene);
void koruna(int vyska);
void kmen(int vyska, int sirka_kmene, int vyska_kmene);
int zkontroluj_vstup();

int main() {
    srand(std::time(0));

    std::cout<< "Zadejte vysku koruny stromu: ";
    int vyska = zkontroluj_vstup();
    

    std::cout << "Zadejte sirku kmene stromu: ";
    int sirka = zkontroluj_vstup();

    std::cout << "Zadejte vysku kmene stromu: ";
    int vyska_kmene= zkontroluj_vstup();

    stromek(vyska, sirka, vyska_kmene);
    
    return 0;
}

void stromek(int vyska, int sirka_kmene, int vyska_kmene)
{
    koruna(vyska);
    kmen(vyska, sirka_kmene, vyska_kmene);    
}

void koruna(int vyska)
{
    for (int i = 0; i < vyska; ++i) {
        for (int j = 0; j < vyska - i - 1; ++j) {
            std::cout << '-';
        }
        for (int k = 0; k < (2 * i + 1); ++k) {
            char c = (rand()%6==0) ? '$':'*';
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void kmen(int vyska, int sirka_kmene, int vyska_kmene)
{
    for (int i = 0; i < vyska_kmene; ++i) {
        for (int j = 0; j < (vyska - sirka_kmene / 2 - 1); ++j) {
            std::cout << '-';
        }
        for (int k = 0; k < sirka_kmene; ++k) {
            std::cout << '#';
        }
        std::cout << std::endl;
    }
}

int zkontroluj_vstup()
{
    int cislo;
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    try
    {
        std::cin>>cislo;
        if(cislo<0){
            throw std::runtime_error("Neplatne cislo");
        }
        return cislo;
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
