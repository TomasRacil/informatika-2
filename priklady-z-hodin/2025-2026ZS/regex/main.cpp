#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <iterator>
#include <set>
#include <list>

std::string nactiSoubor(const std::string& nazev) {
    std::ifstream soubor(nazev);
    if (!soubor.is_open()) {
        std::cerr << "CHYBA: Nelze otevrit soubor '" << nazev << "'." << std::endl;
        std::cerr << "Ujistete se, ze jste ho stahli (viz README.md)." << std::endl;
        return "";
    }
    
    // Využijeme iterátory pro načtení celého souboru naraz
    return std::string((std::istreambuf_iterator<char>(soubor)),
                        std::istreambuf_iterator<char>());
}

void analyzujRoboty(const std::string& text) {
    std::cout << "--- Analyza slova Robot ---" << std::endl;
    std::regex re(R"([Rr]obot[\w]*)");
    
    std::smatch shody;
    std::string::const_iterator startHledani = text.cbegin();
    int pocitadlo = 0;
    
    while (std::regex_search(startHledani, text.cend(), shody, re)) {
        pocitadlo++;
        startHledani = shody[0].second;
    }

    std::cout << "Pocet vyskytu slova s korenem 'Robot': " 
              << pocitadlo << std::endl << std::endl;
}

void najdiPrimouRec(const std::string& text) {
    std::cout << "--- Prvnich 5 vet v uvozovkach ---" << std::endl;
    std::regex re(R"("[^"]*")");
    
    std::smatch shody;
    std::string::const_iterator startHledani = text.cbegin();
    int pocitadlo = 0;

    while (std::regex_search(startHledani, text.cend(), shody, re) && pocitadlo < 5) {
        std::cout << (pocitadlo + 1) << ". " << shody[0].str() << std::endl;
        pocitadlo++;
        startHledani = shody[0].second;
    }
    std::cout << std::endl;
}

void najdiLetopocty(const std::string& text) {
    std::cout << "--- Nalezene letopocty ---" << std::endl;
    std::regex re(R"(\b\d{4}\b)");
    
    std::smatch shody;
    std::string::const_iterator startHledani = text.cbegin();
    std::list<std::string> letopocty;

    while (std::regex_search(startHledani, text.cend(), shody, re)) {
        letopocty.push_back(shody[0].str());
        startHledani = shody[0].second;
    }

    for (const auto& rok : letopocty) {
        std::cout << rok << " ";
    }
    if (letopocty.empty()) std::cout << "Zadne letopocty nenalezeny.";
    std::cout << std::endl << std::endl;
}

void najdiPostavy(const std::string& text) {
    std::cout << "--- Nalezene postavy (mluvci) ---" << std::endl;
    std::regex re(R"(\n([A-Z][a-z]+):)");
    
    std::smatch shody;
    std::string::const_iterator startHledani = text.cbegin();
    std::set<std::string> postavy;

    while (std::regex_search(startHledani, text.cend(), shody, re)) {
        postavy.insert(shody[1].str()); 
        startHledani = shody[0].second;
    }

    for (const auto& postava : postavy) {
        std::cout << postava << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << "Nacitam knihu..." << std::endl;
    std::string text = nactiSoubor("kniha.txt");
    
    if (text.empty()) {
        return 1;
    }

    std::cout << "Kniha nactena. Velikost: " << text.length() << " znaku.\n" << std::endl;

    analyzujRoboty(text);
    najdiPrimouRec(text);
    najdiLetopocty(text);
    najdiPostavy(text);

    return 0;
}