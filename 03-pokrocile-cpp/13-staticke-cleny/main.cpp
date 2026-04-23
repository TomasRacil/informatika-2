#include <iostream>
#include <string>

/**
 * @class Hrac
 * @brief Demonstruje použití statických členů.
 *
 * Třída Hrac počítá, kolik jejích instancí (hráčů)
 * je aktuálně ve hře (kolik jich bylo vytvořeno a kolik smazáno).
 */
class Hrac
{
private:
    // Statický atribut (členská proměnná)
    // Je sdílený všemi instancemi třídy Hrac.
    // Musí být inicializován mimo třídu.
    static int pocetHracuOnline;

    // Běžný atribut (členská proměnná)
    // Každá instance má svůj vlastní.
    std::string jmeno;

public:
    /**
     * @brief Konstruktor
     * Zvýší statické počítadlo při vytvoření nového hráče.
     */
    Hrac(std::string jmeno) : jmeno(jmeno)
    {
        pocetHracuOnline++;
        std::cout << "  KONSTRUKTOR: Hrac '" << this->jmeno << "' se pripojil. ";
        std::cout << "(Celkem hracu: " << pocetHracuOnline << ")" << std::endl;
    }

    /**
     * @brief Destruktor
     * Sníží statické počítadlo při zániku hráče.
     */
    ~Hrac()
    {
        pocetHracuOnline--;
        std::cout << "  DESTRUKTOR: Hrac '" << this->jmeno << "' se odpojil. ";
        std::cout << "(Zbyva hracu: " << pocetHracuOnline << ")" << std::endl;
    }

    /**
     * @brief Běžná (nestatická) metoda.
     * Má přístup k 'this' (a tedy k atributu 'jmeno') 
     * i ke statickým atributům.
     */
    void predstavSe()
    {
        std::cout << "  Jsem " << this->jmeno << ". Aktualne je nas tu " << pocetHracuOnline << "." << std::endl;
    }

    /**
     * @brief Statická metoda.
     * Lze ji volat i bez existence jakéhokoliv objektu (Hrac::getHracuOnline()).
     * Nemá přístup k 'this' ani k nestatickým atributům (jako 'jmeno').
     */
    static int getHracuOnline()
    {
        // Nelze použít 'this->jmeno' nebo jen 'jmeno'.
        // return this->jmeno; // CHYBA KOMPILACE
        return pocetHracuOnline;
    }
};

// Inicializace statického atributu.
// Musí být provedena v globálním rozsahu (mimo třídu i mimo main).
// Obvykle se dává do .cpp souboru.
int Hrac::pocetHracuOnline = 0;


int main()
{
    // Statickou metodu můžeme zavolat, i když ještě neexistuje žádný objekt Hrac.
    std::cout << "--- Zacatek programu ---" << std::endl;
    std::cout << "Aktualni pocet hracu: " << Hrac::getHracuOnline() << std::endl;

    std::cout << "\n--- Vytvarim hrace na stacku ---" << std::endl;
    Hrac hrac1("Alice");
    hrac1.predstavSe();
    std::cout << "Aktualni pocet hracu: " << Hrac::getHracuOnline() << std::endl;

    std::cout << "\n--- Vytvarim hrace na halde ---" << std::endl;
    Hrac* hrac2_ptr = new Hrac("Bob");
    hrac2_ptr->predstavSe();
    std::cout << "Aktualni pocet hracu: " << hrac1.getHracuOnline() << std::endl; // Lze volat i přes instanci

    std::cout << "\n--- Vstupuji do noveho bloku ---" << std::endl;
    {
        Hrac hrac3("Charlie");
        hrac3.predstavSe();
        std::cout << "Aktualni pocet hracu: " << Hrac::getHracuOnline() << std::endl;
    } // 'hrac3' (Charlie) zde zaniká -> volá se destruktor
    std::cout << "--- Opustil jsem novy blok ---" << std::endl;

    std::cout << "Aktualni pocet hracu: " << Hrac::getHracuOnline() << std::endl;

    std::cout << "\n--- Mazani hrace z haldy ---" << std::endl;
    delete hrac2_ptr; // 'hrac2_ptr' (Bob) zaniká -> volá se destruktor
    hrac2_ptr = nullptr;
    std::cout << "Aktualni pocet hracu: " << Hrac::getHracuOnline() << std::endl;

    std::cout << "\n--- Konec main() ---" << std::endl;
    // 'hrac1' (Alice) zaniká -> volá se destruktor
    return 0;
}