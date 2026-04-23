#include <iostream>

/**
 * @struct Vektor2D
 * @brief Reprezentuje 2D vektor (nebo bod).
 *
 * Používáme 'struct', aby byly atributy 'x' a 'y' ve výchozím stavu
 * veřejné (public) a abychom demonstrovali, že přetěžování
 * operátorů funguje pro 'struct' stejně jako pro 'class'.
 */
struct Vektor2D
{
public: // (pro 'struct' je toto výchozí, píšeme pro srozumitelnost)
    double x;
    double y;

    // Konstruktor
    Vektor2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    /**
     * @brief Přetížení operátoru sčítání (+).
     * Implementováno jako členská funkce.
     * 'this' je levý operand, 'other' je pravý operand.
     * @return Nový Vektor2D, který je součtem obou.
     */
    Vektor2D operator+(const Vektor2D& other) const
    {
        // 'const' na konci znamená, že tato metoda nemění stav objektu 'this'
        return Vektor2D(this->x + other.x, this->y + other.y);
    }

    /**
     * @brief Přetížení operátoru porovnání (==).
     * Implementováno jako členská funkce.
     * @return true, pokud jsou oba vektory shodné.
     */
    bool operator==(const Vektor2D& other) const
    {
        return (this->x == other.x) && (this->y == other.y);
    }
};

/**
 * @brief Přetížení operátoru výpisu do streamu (<<).
 * Musí být implementováno jako volná (nečlenská) funkce,
 * protože levý operand je 'std::ostream&' (např. 'std::cout').
 *
 * Je deklarována jako 'friend' v 'README.md', ale protože
 * 'Vektor2D' je 'struct' a její členy 'x' a 'y' jsou public,
 * technicky 'friend' ani nepotřebuje.
 *
 * @param os Reference na výstupní stream (např. std::cout).
 * @param v Vektor, který chceme vypsat.
 * @return Reference na stejný stream 'os' (pro řetězení).
 */
std::ostream& operator<<(std::ostream& os, const Vektor2D& v)
{
    // Definujeme formát výpisu
    os << "Vektor(" << v.x << ", " << v.y << ")";
    return os;
}


/**
 * @brief Hlavní funkce programu
 *
 * Demonstruje použití přetížených operátorů.
 */
int main()
{
    // Vytvoření instancí pomocí konstruktoru
    Vektor2D v1(10, 5);
    Vektor2D v2(2, 4);
    Vektor2D v3(10, 5);

    std::cout << "--- Demonstrace operatoru << ---" << std::endl;
    std::cout << "Vektor v1: " << v1 << std::endl;
    std::cout << "Vektor v2: " << v2 << std::endl;

    std::cout << "\n--- Demonstrace operatoru + ---" << std::endl;
    // Zde se volá v1.operator+(v2)
    Vektor2D soucet = v1 + v2;
    std::cout << "v1 + v2 = " << soucet << std::endl;

    std::cout << "\n--- Demonstrace operatoru == ---" << std::endl;
    
    // Zde se volá v1.operator==(v2)
    if (v1 == v2) {
        std::cout << "v1 a v2 jsou shodne." << std::endl;
    } else {
        std::cout << "v1 a v2 nejsou shodne." << std::endl;
    }

    // Zde se volá v1.operator==(v3)
    if (v1 == v3) {
        std::cout << "v1 a v3 jsou shodne." << std::endl;
    } else {
        std::cout << "v1 a v3 nejsou shodne." << std::endl;
    }

    std::cout << "\n--- Demonstrace retezoveho volani ---" << std::endl;
    std::cout << v1 << " + " << v2 << " = " << (v1 + v2) << std::endl;


    return 0;
}