# **Větvení**

Větvení umožňuje programu rozhodovat se na základě podmínek a vykonávat různé části kódu podle toho, zda je podmínka splněna (`true`) nebo ne (`false`).

### **`if` / `else if` / `else`**

Základní konstrukce pro rozhodování.

* `if`: Vykoná blok kódu, pokud je zadaná podmínka `true`.  
* `else if`: Pokud předchozí `if` (nebo `else if`) podmínka byla `false`, testuje se nová podmínka. Můžeme jich mít několik za sebou.  
* `else`: Vykoná blok kódu, pokud žádná z předchozích `if` nebo `else if` podmínek nebyla `true`.

```cpp
int vek = 18;

if (vek < 18) {  
    std::cout << "Nejsi plnolety." << std::endl;  
} else if (vek == 18) {  
    std::cout << "Gratuluji, prave jsi dosahl plnoletosti!" << std::endl;  
} else {  
    std::cout << "Jsi plnolety." << std::endl;  
}
```

### **`switch`**

Příkaz `switch` je vhodný, když potřebujeme porovnat jednu proměnnou s více možnými **konstantními** hodnotami. Je často přehlednější než dlouhá série `if-else if`.

* `case`: Definuje hodnotu, se kterou se porovnává.  
* `break`: **Nezbytný** k ukončení `switch` bloku po nalezení shody. Bez něj by program pokračoval ve vykonávání kódu všech následujících `case` bloků (tomuto se říká "propadávání" - fallthrough).  
* `default`: Podobné jako `else`, vykoná se, pokud žádný `case` neodpovídá hodnotě.

```cpp
char znamka = 'B';

switch (znamka) {  
    case 'A':  
        std::cout << "Vyborne!" << std::endl;  
        break;  
    case 'B':  
        std::cout << "Chvalitebne." << std::endl;  
        break;  
    case 'C':  
        std::cout << "Dobre." << std::endl;  
        break;  
    default:  
        std::cout << "Je potreba se vice ucit." << std::endl;  
        break;  
}
```
## **Zpracování výjimek (`try`, `catch`, `throw`)**

Způsob pro ošetření chyb, které mohou nastat hluboko uvnitř volaných funkcí.

* **`try`**: Blok kódu, ve kterém očekáváme, že může nastat chyba (výjimka).  
* **`throw`**: "Vyhodí" výjimku, když nastane chyba. Tím se přeruší normální běh programu a hledá se odpovídající catch.  
* **`catch`**: Blok kódu, který "chytí" vyhozenou výjimku a zpracuje ji. Program pak může pokračovat.
```cpp
double delenec = 10.0;  
double delitel = 0.0;

try {  
    if (delitel == 0) {  
        throw std::runtime_error("Deleni nulou!");  
    }  
    double vysledek = delenec / delitel;  
    std::cout << "Vysledek: " << vysledek << std::endl;  
}  
catch (const std::runtime_error& e) {  
    std::cerr << "Nastala chyba: " << e.what() << std::endl;  
}
```

`std::cerr` je standardní chybový výstup, podobný `std::cout`, ale určený pro chybové hlášky.

### ** Vícenásobné a obecné `catch` bloky**

Můžeme definovat více `catch` bloků pro jeden `try` blok, abychom mohli zpracovat různé typy výjimek odlišně. Jako poslední záchranu můžeme použít `catch (...)`, který zachytí jakoukoliv výjimku, která nebyla zachycena předchozími `catch` bloky.

```cpp
try {
    throw 42; // Vyhodíme výjimku typu int
}
catch (const std::runtime_error& e) {
    // Tento blok se přeskočí
}
catch (...) {
    // Tato výjimka bude zachycena zde
    std::cerr << "Byla zachycena neznámá chyba!" << std::endl;
}
```
---
## **Cvičení**

### **1. Hodnocení studentů**
Napište program, který načte počet bodů z testu (0-100) a vypíše známku:
- 90-100: A
- 80-89: B
- 70-79: C
- 60-69: D
- 0-59: F
Použijte `if` / `else if` / `else`.

### **2. Dny v týdnu**
Pomocí `switch` vytvořte program, který podle zadaného čísla (1-7) vypíše název dne v týdnu. Pokud uživatel zadá jiné číslo, vypište "Neplatný den".

### **3. Bezpečné dělení**
Vytvořte program, který načte dvě čísla a provede dělení. Použijte `try-catch` blok pro ošetření dělení nulou (vyhoďte výjimku, pokud je dělitel 0).
