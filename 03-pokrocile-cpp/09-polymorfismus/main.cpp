#include <iostream>
#include <string>
#include <vector>

/**
 * @class Zvire
 * @brief Abstraktní základní třída.
 *
 * Slouží jako "kontrakt" (rozhraní) pro všechny dceřiné třídy.
 * Nelze z ní vytvořit instanci, protože má čistě virtuální metodu.
 */
class Zvire
{
protected:
    std::string jmeno;

public:
    // Konstruktor
    Zvire(std::string jmeno) : jmeno(jmeno) {}

    /**
     * @brief Virtuální destruktor.
     * Zajišťuje, že se při mazání objektu přes ukazatel na Zvire
     * zavolá správný destruktor dceřiné třídy.
     */
    virtual ~Zvire()
    {
        std::cout << "  ~Zvire destruktor pro: " << this->jmeno << std::endl;
    }

    /**
     * @brief Čistě virtuální metoda (pure virtual function).
     * Dceřiné třídy MUSÍ tuto metodu implementovat.
     * Definuje "co" má objekt umět, ale ne "jak".
     */
    virtual void udelejZvuk() = 0;

    /**
     * @brief Běžná, ne-virtuální metoda.
     * Tato metoda se NEBUDE chovat polymorfně.
     * Vždy se zavolá implementace ze Zvire.
     */
    void spi()
    {
        std::cout << this->jmeno << " spí (metoda Zvire::spi)" << std::endl;
    }
};

/**
 * @class Pes
 * @brief Dceřiná třída, která implementuje rozhraní Zvire.
 */
class Pes : public Zvire
{
public:
    Pes(std::string jmeno) : Zvire(jmeno) {}

    ~Pes()
    {
        std::cout << "  ~Pes destruktor pro: " << this->jmeno << std::endl;
    }

    /**
     * @brief Implementace (přepsání) čistě virtuální metody.
     * Klíčové slovo 'override' je dobrá praxe, kontroluje,
     * zda v rodiči skutečně existuje metoda ke přepsání.
     */
    void udelejZvuk() override
    {
        std::cout << this->jmeno << " rika: Haf! Haf!" << std::endl;
    }
};

/**
 * @class Kocka
 * @brief Další dceřiná třída, implementující Zvire.
 */
class Kocka : public Zvire
{
public:
    Kocka(std::string jmeno) : Zvire(jmeno) {}

    ~Kocka()
    {
        std::cout << "  ~Kocka destruktor pro: " << this->jmeno << std::endl;
    }

    void udelejZvuk() override
    {
        std::cout << this->jmeno << " rika: Mnau." << std::endl;
    }
};

/**
 * @brief Hlavní funkce programu
 *
 * Demonstruje polymorfismus v praxi.
 */
int main()
{
    // Nelze vytvořit instanci abstraktní třídy:
    // Zvire z("Nejake zvire"); // CHYBA!

    // Můžeme ale vytvořit instance dceřiných tříd
    Pes p("Alik");
    Kocka k("Micka");
    std::cout << "--- Test jednotlivych objektu ---" << std::endl;
    p.udelejZvuk();
    k.udelejZvuk();

    std::cout << "\n--- Demonstrace polymorfismu ---" << std::endl;

    // Vytvoříme vektor ukazatelů na základní třídu Zvire
    std::vector<Zvire *> zvirata;

    // Do vektoru můžeme přidat jakýkoliv objekt, který DĚDÍ ze Zvire
    zvirata.push_back(new Pes("Baryk"));
    zvirata.push_back(new Kocka("Minda"));
    zvirata.push_back(new Pes("Rex"));

    // Nyní projdeme vektor a se všemi objekty zacházíme stejně
    // (jako s obecným 'Zvire*'), přesto se každý chová jinak.
    std::cout << "\n--- Polymorfni volani metod ---" << std::endl;
    for (Zvire *z : zvirata)
    {
        // Díky 'virtual' se zde zavolá správná verze
        // (Pes::udelejZvuk nebo Kocka::udelejZvuk)
        z->udelejZvuk();

        // Metoda 'spi' není virtuální, zavolá se vždy Zvire::spi
        z->spi();
    }

    std::cout << "\n--- Uklid (mazani objektu) ---" << std::endl;
    // Objekty byly vytvořeny pomocí 'new', musíme je tedy ručně uvolnit pomocí 'delete'.
    // Díky virtuálnímu destruktoru v Zvire se při 'delete'
    // zavolá nejdříve destruktor dceřiné třídy (~Pes nebo ~Kocka) a pak teprve základní (~Zvire).
    // Pokud by destruktor Zvire nebyl virtuální, zavolal by se POUZE ~Zvire(), což by vedlo k úniku zdrojů,
    // pokud by dceřiné třídy alokovaly vlastní zdroje.
    for (Zvire *z : zvirata)
    {
        delete z;
        // z = nullptr; // Po delete je dobré ukazatel nastavit na nullptr, i když zde už ho znovu nepoužijeme.
    }
    zvirata.clear(); // Vyčistí vektor (ukazatele už jsou neplatné).

    std::cout << "\n--- Konec main() ---" << std::endl;
    return 0;
}