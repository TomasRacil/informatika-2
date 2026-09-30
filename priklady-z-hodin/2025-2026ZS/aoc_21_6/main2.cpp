#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <cstdint>
#include <algorithm>

std::array<uint64_t, 9> nacti_data(std::string filename) {
    std::ifstream soubor(filename);
    if (!soubor.is_open()) {
        std::cerr << "Chyba: Soubor '" << filename << "' se nepodařilo otevřít!" << std::endl;
    }

    std::array<uint64_t, 9> pocty = {0};

    std::string radek, cislo_ryby;
    std::getline(soubor, radek);
    std::stringstream ss(radek);

    while (std::getline(ss, cislo_ryby, ',')) {
        int den = std::stoi(cislo_ryby);
        if (den >= 0 && den < pocty.size()) {
            pocty[den]++;
        }
    }
    return pocty;
}

uint64_t spocitej_ryby(const std::array<uint64_t, 9>& pocty) {
    uint64_t pocet_celkem = 0;
    for(auto pocet : pocty){
        pocet_celkem+=pocet;
    }
    return pocet_celkem;
}

void vytiskni_pocty(const std::array<uint64_t, 9>& pocty) {
    std::cout << "Aktualni stavy:" << std::endl;
    for (size_t i = 0; i < pocty.size(); ++i) {
        if (pocty[i] > 0) {
            std::cout << "  Den " << i << ": " << pocty[i] << " ryb" << std::endl;
        }
    }
}

void simuluj_ryby(std::array<uint64_t, 9>& ryby_pocty, int dny) {
    for (int den = 0; den < dny; den++) {

        std::rotate(ryby_pocty.begin(),
                    ryby_pocty.begin() + 1, 
                    ryby_pocty.end());

        ryby_pocty[6] += ryby_pocty[8];
    }
}

int main() {
    std::string filename = "data.txt";
    
    std::array<uint64_t, 9> ryby_pocty = nacti_data(filename);

    vytiskni_pocty(ryby_pocty);
    std::cout << "Pocatecni celkovy pocet ryb: " << spocitej_ryby(ryby_pocty) << std::endl;

    int dny_simulace = 256;
    simuluj_ryby(ryby_pocty, dny_simulace);

    std::cout << "\n--- Po " << dny_simulace << " dnech ---" << std::endl;
    std::cout << "Konecny celkovy pocet ryb: " << spocitej_ryby(ryby_pocty) << std::endl;

    return 0;
}