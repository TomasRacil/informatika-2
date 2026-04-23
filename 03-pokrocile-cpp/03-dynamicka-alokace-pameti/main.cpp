#include <iostream>
#include <new> // Pro std::bad_alloc

int main() {
    // --- 1. Alokace a uvolnění JEDNOHO prvku ---
    std::cout << "--- 1. Alokace a uvolneni jednoho prvku ---" << std::endl;
    int* pCislo = nullptr;

    try {
        pCislo = new int; // Alokujeme paměť pro jeden int na haldě
        std::cout << "Pamet pro int alokovana na adrese: " << pCislo << std::endl;

        *pCislo = 123; // Zapíšeme hodnotu do alokované paměti
        std::cout << "Hodnota na alokovane adrese: " << *pCislo << std::endl;

        delete pCislo; // UVOLNÍME paměť
        std::cout << "Pamet pro int uvolnena." << std::endl;
        pCislo = nullptr; // Nastavíme ukazatel na null, aby neukazoval na neplatnou paměť

        // POZOR: Přístup k paměti po delete je chyba!
        // if (pCislo != nullptr) {
        //     std::cout << *pCislo; // Toto by mohlo spadnout nebo vypsat nesmysl
        // }

    } catch (const std::bad_alloc& e) {
        std::cerr << "Chyba alokace pameti: " << e.what() << std::endl;
    }


    // --- 2. Alokace a uvolnění POLE ---
    std::cout << "\n--- 2. Alokace a uvolneni pole ---" << std::endl;
    int velikost = 5;
    int* pPole = nullptr;

    try {
        pPole = new int[velikost]; // Alokujeme paměť pro pole 5 intů
        std::cout << "Pamet pro pole " << velikost << " int alokovana na adrese: " << pPole << std::endl;

        // Naplníme pole hodnotami
        for (int i = 0; i < velikost; ++i) {
            pPole[i] = (i + 1) * 10;
        }

        // Vypíšeme pole
        std::cout << "Obsah dynamickeho pole: ";
        for (int i = 0; i < velikost; ++i) {
            std::cout << pPole[i] << " ";
        }
        std::cout << std::endl;

        delete[] pPole; // UVOLNÍME paměť alokovanou pro POLE
        std::cout << "Pamet pro pole uvolnena." << std::endl;
        pPole = nullptr;

    } catch (const std::bad_alloc& e) {
        std::cerr << "Chyba alokace pameti pro pole: " << e.what() << std::endl;
    }

    // --- 3. Dynamická alokace 2D pole (pole ukazatelů) ---
    std::cout << "\n--- 3. Dynamicka alokace 2D pole ---" << std::endl;
    int radky = 3;
    int sloupce = 4;
    int** pPole2D = nullptr;

    try {
        // Krok 1: Alokace pole ukazatelů (pro řádky)
        pPole2D = new int*[radky];
        std::cout << "Alokovano pole " << radky << " ukazatelu na adrese: " << pPole2D << std::endl;

        // Krok 2: Alokace každého jednotlivého řádku (pole intů)
        for (int i = 0; i < radky; ++i) {
            pPole2D[i] = new int[sloupce];
            std::cout << "  - Alokovan radek " << i << " (" << sloupce << " int) na adrese: " << pPole2D[i] << std::endl;
        }

        // Naplnění 2D pole
        std::cout << "Naplnuji 2D pole..." << std::endl;
        for (int i = 0; i < radky; ++i) {
            for (int j = 0; j < sloupce; ++j) {
                pPole2D[i][j] = (i + 1) * 10 + (j + 1);
            }
        }

        // Výpis 2D pole
        std::cout << "Obsah dynamickeho 2D pole:" << std::endl;
        for (int i = 0; i < radky; ++i) {
            for (int j = 0; j < sloupce; ++j) {
                std::cout << pPole2D[i][j] << "\t"; // Použijeme tabulátor pro zarovnání
            }
            std::cout << std::endl;
        }

        // UVOLNĚNÍ 2D POLE (MUSÍ být v opačném pořadí než alokace!)
        std::cout << "Uvolnuji 2D pole..." << std::endl;
        
        // Krok 1: Uvolnění každého jednotlivého řádku
        for (int i = 0; i < radky; ++i) {
            std::cout << "  - Uvolnuji radek " << i << " na adrese: " << pPole2D[i] << std::endl;
            delete[] pPole2D[i];
            pPole2D[i] = nullptr; // Dobrá praxe
        }

        // Krok 2: Uvolnění pole ukazatelů
        std::cout << "Uvolnuji pole ukazatelu na adrese: " << pPole2D << std::endl;
        delete[] pPole2D;
        pPole2D = nullptr;

        std::cout << "Pamet pro 2D pole kompletne uvolnena." << std::endl;

    } catch (const std::bad_alloc& e) {
        std::cerr << "Chyba alokace pameti pro 2D pole: " << e.what() << std::endl;
        // Poznámka: Pokud alokace selže uprostřed (např. při alokaci 3. řádku),
        // správně bychom měli uvolnit již alokované řádky předcházející
        // a pole ukazatelů. Pro zjednodušení to zde neděláme.
    }


    // --- 4. Ukázka ÚNIKU PAMĚTI (Memory Leak) ---
    std::cout << "\n--- 4. Demonstrace uniku pameti (nedelejte to!) ---" << std::endl;
    for (int i = 0; i < 3; ++i) {
        int* pUnik = new int(i);
        std::cout << "Alokovano " << *pUnik << " na adrese " << pUnik << std::endl;
        // CHYBA: Zapomněli jsme 'delete pUnik;'
        // Ukazatel pUnik zanikne na konci cyklu, ale paměť zůstane alokovaná
    }
    std::cout << "Cyklus skoncil. 3 bloky pameti zustaly alokovane (memory leak)." << std::endl;


    // --- 5. Nebezpečí - Dvojité uvolnění (Double Free) ---
    std::cout << "\n--- 5. Demonstrace dvojiteho uvolneni (nedelejte to!) ---" << std::endl;
    int* pNebezpecny = new int(99);
    std::cout << "Alokovano " << *pNebezpecny << " na " << pNebezpecny << std::endl;
    delete pNebezpecny;
    std::cout << "Pamet uvolnena poprve." << std::endl;
    // pNebezpecny = nullptr; // TOTO by zabránilo chybě níže
    // delete pNebezpecny; // CHYBA: Pokus o uvolnění již uvolněné paměti. Může (a často i způsobí) pád programu.
    std::cout << "!!! Pokud program nespadl pri druhem delete, meli jsme stesti !!!" << std::endl;


    return 0;
}