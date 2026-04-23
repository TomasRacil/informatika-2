/*
 * Příklad: Zpracování argumentů příkazové řádky v C++
 *
 * Tento program očekává argumenty ve formátu:
 * ./program <cislo1> <cislo2> [-v|--verbose]
 *
 * Příklad použití:
 * ./a.out 10 20
 * ./a.out 10 20 -v
 * ./a.out --help
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // pro std::atoi, ale lépe použít std::stoi ze string

// Funkce pro nápovědu
void vypis_napovedu(const std::string& nazev_programu) {
    std::cout << "Použití: " << nazev_programu << " <cislo1> <cislo2> [prepinace]" << std::endl;
    std::cout << "Sečte dvě celá čísla." << std::endl;
    std::cout << "Přepínače:" << std::endl;
    std::cout << "  -h, --help     Zobrazí tuto nápovědu" << std::endl;
    std::cout << "  -v, --verbose  Zapne detailní výpis" << std::endl;
}

int main(int argc, char* argv[]) {
    // argc (ARGument Count): Počet argumentů (včetně názvu programu)
    // argv (ARGument Vector): Pole řetězců (C-style stringů)

    // 1. Převedeme C-style pole na std::vector<std::string> pro pohodlnější práci
    // (není to nutné, ale v C++ modernější a bezpečnější než práce s pointery)
    std::vector<std::string> argumenty;
    for (int i = 0; i < argc; ++i) {
        argumenty.push_back(std::string(argv[i]));
    }

    // 2. Kontrola základních přepínačů (např. help)
    // Procházíme od 1, protože index 0 je název programu
    for (const auto& arg : argumenty) {
        if (arg == "-h" || arg == "--help") {
            vypis_napovedu(argumenty[0]);
            return 0; // Konec programu (úspěch)
        }
    }

    // 3. Validace počtu argumentů
    // Očekáváme minimálně: program, cislo1, cislo2 (tedy 3 argumenty)
    if (argumenty.size() < 3) {
        std::cerr << "CHYBA: Nedostatek argumentů!" << std::endl;
        vypis_napovedu(argumenty[0]);
        return 1; // Konec programu (chyba)
    }

    // 4. Parsování čísel a zpracování přepínačů
    int cislo1 = 0;
    int cislo2 = 0;
    bool verbose = false;

    try {
        // argv[1] je první číslo, argv[2] je druhé číslo
        cislo1 = std::stoi(argumenty[1]); // string to int
        cislo2 = std::stoi(argumenty[2]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "CHYBA: Zadané argumenty nejsou platná čísla!" << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "CHYBA: Číslo je příliš velké!" << std::endl;
        return 1;
    }

    // Kontrola volitelného přepínače (může být kdekoliv od 3. pozice dál)
    for (size_t i = 3; i < argumenty.size(); ++i) {
        if (argumenty[i] == "-v" || argumenty[i] == "--verbose") {
            verbose = true;
        } else {
            std::cerr << "VAROVÁNÍ: Neznámý přepínač '" << argumenty[i] << "'" << std::endl;
        }
    }

    // 5. Vlastní logika
    if (verbose) {
        std::cout << "[LOG] Načteno číslo A: " << cislo1 << std::endl;
        std::cout << "[LOG] Načteno číslo B: " << cislo2 << std::endl;
        std::cout << "[LOG] Provádím sčítání..." << std::endl;
    }

    int soucet = cislo1 + cislo2;
    std::cout << "Výsledek: " << soucet << std::endl;

    return 0;
}