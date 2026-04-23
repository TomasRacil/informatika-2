#include <iostream>
#include <vector>     // Pro std::vector
#include <map>        // Pro std::map
#include <string>     // Pro std::string
#include <algorithm>  // Pro std::sort a std::for_each
#include <list>       // Pro std::list

// Pomocná funkce pro výpis prvků vektoru
void vypisVektor(const std::vector<int>& vec) {
    std::cout << "[ ";
    // Použití "range-based for loop" (od C++11)
    for (int hodnota : vec) {
        std::cout << hodnota << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    
    // --- 1. std::vector (Dynamické pole) ---
    std::cout << "--- std::vector ---" << std::endl;
    std::vector<int> cisla; // Vytvoření prázdného vektoru
    
    // Přidávání prvků na konec
    cisla.push_back(30);
    cisla.push_back(10);
    cisla.push_back(20);

    std::cout << "Puvodni vektor: ";
    vypisVektor(cisla);

    std::cout << "Velikost vektoru: " << cisla.size() << std::endl;
    std::cout << "Prvek na indexu 1: " << cisla[1] << std::endl; // Přístup jako u pole

    // Použití algoritmu std::sort z <algorithm>
    // Sort vyžaduje iterátory na začátek a konec
    std::sort(cisla.begin(), cisla.end());

    std::cout << "Serazeny vektor: ";
    vypisVektor(cisla);


    // --- 2. std::map (Asociativní pole / Slovník) ---
    std::cout << "\n--- std::map ---" << std::endl;
    // Mapování ze stringu (jméno) na int (věk)
    std::map<std::string, int> vekLidi;

    // Vkládání prvků
    vekLidi["Petr"] = 34;
    vekLidi["Jana"] = 28;
    vekLidi["Adam"] = 45;

    // Přístup k hodnotě pomocí klíče
    std::cout << "Vek Jany: " << vekLidi["Jana"] << std::endl;

    // Změna hodnoty
    vekLidi["Petr"] = 35;

    // Procházení mapy (pomocí iterátorů a C++11 'auto')
    std::cout << "Vypis mapy (serazeno podle klice):" << std::endl;
    for (auto const& [jmeno, vek] : vekLidi) { // C++17 structured binding
        std::cout << "  - " << jmeno << " ma " << vek << " let." << std::endl;
    }


    // --- 3. std::list (Oboustranně vázaný seznam) ---
    std::cout << "\n--- std::list ---" << std::endl;
    std::list<int> seznam;
    seznam.push_back(10);  // Přidá na konec [10]
    seznam.push_front(5);  // Přidá na začátek [5, 10]
    seznam.push_back(20);  // Přidá na konec [5, 10, 20]

    std::cout << "Vypis seznamu: ";
    // Pro list je bezpečnější použít iterátory nebo range-based for
    for (int hodnota : seznam) {
        std::cout << hodnota << " ";
    }
    std::cout << std::endl;
    
    // Seznam nemá operátor []. Přístup pouze přes iterátory.

    return 0;
}
