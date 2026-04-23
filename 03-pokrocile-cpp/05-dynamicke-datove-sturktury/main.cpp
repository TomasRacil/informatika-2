#include <iostream>

// --- Definice struktury Uzlu ---
struct Uzel {
    int data;       // Data uložená v uzlu
    Uzel* dalsi;    // Ukazatel na následující uzel

    // Konstruktor pro snadné vytváření uzlů
    Uzel(int hodnota) {
        data = hodnota;
        dalsi = nullptr; // Nový uzel na začátku neukazuje nikam
        std::cout << "   (Vytvoren uzel s hodnotou " << data << ")" << std::endl;
    }
    
    // Destruktor pro kontrolu uvolnění paměti
    ~Uzel() {
        std::cout << "   (Destruktor: Uvolnen uzel s hodnotou " << data << ")" << std::endl;
    }
};

// --- Funkce pro práci se seznamem ---

/**
 * @brief Vypíše obsah spojového seznamu.
 * @param head Ukazatel na první uzel seznamu.
 */
void vypisSeznam(Uzel* head) {
    Uzel* aktualni = head; // Dočasný ukazatel pro procházení
    std::cout << "Seznam: [ ";
    while (aktualni != nullptr) {
        std::cout << aktualni->data << " ";
        aktualni = aktualni->dalsi; // Posun na další uzel
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Vloží nový uzel s danou hodnotou na ZAČÁTEK seznamu.
 * @param pHead Ukazatel NA UKAZATEL na první uzel (abychom mohli změnit samotný head).
 * @param hodnota Hodnota pro nový uzel.
 */
void vlozNaZacatek(Uzel** pHead, int hodnota) {
    std::cout << "Vkladam " << hodnota << " na zacatek..." << std::endl;
    // 1. Vytvoř nový uzel
    Uzel* novyUzel = new Uzel(hodnota);
    // 2. Nastav jeho 'dalsi' na aktuální první uzel
    novyUzel->dalsi = *pHead;
    // 3. Přesuň 'head', aby ukazoval na nový uzel
    *pHead = novyUzel;
}

/**
 * @brief Vloží nový uzel s danou hodnotou na KONEC seznamu.
 * @param pHead Ukazatel NA UKAZATEL na první uzel.
 * @param hodnota Hodnota pro nový uzel.
 */
void vlozNaKonec(Uzel** pHead, int hodnota) {
     std::cout << "Vkladam " << hodnota << " na konec..." << std::endl;
    // 1. Vytvoř nový uzel
    Uzel* novyUzel = new Uzel(hodnota);

    // 2. Pokud je seznam prázdný, nový uzel se stane prvním
    if (*pHead == nullptr) {
        *pHead = novyUzel;
        return;
    }

    // 3. Najdi poslední uzel
    Uzel* posledni = *pHead;
    while (posledni->dalsi != nullptr) {
        posledni = posledni->dalsi;
    }

    // 4. Připoj nový uzel za poslední
    posledni->dalsi = novyUzel;
}

/**
 * @brief Uvolní paměť všech uzlů ve spojovém seznamu.
 * @param pHead Ukazatel NA UKAZATEL na první uzel.
 */
void zrusSeznam(Uzel** pHead) {
    std::cout << "\n--- Ruseni seznamu ---" << std::endl;
    Uzel* aktualni = *pHead;
    Uzel* dalsi = nullptr;

    while (aktualni != nullptr) {
        dalsi = aktualni->dalsi; // Zapamatujeme si adresu dalšího
        delete aktualni;        // Smažeme aktuální
        aktualni = dalsi;       // Posuneme se na další
    }

    *pHead = nullptr; // Seznam je nyní prázdný
     std::cout << "--- Seznam zrusen ---" << std::endl;
}


int main() {
    Uzel* mujSeznam = nullptr; // Ukazatel na první prvek (hlavu) seznamu

    vypisSeznam(mujSeznam); // []

    // Vkládáme prvky
    vlozNaZacatek(&mujSeznam, 10);
    vypisSeznam(mujSeznam); // [ 10 ]

    vlozNaZacatek(&mujSeznam, 5);
    vypisSeznam(mujSeznam); // [ 5 10 ]

    vlozNaKonec(&mujSeznam, 20);
    vypisSeznam(mujSeznam); // [ 5 10 20 ]
    
    vlozNaKonec(&mujSeznam, 30);
    vypisSeznam(mujSeznam); // [ 5 10 20 30 ]

    // Důležité: Uvolnění paměti!
    zrusSeznam(&mujSeznam);
    vypisSeznam(mujSeznam); // []

    return 0; // Destruktory zbývajících lokálních proměnných se zavolají zde
}
