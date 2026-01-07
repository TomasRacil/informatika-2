# **11 - Šablony (Templates)**

Šablony (Templates) jsou základem **generického programování** v C++. Umožňují nám psát kód (funkce nebo třídy) bez přesného určení datových typů, se kterými bude pracovat. Datový typ je specifikován až v momentě, kdy je šablona použita.

To nám umožňuje psát flexibilní a znovupoužitelný kód, který funguje pro `int`, `double`, `std::string` nebo jakýkoli vlastní datový typ, aniž bychom museli kód duplikovat.

## 1. Šablony funkcí (Function Templates)

Šablona funkce je "recept" na funkci. Kompilátor podle ní automaticky vygeneruje konkrétní verzi funkce pro každý datový typ, se kterým ji zavoláme.

Definují se pomocí klíčového slova `template` následovaného `typename` (nebo `class`) a jménem zástupného typu (běžně `T`).

**Příklad:** Místo psaní `maxInt(int a, int b)` a `maxDouble(double a, double b)` napíšeme jednu šablonu:

```cpp
#include <iostream>

// Definice šablony funkce
template <typename T>
T getMax(T a, T b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    // Kompilátor sám pozná (podle typů argumentů), že má vytvořit:
    
    // 1. Verzi pro int: getMax(int a, int b)
    std::cout << "Vetsi z 5 a 10 je: " << getMax(5, 10) << std::endl;

    // 2. Verzi pro double: getMax(double a, double b)
    std::cout << "Vetsi z 3.14 a 2.71 je: " << getMax(3.14, 2.71) << std::endl;

    // 3. Verzi pro std::string: getMax(std::string a, std::string b)
    // (Funguje, protože operátor '>' je pro string definován)
    std::cout << "Vetsi z 'auto' a 'zebra' je: " << getMax(std::string("auto"), std::string("zebra")) << std::endl;

    // Můžeme typ specifikovat i explicitně:
    std::cout << "Vetsi z 5 a 10.5 je: " << getMax<double>(5, 10.5) << std::endl;
}
```

## 2. Šablony tříd (Class Templates)

Stejný princip můžeme aplikovat na celé třídy. To je extrémně užitečné pro vytváření tzv. **kontejnerových tříd** (jako `std::vector` nebo `std::map`), které mohou uchovávat různé datové typy.

**Příklad:** Třída `Box`, která může uchovávat jeden libovolný předmět.

```cpp
#include <iostream>
#include <string>

// Definice šablony třídy
template <typename T>
class Box {
private:
    T item; // Atribut 'item' má generický typ T

public:
    // Konstruktor
    Box(T newItem) {
        this->item = newItem;
    }

    // Metoda pro získání hodnoty
    T getItem() {
        return this->item;
    }
};

int main() {
    // Vytvoříme instanci Box, která bude uchovávat int
    // Kompilátor vytvoří třídu Box<int>
    Box<int> intBox(123);
    std::cout << "V krabici na cisla je: " << intBox.getItem() << std::endl;

    // Vytvoříme instanci Box, která bude uchovávat std::string
    // Kompilátor vytvoří třídu Box<std::string>
    Box<std::string> stringBox("Ahoj svete");
    std::cout << "V krabici na text je: " << stringBox.getItem() << std::endl;
}
```

Šablony jsou základním kamenem **Standard Template Library (STL)**, která poskytuje předpřipravené a efektivní kontejnery, iterátory a algoritmy.
---
## **Cvičení**

### **1. Šablona funkce**
Vytvořte šablonu funkce `vymen(T& a, T& b)`, která prohodí hodnoty dvou proměnných libovolného typu. Vyzkoušejte pro `int`, `double` a `string`.

### **2. Šablona třídy**
Napište šablonovou třídu `Schranka<T>`, která bude uchovávat jednu hodnotu typu `T`.
- Metodu `vloz(T data)`
- Metodu `T vyzvedni()`
Vyzkoušejte pro různá data.
