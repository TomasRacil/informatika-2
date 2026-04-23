#include <iostream>
#include <string>

/**
 * @class Resource
 * @brief Demonstruje použití konstruktoru a destruktoru.
 *
 * Třída alokuje v konstruktoru dynamickou paměť (int*)
 * a uvolňuje ji v destruktoru. Tím se zabrání úniku paměti (memory leak).
 */
class Resource
{
private:
    int* data;
    std::string name;

public:
    /**
     * @brief Konstruktor
     * Volá se automaticky při vytvoření objektu.
     * Alokuje paměť a inicializuje atributy.
     */
    Resource(std::string n, int val)
    {
        this->name = n;
        this->data = new int; // Alokace paměti na haldě (heap)
        *(this->data) = val;

        std::cout << "  KONSTRUKTOR: Vytvoren Resource '" << this->name
                  << "' s hodnotou " << *(this->data) << std::endl;
    }

    /**
     * @brief Destruktor
     * Volá se automaticky při zániku objektu.
     * Uvolňuje dynamicky alokovanou paměť.
     */
    ~Resource()
    {
        std::cout << "  DESTRUKTOR: Uvolnuji Resource '" << this->name
                  << "' s hodnotou " << *(this->data) << std::endl;
        
        delete this->data; // Uvolnění paměti
        this->data = nullptr; // Dobrá praxe - nastavit ukazatel na null
    }

    void print()
    {
        std::cout << "  Resource '" << this->name << "' ma hodnotu " 
                  << *(this->data) << std::endl;
    }
};

/**
 * @brief Hlavní funkce programu
 *
 * Demonstruje životní cyklus objektů:
 * 1. Objekty na zásobníku (stack) - destruktor volán automaticky na konci 'scope'.
 * 2. Objekty na haldě (heap) - destruktor volán manuálně pomocí 'delete'.
 */
int main()
{
    // --- Demonstrace 1: Objekt na zásobniku (stack) ---
    std::cout << "--- Vstupuji do bloku (stack) ---" << std::endl;
    {
        // Konstruktor se volá při definici proměnné
        Resource r1("r1_stack", 100);
        r1.print();

    } // 'r1' opouští scope, automaticky se volá destruktor ~Resource()
    std::cout << "--- Opustil jsem blok (stack) ---" << std::endl;


    std::cout << "\n--- Vytvarim druhy objekt na stacku ---" << std::endl;
    Resource r_global("r_global_stack", 50);
    r_global.print();


    // --- Demonstrace 2: Objekt na haldě (heap) ---
    std::cout << "\n--- Vytvarim na halde (heap) ---" << std::endl;
    
    // Konstruktor se volá při použití 'new'
    Resource* r2_ptr = new Resource("r2_heap", 200);
    r2_ptr->print();

    // Objekt na haldě nezaniká automaticky!
    std::cout << "--- Manualne mazu objekt z haldy ---" << std::endl;
    
    // Zde musíme explicitně zavolat 'delete', 
    // což následně spustí destruktor ~Resource()
    delete r2_ptr;
    r2_ptr = nullptr;

    std::cout << "\n--- Konec main() ---" << std::endl;
    
    // Nyní zaniká 'r_global', volá se její destruktor
    return 0;
}
