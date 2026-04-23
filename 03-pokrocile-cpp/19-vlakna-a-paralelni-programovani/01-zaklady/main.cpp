#include <iostream>
#include <thread>   // Hlavní knihovna pro vlákna
#include <vector>
#include <chrono>   // Pro práci s časem (sleep)

// --- ČÁST 1: Základy spouštění vláken ---

// Funkce, kterou bude vykonávat vlákno
// Přijímá ID a čas, jak dlouho má "pracovat"
void pracuj(int id, int doba_ms) {
    std::cout << "Vlakno " << id << " zacina pracovat..." << std::endl;
    
    // Simulace práce (uspání vlákna)
    std::this_thread::sleep_for(std::chrono::milliseconds(doba_ms));
    
    std::cout << "Vlakno " << id << " dokoncilo praci." << std::endl;
}

// --- ČÁST 2: Ukázka Race Condition (Souběhu) ---

// Sdílená globální proměnná
// Není chráněna žádným mutexem ani není atomická (std::atomic).
int sdilene_pocitadlo = 0;

void inkrementuj(int pocet_iteraci) {
    for (int i = 0; i < pocet_iteraci; ++i) {
        // Operace ++ vypadá v C++ jako jeden příkaz, ale procesor ji provádí ve 3 krocích:
        // 1. READ:   Načti hodnotu z paměti do registru CPU.
        // 2. MODIFY: Zvyš hodnotu v registru o 1.
        // 3. WRITE:  Ulož hodnotu z registru zpět do paměti.
        
        // Pokud dojde k přepnutí kontextu (Context Switch) mezi krokem 1 a 3,
        // vlákna si navzájem přepíší výsledky. Jedno vlákno "nevidí" změnu druhého.
        sdilene_pocitadlo++;
    }
}

int main() {
    // ---------------------------------------------------------
    // 1. Spouštění vláken (Základ)
    // ---------------------------------------------------------
    std::cout << "=== CAST 1: Zakladni prace s vlakny ===" << std::endl;

    std::thread t1(pracuj, 1, 500); 

    std::vector<std::thread> skupina_vlaken;
    for (int i = 2; i <= 4; ++i) {
        // emplace_back vytvoří vlákno přímo ve vektoru
        skupina_vlaken.emplace_back(pracuj, i, 200 * i);
    }

    // Čekání na dokončení (join)
    if (t1.joinable()) t1.join();
    for (auto& t : skupina_vlaken) {
        if (t.joinable()) t.join();
    }

    std::cout << "Vsechna pracujici vlakna hotova.\n" << std::endl;

    // ---------------------------------------------------------
    // 2. Demonstrace chyby Race Condition
    // ---------------------------------------------------------
    std::cout << "=== CAST 2: Demonstrace Race Condition ===" << std::endl;
    
    // Budeme inkrementovat velké číslo, aby se stihlo projevit přepínání vláken plánovačem
    const int POCET_ITERACI = 1000000;
    
    std::cout << "Spoustim 2 vlakna, kazde pripocte " << POCET_ITERACI << " k pocitadlu." << std::endl;
    std::cout << "Ocekavana vysledna hodnota: " << (2 * POCET_ITERACI) << std::endl;

    // Vytvoření dvou vláken nad stejnou funkcí a sdílenou proměnnou
    std::thread ta(inkrementuj, POCET_ITERACI);
    std::thread tb(inkrementuj, POCET_ITERACI);

    // Počkáme, až obě doběhnou
    ta.join();
    tb.join();

    std::cout << "Skutecna vysledna hodnota:  " << sdilene_pocitadlo << std::endl;
    std::cout << "Rozdil (chyby):             " << (2 * POCET_ITERACI) - sdilene_pocitadlo << std::endl;

    if (sdilene_pocitadlo != 2 * POCET_ITERACI) {
        std::cout << "\n[!] Nastala chyba soubehu (Race Condition)!" << std::endl;
        std::cout << "Hodnota je nizsi, protoze se nektere inkrementace 'ztratily' pri prepisu." << std::endl;
        std::cout << "Resenim je pouzit std::mutex nebo std::atomic (viz dalsi lekce)." << std::endl;
    } else {
        std::cout << "\n[?] Nahodou to vyslo spravne. Zkuste program spustit znovu nebo zvysit pocet iteraci." << std::endl;
    }

    return 0;
}