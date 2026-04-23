#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Sdílená proměnná (bankovní účet)
int zustatek = 1000;

// Mutex pro ochranu přístupu k 'zustatek'
std::mutex mtx;

// Funkce simulující výběr z bankomatu
void vyberPenez(int castka, int id_vlakna) {
    // Zkusíme zamknout mutex. Pokud je zamčený někým jiným, 
    // toto vlákno zde počká, dokud se neuvolní.
    mtx.lock(); 
    
    // --- KRITICKÁ SEKCE (začátek) ---
    // Zde má přístup vždy jen jedno vlákno.
    
    std::cout << "[Vlakno " << id_vlakna << "] Kontroluji zustatek..." << std::endl;
    
    if (zustatek >= castka) {
        std::cout << "[Vlakno " << id_vlakna << "] Vyber schvalen: " << castka << std::endl;
        // Simulace zpoždění (kdyby tu nebyl mutex, jiné vlákno by mezitím mohlo změnit zůstatek)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        zustatek -= castka;
    } else {
        std::cout << "[Vlakno " << id_vlakna << "] Zamitnuto! Nedostatek penez." << std::endl;
    }
    
    std::cout << "[Vlakno " << id_vlakna << "] Novy zustatek: " << zustatek << std::endl;
    
    // --- KRITICKÁ SEKCE (konec) ---
    
    mtx.unlock(); // Vždy musíme odemknout!
}

/* Modernější verze s std::lock_guard (RAII)
   Toto je bezpečnější, protože odemkne mutex i v případě chyby/výjimky.
*/
void vkladPenez(int castka) {
    std::lock_guard<std::mutex> zamek(mtx); 
    // Mutex se zamkne v konstruktoru 'zamek'
    
    zustatek += castka;
    std::cout << "[Vklad] Vlozeno: " << castka << ". Novy zustatek: " << zustatek << std::endl;
    
    // Mutex se odemkne automaticky v destruktoru 'zamek' na konci funkce
}

int main() {
    std::cout << "Pocatecni zustatek: " << zustatek << std::endl;

    std::vector<std::thread> vlakna;

    // Spustíme 5 vláken, která se pokusí vybrat peníze SOUČASNĚ
    for (int i = 0; i < 5; ++i) {
        vlakna.emplace_back(vyberPenez, 800, i);
    }

    // A jedno, které vloží
    vlakna.emplace_back(vkladPenez, 2000);

    for (auto& t : vlakna) {
        t.join();
    }

    return 0;
}