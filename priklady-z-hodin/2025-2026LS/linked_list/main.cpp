#include <iostream>

// Struktura jednoho uzlu seznamu
struct Node {
    int data;
    Node* next;
};

// ÚKOL 1: Přidání prvku na ZAČÁTEK seznamu
// Všimněte si 'Node*& head' - je to reference na pointer! Můžeme tak změnit samotný head.
void insertFront(Node*& head, int value) {
    // 1. Vytvořte nový uzel pomocí operátoru 'new'
    // 2. Naplňte ho daty
    // 3. Jeho 'next' musí ukazovat na současný první prvek (head)
    // 4. Přesuňte 'head', aby ukazoval na tento nový uzel
    
    // Váš kód zde:
    
}

// ÚKOL 2: Výpis celého seznamu
void printList(Node* head) {
    // Projděte seznam od 'head' až do konce (dokud nenarazíte na nullptr)
    // a vypisujte hodnoty.
    
    // Váš kód zde:
    
    std::cout << "nullptr\n";
}

// ÚKOL 3: Uvolnění paměti (prevence memory leaku)
void deleteList(Node*& head) {
    // Záludnost: Nemůžete smazat uzel a PAK se ptát na jeho 'next'.
    // Musíte si 'next' nejdříve uložit bokem!
    // K mazání použijte operátor 'delete'.
    
    // Váš kód zde:
    
    head = nullptr; // Nakonec nastavíme head bezpečně na nic
}

int main() {
    Node* head = nullptr; // Na začátku je seznam prázdný

    insertFront(head, 10);
    insertFront(head, 20);
    insertFront(head, 30);

    std::cout << "Vypis seznamu: ";
    printList(head); // Očekávaný výstup: 30 -> 20 -> 10 -> nullptr

    deleteList(head);
    
    std::cout << "Po smazani: ";
    printList(head); // Očekávaný výstup: nullptr

    return 0;
}