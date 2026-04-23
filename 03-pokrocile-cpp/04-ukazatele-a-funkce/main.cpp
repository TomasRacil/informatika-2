#include <iostream>

// --- 1. Předání hodnotou vs. ukazatelem ---

void nezmeni(int a) {
    a = 100;
    std::cout << "   -> Hodnota 'a' uvnitr nezmeni(): " << a << std::endl;
}

void zmeni(int* pA) { // Parametr je ukazatel
    if (pA != nullptr) { // Kontrola platnosti ukazatele
        *pA = 100; // Změna hodnoty na adrese
        std::cout << "   -> Hodnota '*pA' uvnitr zmeni(): " << *pA << std::endl;
    } else {
        std::cout << "   -> Chyba: Byl predan neplatny ukazatel (nullptr)!" << std::endl;
    }
}

// --- 2. Předání pole funkci ---

// Funkce přijímá ukazatel na první prvek a velikost
void vynulujPole(int* arr, int velikost) {
    std::cout << "   -> Nuluji pole na adrese: " << arr << std::endl;
    for (int i = 0; i < velikost; ++i) {
        arr[i] = 0; // Modifikujeme původní pole
    }
}

// Ekvivalentní zápis (kompilátor to stále vidí jako int* arr)
/*
void vynulujPole(int arr[], int velikost) {
    std::cout << "   -> Nuluji pole (zapis arr[]): " << arr << std::endl;
    for (int i = 0; i < velikost; ++i) {
        arr[i] = 0;
    }
}
*/

void vypisPole(int* arr, int velikost) {
    std::cout << "[ ";
    for (int i = 0; i < velikost; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]" << std::endl;
}


// --- 3. Návrat ukazatele z funkce ---

int* vytvorDynamickePole(int velikost) {
    if (velikost <= 0) {
        return nullptr;
    }
    std::cout << "   -> Alokuji dynamicke pole velikosti " << velikost << std::endl;
    int* pPole = nullptr;
    try {
         pPole = new int[velikost];
         // Inicializace
         for(int i = 0; i < velikost; ++i) {
             pPole[i] = i * i; // Naplníme druhými mocninami
         }
    } catch (const std::bad_alloc& e) {
        std::cerr << "   -> Chyba alokace v createDynamicArray: " << e.what() << std::endl;
        return nullptr; // Vracíme nullptr při chybě
    }
    return pPole; // Vracíme adresu alokovaného pole
}

// --- 4. Špatný příklad - NIKDY NEDĚLAT ---
int* spatnaFunkce() {
    int lokalniCislo = 50;
    std::cout << "   -> Adresa lokalni promenne uvnitr spatnaFunkce(): " << &lokalniCislo << std::endl;
    return &lokalniCislo; // Vracíme adresu paměti, která zanikne!
}


int main() {
    std::cout << "--- 1. Predani hodnotou vs. ukazatelem ---" << std::endl;
    int x = 10;
    std::cout << "Puvodni x: " << x << std::endl;
    nezmeni(x);
    std::cout << "x po volani nezmeni(x): " << x << std::endl;
    zmeni(&x); // Předáme adresu proměnné x
    std::cout << "x po volani zmeni(&x): " << x << std::endl;
    // Zkusíme předat nullptr
    zmeni(nullptr);


    std::cout << "\n--- 2. Predani pole funkci ---" << std::endl;
    int mojePole[] = {1, 2, 3, 4, 5};
    int n = sizeof(mojePole) / sizeof(mojePole[0]);
    std::cout << "Puvodni pole: ";
    vypisPole(mojePole, n);
    vynulujPole(mojePole, n); // Předáme pole (rozpadne se na ukazatel) a velikost
    std::cout << "Pole po vynulovani: ";
    vypisPole(mojePole, n);


    std::cout << "\n--- 3. Navrat ukazatele z funkce ---" << std::endl;
    int vel = 5;
    int* pMojeDynPole = vytvorDynamickePole(vel);

    if (pMojeDynPole != nullptr) {
        std::cout << "Dynamicke pole vytvoreno na adrese: " << pMojeDynPole << std::endl;
        std::cout << "Obsah: ";
        vypisPole(pMojeDynPole, vel);

        // Změna hodnoty
        pMojeDynPole[1] = 99;
        std::cout << "Obsah po zmene: ";
        vypisPole(pMojeDynPole, vel);

        std::cout << "   -> Uvolnuji dynamicke pole v main()..." << std::endl;
        delete[] pMojeDynPole; // Musíme paměť uvolnit!
        pMojeDynPole = nullptr;
    } else {
        std::cout << "Nepodarilo se vytvorit dynamicke pole." << std::endl;
    }


    std::cout << "\n--- 4. Navrat ukazatele na lokalni promennou (NEBEZPECI!) ---" << std::endl;
    int* pSpatny = spatnaFunkce();
    std::cout << "Ukazatel pSpatny ukazuje na (jiz neplatnou) adresu: " << pSpatny << std::endl;
    // Následující řádek je velmi nebezpečný!
    // Může vypsat nesmysl, nebo program spadne.
    // std::cout << "Hodnota na teto adrese (nedefinovane chovani): " << *pSpatny << std::endl;
    // *pSpatny = 100; // Ještě horší - zápis do neplatné paměti!

    return 0;
}
