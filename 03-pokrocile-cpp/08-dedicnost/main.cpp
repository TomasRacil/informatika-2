#include <iostream>
#include <string>

/**
 * @class Person
 * @brief Základní (rodičovská) třída.
 *
 * Reprezentuje obecnou osobu.
 * Používá 'protected', aby 'jmeno' bylo přístupné pro dceřiné třídy,
 * ale 'private' 'vek' přístupný nebyl.
 */
class Person
{
protected:
    // Protected: Přístupné pro tuto třídu a všechny dceřiné třídy
    std::string jmeno;

private:
    // Private: Přístupné POUZE pro třídu Person
    int vek;

public:
    /**
     * @brief Konstruktor základní třídy
     */
    Person(std::string jmeno, int vek)
    {
        this->jmeno = jmeno;
        this->vek = vek;
        std::cout << "  KONSTRUKTOR: Person '" << this->jmeno << "' byl vytvoren." << std::endl;
    }

    /**
     * @brief Destruktor základní třídy
     */
    ~Person()
    {
        std::cout << "  DESTRUKTOR: Person '" << this->jmeno << "' byl znicen." << std::endl;
    }

    void pozdrav()
    {
        std::cout << "Ahoj, jmenuji se " << this->jmeno << " a je mi " << this->vek << " let.";
    }

    int getVek()
    {
        return this->vek;
    }
};

/**
 * @class Student
 * @brief Odvozená (dceřiná) třída.
 *
 * Dědí z třídy Person pomocí 'public' dědičnosti.
 * Přidává vlastní atributy a metody a rozšiřuje existující.
 */
class Student : public Person
{
private:
    // Atribut specifický pouze pro Studenta
    std::string skola;

public:
    /**
     * @brief Konstruktor odvozené třídy
     *
     * Pomocí inicializačního seznamu ': Person(jmeno, vek)'
     * volá konstruktor rodičovské třídy.
     */
    Student(std::string jmeno, int vek, std::string skola) : Person(jmeno, vek)
    {
        this->skola = skola;
        std::cout << "  KONSTRUKTOR: Student '" << this->jmeno << "' byl vytvoren." << std::endl;
    }

    /**
     * @brief Destruktor odvozené třídy
     */
    ~Student()
    {
        // Destruktor rodiče (~Person) se zavolá automaticky AŽ POTÉTO
        std::cout << "  DESTRUKTOR: Student '" << this->jmeno << "' byl znicen." << std::endl;
    }

    /**
     * @brief Metoda specifická pro Studenta
     */
    void studuj()
    {
        // Máme přístup k 'jmeno', protože je 'protected' v Person
        std::cout << this->jmeno << " se uci na zkousku." << std::endl;

        // K 'vek' přístup nemáme, protože je 'private' v Person
        // Následující řádek by způsobil chybu kompilace:
        // std::cout << "Vek: " << this->vek; // CHYBA!
        
        // Musíme použít veřejnou metodu (getter)
        std::cout << "Vek (pres getter): " << this->getVek() << std::endl;
    }

    /**
     * @brief "Přepsaná" metoda pozdrav
     *
     * Rozšiřuje funkčnost rodičovské metody.
     */
    void pozdrav()
    {
        // 1. Zavoláme původní metodu z rodičovské třídy
        Person::pozdrav();

        // 2. Přidáme vlastní výpis
        std::cout << " A studuji na " << this->skola << "." << std::endl;
    }
};


/**
 * @brief Hlavní funkce programu
 *
 * Demonstruje vytváření objektů, volání metod a pořadí
 * volání konstruktorů a destruktorů.
 */
int main()
{
    std::cout << "--- Vytvarim objekt Person ---" << std::endl;
    Person osoba("Tomas", 30);
    osoba.pozdrav();
    std::cout << std::endl;

    std::cout << "\n--- Vytvarim objekt Student ---" << std::endl;
    Student student("Pavel", 22, "VUT");

    // 'student' má přístup k metodám z 'Person'
    std::cout << "Vek studenta: " << student.getVek() << std::endl;

    // 'student' volá svou vlastní "přepsanou" metodu
    student.pozdrav();

    // 'student' volá svou vlastní unikátní metodu
    student.studuj();
    
    // Přímý přístup k 'protected' nebo 'private' členům zvenku není možný
    // student.jmeno = "David"; // CHYBA! 'jmeno' je protected
    // student.vek = 25;      // CHYBA! 'vek' je private
    // student.skola = "MUNI";  // CHYBA! 'skola' je private

    std::cout << "\n--- Konec main() (objekty zanikaji) ---" << std::endl;
    // Zde zanikne 'student' (volá ~Student a pak ~Person)
    // a poté 'osoba' (volá ~Person)
    
    return 0;
}
