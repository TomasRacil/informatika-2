#include <iostream>
#include <string>
#include <cstring>

// --- 1. Šablona funkce (Function Template) ---

/**
 * @brief Šablona funkce pro nalezení větší ze dvou hodnot.
 * * Kompilátor automaticky vygeneruje verzi této funkce
 * pro jakýkoliv typ T, který podporuje operátor >.
 * @tparam T Datový typ, který se má porovnávat.
 * @param a První hodnota.
 * @param b Druhá hodnota.
 * @return Větší z hodnot a nebo b.
 */
template <typename T>
T getMax(T a, T b) {
    std::cout << "   (Volana sablonova funkce getMax pro typ " << typeid(T).name() << ")" << std::endl;
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// --- 2. Šablona třídy (Class Template) ---

/**
 * @class Box
 * @brief Šablona třídy, která může uchovávat jeden prvek libovolného typu.
 * @tparam T Datový typ uloženého prvku.
 */
template <typename T>
class Box {
private:
    T item; // Atribut 'item' má generický typ T

public:
    // Konstruktor
    Box(T newItem) {
        this->item = newItem;
        std::cout << "   (Vytvoren Box pro typ " << typeid(T).name() << ")" << std::endl;
    }

    // Metoda pro získání hodnoty
    T getItem() {
        return this->item;
    }

    void setItem(T newItem) {
        this->item = newItem;
    }
};

// --- 3. Explicitní specializace šablony (nepovinné, pro ukázku) ---
// Můžeme vytvořit speciální verzi šablony pro konkrétní typ.
// Např. pro char* chceme porovnávat řetězce, ne adresy.
template <>
const char* getMax<const char*>(const char* a, const char* b) {
    std::cout << "   (Volana SPECIALIZOVANA funkce getMax pro const char*)" << std::endl;
    // Použijeme strcmp pro porovnání C-style řetězců
    return (std::strcmp(a, b) > 0) ? a : b;
}


int main() {
    std::cout << "--- 1. Testovani sablony funkce ---" << std::endl;
    
    // Volání pro int
    std::cout << "Vetsi z (5, 10) je: " << getMax(5, 10) << std::endl;
    
    // Volání pro double
    std::cout << "Vetsi z (3.14, 2.71) je: " << getMax(3.14, 2.71) << std::endl;

    // Volání pro std::string (použije se obecná šablona T)
    std::string s1 = "Jablko";
    std::string s2 = "Hruska";
    std::cout << "Vetsi z ('" << s1 << "', '" << s2 << "') je: " << getMax(s1, s2) << std::endl;

    // Volání pro const char* (použije se specializovaná verze)
    std::cout << "Vetsi z ('Ahoj', 'Sbohem') je: " << getMax("Ahoj", "Sbohem") << std::endl;


    std::cout << "\n--- 2. Testovani sablony tridy ---" << std::endl;

    // Instance pro int
    Box<int> intBox(123);
    std::cout << "V krabici na cisla je: " << intBox.getItem() << std::endl;
    intBox.setItem(456);
    std::cout << "Po zmene je v krabici: " << intBox.getItem() << std::endl;

    // Instance pro std::string
    Box<std::string> stringBox("Puvodni text");
    std::cout << "V krabici na text je: '" << stringBox.getItem() << "'" << std::endl;
    stringBox.setItem("Novy text");
    std::cout << "Po zmene je v krabici: '" << stringBox.getItem() << "'" << std::endl;

    return 0;
}