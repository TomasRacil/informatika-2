#include <iostream>
#include <string>
#include <regex>    // Knihovna pro regulární výrazy
#include <vector>

/**
 * @brief Funkce pro demonstraci std::regex_match
 * Kontroluje, zda *celý* řetězec odpovídá vzoru.
 */
void demo_regex_match() {
    std::cout << "--- 1. Demo regex_match (Validace) ---" << std::endl;
    
    // Vytvoříme regex pro jednoduché datum ve formátu RRRR-MM-DD
    // Používáme raw string R"(...)", abychom nemuseli zdvojovat lomítka.
    // ^ - začátek řetězce
    // \d{4} - přesně 4 číslice (rok)
    // -     - pomlčka
    // (0[1-9]|1[0-2]) - měsíc (01-09 nebo 10-12)
    // -     - pomlčka
    // (0[1-9]|[12]\d|3[01]) - den (01-09 nebo 10-29 nebo 30-31)
    // $ - konec řetězce
    std::regex date_regex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");

    std::vector<std::string> testovaci_data = {
        "2024-10-28",
        "1999-12-31",
        "2024-13-01",  // Neplatný měsíc
        "2024-02-32",  // Neplatný den
        "Text 2024-10-28 text" // Obsahuje platné datum, ale není to *celý* řetězec
    };

    for (const std::string& text : testovaci_data) {
        if (std::regex_match(text, date_regex)) {
            std::cout << "'" << text << "' -> ODPOVIDA VZORU" << std::endl;
        } else {
            std::cout << "'" << text << "' -> NEODPOVIDA VZORU" << std::endl;
        }
    }
}

/**
 * @brief Funkce pro demonstraci std::regex_search a std::smatch
 * Hledá *výskyt* vzoru kdekoli v řetězci a extrahuje data.
 */
void demo_regex_search() {
    std::cout << "\n--- 2. Demo regex_search (Extrakce dat) ---" << std::endl;
    
    std::string text = "Kontaktujte nás na info@example.com nebo na podpora@test.cz.";

    // Vzor pro nalezení emailů. Závorky () vytvářejí "zachytávací skupiny".
    // Skupina 1: ([\w.-]+) - uživatelské jméno
    // Skupina 2: ([\w.-]+) - doména
    // Skupina 3: ([a-zA-Z]{2,}) - TLD (např. com, cz)
    std::regex email_vzor(R"(([\w.-]+)@([\w.-]+)\.([a-zA-Z]{2,}))");

    std::smatch shody; // Objekt, kam se uloží výsledky

    // Prohledáváme řetězec 'text'
    std::string::const_iterator startHledani = text.cbegin();
    
    std::cout << "Hledam emaily v textu: '" << text << "'" << std::endl;

    // Cyklus pro nalezení všech shod
    while (std::regex_search(startHledani, text.cend(), shody, email_vzor)) {
        std::cout << "  Nalezen email: " << shody[0].str() << std::endl; // shody[0] je celá shoda
        std::cout << "    Uzivatel [1]: " << shody[1].str() << std::endl;
        std::cout << "    Domena   [2]: " << shody[2].str() << std::endl;
        std::cout << "    TLD      [3]: " << shody[3].str() << std::endl;
        
        // Posuneme začátek hledání na konec právě nalezené shody
        startHledani = shody[0].second;
    }
}

/**
 * @brief Funkce pro demonstraci std::regex_replace
 * Hledá všechny shody a nahrazuje je.
 */
void demo_regex_replace() {
    std::cout << "\n--- 3. Demo regex_replace (Nahrazovani) ---" << std::endl;
    
    std::string text = "Tajna zprava: Heslo je 'TajneHeslo123' a PIN je '9876'.";

    // Vzor pro cokoliv v uvozovkách
    std::regex tajny_vzor(R"('([^']*)')"); // ([^']*) znamená "zachytit 0 a více jakýchkoli znaků, které NEJSOU uvozovka"

    // Nahradíme všechna nalezená hesla
    std::string cenzurovano = std::regex_replace(text, tajny_vzor, "'[CENZUROVANO]'");
    
    std::cout << "Originalni zprava: " << text << std::endl;
    std::cout << "Cenzurovana zprava: " << cenzurovano << std::endl;

    // Příklad s použitím zachycených skupin při nahrazování
    // Chceme prohodit jméno a příjmení
    std::string jmeno = "Novak, Jan";
    std::regex vzor_jmena(R"((\w+), (\w+))"); // Skupina 1: Prijmeni, Skupina 2: Jmeno
    
    // $2 odkazuje na druhou zachycenou skupinu, $1 na první
    std::string format_vymeny = "$2 $1"; 
    
    std::string vymeneno = std::regex_replace(jmeno, vzor_jmena, format_vymeny);
    std::cout << "Original jmeno: " << jmeno << std::endl;
    std::cout << "Prohozene jmeno: " << vymeneno << std::endl;
}


int main() {
    // 1. Validace - je celý vstup platný?
    demo_regex_match();

    // 2. Hledání a extrakce - najdi data uvnitř textu
    demo_regex_search();
    
    // 3. Nahrazování - najdi a nahraď data
    demo_regex_replace();

    return 0;
}