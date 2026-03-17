# **Pole a řetězce**

Pole je datová struktura, která nám umožňuje uložit pevně daný počet prvků **stejného datového typu** do souvislého bloku paměti. Můžeme si ho představit jako řadu přihrádek, kde každá má své číslo (index) a obsahuje jednu hodnotu.

## **Jednorozměrná pole**

Nejzákladnější typ pole, který si lze představit jako jednoduchý seznam hodnot.

### **Deklarace a inicializace**

Při deklaraci pole musíme specifikovat jeho typ, název a velikost (počet prvků) v hranatých závorkách `[]`.
```cpp
// Deklarace pole 'cisla' pro 5 celých čísel.  
// Hodnoty jsou zatím nedefinované (mohou být náhodné).  
int cisla[5];

// Deklarace s přímou inicializací.  
// Velikost pole je automaticky určena počtem prvků.  
double znamky[] = {1.5, 2.0, 1.0, 3.5};
```

### **Přístup k prvkům**

K jednotlivým prvkům pole přistupujeme pomocí jejich **indexu**, což je celé číslo udávající pozici prvku. **Indexování v C++ začíná od 0!** První prvek má tedy index 0, druhý 1, a tak dále.

```cpp
int cisla[3] = {10, 20, 30};

std::cout << cisla[0]; // Vypíše 10  
std::cout << cisla[1]; // Vypíše 20

cisla[2] = 35; // Změní hodnotu na 3. pozici (index 2) na 35
```

**Pozor:** Pokus o přístup k prvku mimo rozsah pole (např. cisla[5] u pole o velikosti 5) vede k nedefinovanému chování a je častou příčinou pádů programů.

### **Procházení pole**

Nejčastěji se pole prochází pomocí for cyklu, kde řídicí proměnná cyklu slouží jako index.

```cpp
int cisla[] = {2, 4, 6, 8, 10};  
// Velikost pole zjistíme vydělením celkové velikosti v bajtech  
// velikostí jednoho prvku v bajtech.  
int velikost = sizeof(cisla) / sizeof(cisla[0]);

for (int i = 0; i < velikost; i++) {  
    std::cout << cisla[i] << std::endl;  
}
```

## **Řetězce (Strings)**

V C++ existují dva hlavní způsoby, jak pracovat s textem:

### **1. C-style řetězce (pole znaků)**

Tradiční způsob převzatý z jazyka C. Řetězec je pole znaků (char), které je ukončeno speciálním nulovým znakem '0'.

```cpp
char pozdrav[] = "Ahoj"; // Kompilátor automaticky přidá '0' na konec  
// V paměti je uloženo: {'A', 'h', 'o', 'j', '0'}
```

Práce s nimi je nízkoúrovňová a náchylná k chybám (např. přetečení bufferu).

### **2. `std::string` (doporučený způsob)**

Moderní, bezpečný a mnohem pohodlnější způsob. `std::string` je třída ze standardní knihovny. Pro její použití musíme vložit hlavičkový soubor `#include <string>`.

* Automaticky spravuje paměť.  
* Poskytuje mnoho užitečných metod (zjištění délky, spojování, vyhledávání...).

```cpp
#include <string>

std::string jmeno = "Karel";  
std::string prijmeni = "Novak";

// Jednoduché spojování pomocí operátoru +  
std::string celeJmeno = jmeno + " " + prijmeni;

std::cout << "Delka jmena: " << jmeno.length() << std::endl;
```

## **Vícerozměrná pole**

Můžeme vytvářet i pole polí, tzv. vícerozměrná pole. Nejčastěji se používají dvourozměrná pole pro reprezentaci matic nebo herních ploch.

```cpp
// Matice 2x3 (2 řádky, 3 sloupce)  
int matice[2][3] = {  
    {1, 2, 3},  
    {4, 5, 6}  
};

// Přístup k prvku v prvním řádku (index 0) a druhém sloupci (index 1)  
int prvek = matice[0][1]; // prvek bude 2  
```
---
## **Cvičení**

### **1. Statistika pole**
Vytvořte pole pro uložení 5 celých čísel (načtěte je od uživatele).
- Vypočtěte a vypište jejich součet.
- Vypočtěte a vypište průměr.

### **2. Maximum v poli**
Mějte pole čísel (např. `{10, 5, 23, 8, 12}`). Pomocí cyklu najděte a vypište největší číslo v tomto poli.

### **3. Spojování jmen**
Napište program, který:
1. Načte křestní jméno a příjmení do proměnných typu `std::string`.
2. Vytvoří třetí proměnnou a spojí je dohromady (s mezerou).
3. Vypíše celé jméno a počet jeho znaků (délku).
