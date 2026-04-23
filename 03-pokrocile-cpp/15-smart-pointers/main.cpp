#include <iostream>
#include <string>
#include <memory> // Potřebná knihovna pro chytré ukazatele
#include <vector>

// Pomocná třída, abychom viděli, kdy se volá konstruktor a destruktor
class MojeTrida {
public:
    std::string jmeno;

    MojeTrida(std::string n) : jmeno(n) {
        std::cout << "  KONSTRUKTOR: Vytvoren objekt '" << jmeno << "'" << std::endl;
    }

    ~MojeTrida() {
        std::cout << "  DESTRUKTOR: Nicen objekt '" << jmeno << "'" << std::endl;
    }

    void Vypis() {
        std::cout << "  Ahoj, jsem '" << jmeno << "'" << std::endl;
    }
};

// --- Příklad s unique_ptr ---
void demoUniquePtr() {
    std::cout << "--- Demo std::unique_ptr ---" << std::endl;

    // Vytvoření unique_ptr pomocí std::make_unique (preferovaný způsob)
    std::unique_ptr<MojeTrida> ptr1 = std::make_unique<MojeTrida>("Objekt 1");
    
    // Použití operátoru -> pro volání metody
    ptr1->Vypis();

    // Vytvoření druhého unique_ptr
    std::unique_ptr<MojeTrida> ptr2;

    // Kopírování NENÍ povoleno:
    // ptr2 = ptr1; // CHYBA KOMPILACE

    // Přesun (transfer vlastnictví) JE povolen:
    std::cout << "  Presouvam vlastnictvi z ptr1 na ptr2..." << std::endl;
    ptr2 = std::move(ptr1);

    // Nyní ptr1 ukazuje na nullptr
    if (!ptr1) {
        std::cout << "  ptr1 je nyni prazdny (nullptr)." << std::endl;
    }

    // A ptr2 vlastní objekt
    ptr2->Vypis();

    std::cout << "  Konec funkce demoUniquePtr()..." << std::endl;
    // 'ptr2' zde opouští scope, jeho destruktor se volá
    // a ten automaticky smaže objekt 'Objekt 1'.
    // 'ptr1' je prázdný, takže nic nedělá.
}


// --- Příklad se shared_ptr ---
void demoSharedPtr() {
    std::cout << "\n--- Demo std::shared_ptr ---" << std::endl;

    std::shared_ptr<MojeTrida> s_ptr1;

    { // Začátek vnitřního bloku
        // Vytvoření shared_ptr pomocí std::make_shared (preferovaný způsob)
        s_ptr1 = std::make_shared<MojeTrida>("Objekt 2");
        std::cout << "  Pocet referenci po vytvoreni: " << s_ptr1.use_count() << std::endl; // Vypíše 1

        // Vytvoření kopie - sdílení vlastnictví
        std::shared_ptr<MojeTrida> s_ptr2 = s_ptr1;
        
        std::cout << "  Pocet referenci po zkopirovani: " << s_ptr1.use_count() << std::endl; // Vypíše 2
        
        s_ptr2->Vypis();

        std::cout << "  Konec vnitrniho bloku..." << std::endl;
        // Zde zaniká 's_ptr2', počítadlo referencí klesne na 1.
    } // Konec vnitřního bloku

    std::cout << "  Za vnitrnim blokem." << std::endl;
    std::cout << "  Pocet referenci: " << s_ptr1.use_count() << std::endl; // Vypíše 1

    std::cout << "  Konec funkce demoSharedPtr()..." << std::endl;
    // Zde zaniká 's_ptr1', počítadlo referencí klesne na 0.
    // Destruktor objektu 'Objekt 2' je automaticky zavolán.
}


// --- Příklad s weak_ptr ---
void demoWeakPtr() {
    std::cout << "\n--- Demo std::weak_ptr (pro reseni cyklu) ---" << std::endl;
    
    std::weak_ptr<MojeTrida> w_ptr; // Slabý ukazatel
    
    { // Blok pro shared_ptr
        std::shared_ptr<MojeTrida> s_ptr = std::make_shared<MojeTrida>("Objekt 3");
        w_ptr = s_ptr; // 'w_ptr' pozoruje 's_ptr', ale nevlastní ho

        std::cout << "  Pocet referenci (shared_ptr): " << s_ptr.use_count() << std::endl; // 1
        std::cout << "  Pocet referenci (weak_ptr): " << w_ptr.use_count() << std::endl;   // 1
        
        // Pro přístup k objektu musíme weak_ptr "zamknout"
        if (auto tmp_s_ptr = w_ptr.lock()) { // Vytvoří dočasný shared_ptr
            std::cout << "  Objekt 'Objekt 3' stale existuje." << std::endl;
            tmp_s_ptr->Vypis();
            std::cout << "  Pocet referenci behem lock(): " << w_ptr.use_count() << std::endl; // 2
        } else {
            std::cout << "  Objekt 'Objekt 3' uz byl smazan." << std::endl;
        }
        
        std::cout << "  Konec bloku pro shared_ptr..." << std::endl;
        // Zde zaniká 's_ptr', počet referencí klesá na 0 a 'Objekt 3' je zničen.
    }

    std::cout << "  Za blokem pro shared_ptr." << std::endl;
    std::cout << "  Pocet referenci (weak_ptr): " << w_ptr.use_count() << std::endl; // 0

    // Pokus o zamknutí nyní selže
    if (auto tmp_s_ptr = w_ptr.lock()) {
        std::cout << "  Objekt stale existuje." << std::endl;
    } else {
        std::cout << "  Objekt uz byl smazan (w_ptr.lock() selhal)." << std::endl;
    }
}


int main() {
    
    demoUniquePtr();
    
    demoSharedPtr();

    demoWeakPtr();

    // --- Chytré ukazatele v kontejnerech ---
    std::cout << "\n--- Demo unique_ptr v kontejneru std::vector ---" << std::endl;
    {
        std::vector<std::unique_ptr<MojeTrida>> vektorUkazatelu;

        // Nemůžeme použít push_back(new MojeTrida(...)) - to by vyžadovalo kopírování
        // Musíme explicitně vytvořit unique_ptr a pak ho PŘESUNOUT (std::move)
        vektorUkazatelu.push_back(std::make_unique<MojeTrida>("VecAuto"));
        vektorUkazatelu.push_back(std::make_unique<MojeTrida>("VecKolo"));

        // Od C++14 můžeme použít 'emplace_back', který je efektivnější
        vektorUkazatelu.emplace_back(new MojeTrida("VecLetadlo"));

        std::cout << "  Prochazeni vektoru:" << std::endl;
        for (const auto& ptr : vektorUkazatelu) {
            ptr->Vypis();
        }

        std::cout << "  Konec bloku s vektorem..." << std::endl;
        // Zde zaniká 'vektorUkazatelu'.
        // Destruktor vektoru automaticky zavolá destruktor pro každý 'unique_ptr' v něm.
        // Každý 'unique_ptr' pak smaže objekt, který vlastnil.
    }
    std::cout << "--- Konec programu ---" << std::endl;

    return 0;
}