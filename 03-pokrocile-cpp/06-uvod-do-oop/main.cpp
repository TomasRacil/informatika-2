#include <iostream>

/**
 * @class Obdelnik
 * @brief Reprezentuje geometrický tvar obdélníku.
 *
 * Tato třída demonstruje základní principy OOP:
 * - Zapouzdření: Atributy 'delka' a 'sirka' jsou privátní.
 * - Metody: Veřejné metody pro nastavení a získání hodnot (getters/setters).
 * - Konstruktor: Speciální metoda pro inicializaci objektu.
 */
class Obdelnik
{
private:
    // Atributy jsou privátní - zapouzdření
    int delka;
    int sirka;

public:
    /**
     * @brief Konstruktor třídy Obdelnik.
     * * Volá se při vytváření nového objektu.
     * Inicializuje obdélník s danou délkou a šířkou.
     * Používá 'this->' k rozlišení mezi atributem třídy a parametrem.
     */
    Obdelnik(int delka, int sirka)
    {
        // Kontrola platnosti vstupů
        if (delka > 0) {
            this->delka = delka;
        } else {
            this->delka = 1; // Výchozí hodnota
        }

        if (sirka > 0) {
            this->sirka = sirka;
        } else {
            this->sirka = 1; // Výchozí hodnota
        }
    }

    // --- Gettery (Metody pro získání hodnot) ---

    /**
     * @brief Vrací délku obdélníku.
     */
    int getDelka()
    {
        return delka;
    }

    /**
     * @brief Vrací šířku obdélníku.
     */
    int getSirka()
    {
        return sirka;
    }

    // --- Settery (Metody pro nastavení hodnot) ---

    /**
     * @brief Nastavuje délku obdélníku s validací.
     */
    void setDelka(int delka)
    {
        if (delka > 0)
        {
            this->delka = delka;
        }
        else
        {
            std::cout << "Chyba: Delka nemuze byt zaporna nebo nulova!" << std::endl;
        }
    }

    /**
     * @brief Nastavuje šířku obdélníku s validací.
     */
    void setSirka(int sirka)
    {
        if (sirka > 0)
        {
            this->sirka = sirka;
        }
        else
        {
            std::cout << "Chyba: Sirka nemuze byt zaporna nebo nulova!" << std::endl;
        }
    }

    // --- Další metody ---

    /**
     * @brief Vypočítá a vrací obsah obdélníku.
     */
    int obsah()
    {
        return delka * sirka;
    }

    /**
     * @brief Vypočítá a vrací obvod obdélníku.
     */
    int obvod()
    {
        return 2 * (delka + sirka);
    }

    /**
     * @brief Kontroluje, zda je obdélník čtvercem.
     * @return true pokud je čtverec, jinak false.
     */
    bool jeCtverec()
    {
        return delka == sirka;
    }
};

/**
 * @brief Hlavní funkce programu
 *
 * Demonstruje vytvoření objektů (instancí) třídy Obdelnik
 * a volání jejich metod.
 */
int main()
{
    // Vytvoření instance 'obdelnik1' s délkou 5 a šířkou 10
    Obdelnik obdelnik1(5, 10);

    // Vypis informaci o obdelniku pomoci getteru
    std::cout << "--- Obdelnik 1 ---" << std::endl;
    std::cout << "Delka: " << obdelnik1.getDelka() << std::endl;
    std::cout << "Sirka: " << obdelnik1.getSirka() << std::endl;
    std::cout << "Obsah: " << obdelnik1.obsah() << std::endl;
    std::cout << "Obvod: " << obdelnik1.obvod() << std::endl;
    std::cout << "Je ctverec: " << (obdelnik1.jeCtverec() ? "ano" : "ne") << std::endl;

    // Vytvoření instance 'ctverec'
    Obdelnik ctverec(7, 7);
    std::cout << "\n--- Ctverec ---" << std::endl;
    std::cout << "Delka: " << ctverec.getDelka() << std::endl;
    std::cout << "Sirka: " << ctverec.getSirka() << std::endl;
    std::cout << "Obsah: " << ctverec.obsah() << std::endl;
    std::cout << "Je ctverec: " << (ctverec.jeCtverec() ? "ano" : "ne") << std::endl;


    // Změna délky a šířky 'obdelnik1' pomocí setterů
    std::cout << "\n--- Zmena obdelniku 1 ---" << std::endl;
    obdelnik1.setDelka(20);
    obdelnik1.setSirka(-3); // Test zadání záporné hodnoty

    // Vypis informaci o obdelniku po zmene
    std::cout << "Nova delka: " << obdelnik1.getDelka() << std::endl;
    std::cout << "Nova sirka: " << obdelnik1.getSirka() << std::endl;
    std::cout << "Novy obsah: " << obdelnik1.obsah() << std::endl;


    // Přímý přístup k atributům není možný, protože jsou 'private'
    // Následující řádek by způsobil chybu při kompilaci:
    // obdelnik1.delka = 15; // CHYBA!

    return 0;
}