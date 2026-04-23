#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Pro std::sort, std::find_if, std::count_if, std::for_each
#include <numeric>   // Pro std::accumulate

// Pomocná struktura pro demonstraci
struct Auto {
    std::string model;
    int rokVyroby;
};

// Pomocná funkce pro výpis vektoru (používá šablonu, kterou už známe)
template<typename T>
void vypisVektor(const std::string& nazev, const std::vector<T>& vec) {
    std::cout << nazev << ": [ ";
    for (const auto& prvek : vec) {
        std::cout << prvek << " ";
    }
    std::cout << "]" << std::endl;
}

// Specializovaná verze pro výpis vektoru Aut
void vypisVektorAut(const std::string& nazev, const std::vector<Auto>& vec) {
    std::cout << nazev << ":" << std::endl;
    for (const auto& autoObj : vec) {
        std::cout << "  - " << autoObj.model << " (" << autoObj.rokVyroby << ")" << std::endl;
    }
}


int main() {
    std::vector<int> cisla = {5, 1, 4, 2, 8, 3, 7, 6};
    vypisVektor("Puvodni cisla", cisla);

    // --- 1. std::sort s lambdou ---
    // Seřadíme čísla sestupně
    std::sort(cisla.begin(), cisla.end(), [](int a, int b) {
        return a > b; // Vlastní porovnávací logika
    });
    vypisVektor("Serazeno sestupne", cisla);

    // --- 2. std::find_if s lambdou ---
    std::cout << "\n--- find_if ---" << std::endl;
    int limit = 5;
    // Hledáme první prvek, který je VĚTŠÍ než 'limit'
    // 'limit' je zachycen hodnotou [limit]
    auto prvniVetsi = std::find_if(cisla.begin(), cisla.end(), [limit](int n) {
        return n > limit;
    });
    if (prvniVetsi != cisla.end()) {
        std::cout << "Prvni cislo vetsi nez " << limit << " je: " << *prvniVetsi << std::endl;
    }

    // --- 3. std::count_if s lambdou ---
    std::cout << "\n--- count_if ---" << std::endl;
    // Spočítáme počet sudých čísel
    int pocetSudych = std::count_if(cisla.begin(), cisla.end(), [](int n) {
        return (n % 2) == 0;
    });
    std::cout << "Pocet sudych cisel: " << pocetSudych << std::endl;

    // --- 4. std::transform (modifikace) ---
    std::cout << "\n--- transform ---" << std::endl;
    std::vector<int> dvojnasobky;
    dvojnasobky.resize(cisla.size()); // Připravíme místo v cílovém vektoru

    std::transform(cisla.begin(), cisla.end(), dvojnasobky.begin(), [](int n) {
        return n * 2;
    });
    vypisVektor("Zdvojnasobena cisla", dvojnasobky);

    // --- 5. std::for_each (provedení akce) ---
    std::cout << "\n--- for_each ---" << std::endl;
    int soucet = 0;
    // Sečteme všechny prvky. Musíme zachytit 'soucet' REFERENCÍ, abychom ho mohli měnit.
    std::for_each(cisla.begin(), cisla.end(), [&soucet](int n) {
        soucet += n;
    });
    std::cout << "Soucet (pres for_each): " << soucet << std::endl;
    
    // Poznámka: Pro součet je lepší použít std::accumulate (z <numeric>)
    int soucet2 = std::accumulate(cisla.begin(), cisla.end(), 0);
    std::cout << "Soucet (pres accumulate): " << soucet2 << std::endl;


    // --- 6. Příklad s objekty ---
    std::cout << "\n--- Priklad s objekty (Auto) ---" << std::endl;
    std::vector<Auto> auta = { {"Skoda", 2010}, {"BMW", 2022}, {"Audi", 2018} };

    // Seřadíme auta podle roku výroby (vzestupně)
    std::sort(auta.begin(), auta.end(), [](const Auto& a, const Auto& b) {
        return a.rokVyroby < b.rokVyroby;
    });
    
    vypisVektorAut("Auta serazena podle roku", auta);

    return 0;
}