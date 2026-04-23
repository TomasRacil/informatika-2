#include <iostream>

// ÚKOL 1: Doplňte prohození hodnot pomocí pointrů
void swapPointer(int* a, int* b) {
    // Váš kód zde
    
}

// ÚKOL 2: Doplňte prohození hodnot pomocí referencí
void swapReference(int& a, int& b) {
    // Váš kód zde
    
}

int main() {
    int x = 10, y = 20;
    std::cout << "Puvodni: x=" << x << ", y=" << y << "\n";

    // Volání pointer verze (nezapomeňte poslat adresy!)
    swapPointer(&x, &y);
    std::cout << "Po swapPointer: x=" << x << ", y=" << y << "\n";

    // Volání referenční verze
    swapReference(x, y);
    std::cout << "Po swapReference: x=" << x << ", y=" << y << "\n";

    return 0;
}