#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>

void vyresHanoi(int n, 
                std::stack<int>& zdrojova_vez, 
                std::stack<int>& cilova_vez, 
                std::stack<int>& pomocna_vez,
                const std::string& zdrojova_vez_nazev, 
                const std::string& cilova_vez_nazev, 
                const std::string& pomocna_vez_nazev) 
{
    if (n == 0) {
        return;
    }

    vyresHanoi(n - 1, zdrojova_vez, pomocna_vez, cilova_vez, zdrojova_vez_nazev, pomocna_vez_nazev, cilova_vez_nazev);
    
    int disk = zdrojova_vez.top();
    zdrojova_vez.pop();
    cilova_vez.push(disk);

    std::cout << "Přesun disku " << disk << " z věže " << zdrojova_vez_nazev << " na věž " << cilova_vez_nazev << "\n";

    vyresHanoi(n - 1, pomocna_vez, cilova_vez, zdrojova_vez, pomocna_vez_nazev, cilova_vez_nazev, zdrojova_vez_nazev);
}


int main() {
    int pocet_disku = 3;

    std::stack<int> vezA;
    std::stack<int> vezB;
    std::stack<int> vezC;

    for (int i = pocet_disku; i > 0; --i) {
        vezA.push(i);
    }

    std::cout << "Řešení Hanojských věží pro " << pocet_disku << " disků:\n\n";

    vyresHanoi(pocet_disku, vezA, vezC, vezB, "A", "C", "B");

    std::cout << "Přesun dokončen.\n";

    std::cout << "Obsah cílové věže C (odshora dolů): ";
    while (!vezC.empty()) {
        std::cout << vezC.top() << " ";
        vezC.pop();
    }
    std::cout << "\n";

    std::cout << "Obsah věže A (očekáváno 0): " << vezA.size() << "\n";
    std::cout << "Obsah věže B (očekáváno 0): " << vezB.size() << "\n";

    return 0;
}