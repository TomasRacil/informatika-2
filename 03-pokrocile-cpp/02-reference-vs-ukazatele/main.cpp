#include <iostream>

// Předávání hodnotou - vytváří se kopie
void hodnotaZmen(int hodnota) {
    hodnota = 10;
}

// Předávání ukazatelem - předáváme adresu a přes ní měníme originál
void ukazatelZmen(int* ukazatel) {
    // U ukazatelů je vždy dobré kontrolovat nullptr!
    if (ukazatel != nullptr) {
        *ukazatel = 20;
    }
}

// Předávání referencí - funkce pracuje přímo s originálem přes alias
void referenceZmen(int& ref) {
    ref = 30; // Není potřeba žádná dereference
}

int main() {
    int cislo = 5;

    std::cout << "Puvodni hodnota: " << cislo << std::endl;

    // 1. Pokus o změnu hodnotou
    hodnotaZmen(cislo);
    std::cout << "Po volani hodnotaZmen: " << cislo << std::endl;

    // 2. Úspěšná změna přes ukazatel
    ukazatelZmen(&cislo);
    std::cout << "Po volani ukazatelZmen: " << cislo << std::endl;

    // 3. Úspěšná změna přes referenci
    referenceZmen(cislo);
    std::cout << "Po volani referenceZmen: " << cislo << std::endl;


    // --- DALŠÍ ROZDÍLY ---
    
    int a = 100;
    int b = 200;

    // Ukazatel můžeme přesměrovat z 'a' na 'b'
    int* ptr = &a;
    std::cout << "\nUkazatel ukazuje na: " << *ptr << std::endl;
    ptr = &b;
    std::cout << "Ukazatel presmerovan na: " << *ptr << std::endl;

    // Referenci nelze přesměrovat. 
    int& ref = a;
    std::cout << "Reference ukazuje na: " << ref << std::endl;
    
    // Následující řádek NEPŘESMĚRUJE referenci, 
    // ale přiřadí hodnotu z 'b' do 'a' (protože ref je teď jen jiné jméno pro 'a'!)
    ref = b; 
    std::cout << "Po (ref = b) je hodnota ref: " << ref << " a hodnota 'a': " << a << std::endl;

    return 0;
}
