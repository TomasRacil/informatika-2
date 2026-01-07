# **07 - Práce se soubory**

Dosud jsme všechny vstupy zadávali ručně do konzole a výstupy našeho programu po jeho ukončení zmizely. V reálných aplikacích je však potřeba data uchovávat trvale. Práce se soubory nám umožňuje data číst z externích zdrojů a ukládat výsledky naší práce na disk. V C++ pro tyto operace slouží knihovna `<fstream>`.

## **Čtení ze souboru (Input)**

Pro čtení dat ze souboru používáme třídu `std::ifstream` (input file stream).

### **Základní postup**

1. **Vložit knihovnu:** `#include <fstream>` 
2. **Vytvořit objekt:** `std::ifstream vstupniProud("nazev_souboru.txt")`;  
3. **Zkontrolovat otevření:** Vždy je kriticky důležité ověřit, zda se soubor podařilo otevřít.  
4. **Číst data:** Data můžeme číst různými způsoby.  
5. **Zavřít soubor:** Po dokončení práce se soubor automaticky zavře, když proměnná zanikne. Explicitní zavření pomocí `vstupniProud.close();` je dobrým zvykem pro přehlednost.

### **Způsoby čtení dat**

#### **1. Čtení řádek po řádku**

Nejběžnější způsob, ideální pro zpracování textových souborů, kde každý řádek představuje jednu informaci. Používáme funkci `std::getline()`.

```cpp
#include <string>  
#include <fstream>  
#include <iostream>

std::ifstream soubor("data.txt");  
std::string radek;

if (soubor.is_open()) {  
    while (std::getline(soubor, radek)) {  
        std::cout << radek << std::endl;  
    }  
    soubor.close();  
}
```

#### **2. Čtení slovo po slovu**

Standardní `>>` operátor čte data ze souboru a automaticky se zastavuje na bílých znacích (mezera, tabulátor, nový řádek).

```cpp
std::ifstream soubor("data.txt");  
std::string slovo;

if (soubor.is_open()) {  
    while (soubor >> slovo) {  
        // Zpracuj jedno slovo  
    }  
    soubor.close();  
}
```

## **Zápis do souboru (Output)**

Pro zápis dat do souboru používáme třídu `std::ofstream` (output file stream).

### **Vytvoření nebo přepsání souboru**

Pokud soubor neexistuje, `std::ofstream` ho vytvoří. Pokud již existuje, **ve výchozím nastavení jeho obsah smaže** a začne zapisovat od začátku.

```cpp
// Otevře soubor pro zápis. Pokud existuje, jeho obsah se smaže.  
std::ofstream vystupniProud("vystup.txt");

if (vystupniProud.is_open()) {  
    vystupniProud << "Toto je prvni radek.n";  
    vystupniProud << "Toto je druhy radek." << std::endl;  
    vystupniProud.close();  
}
```

### **Přidání na konec souboru (Append)**

Pokud chceme data pouze přidat na konec existujícího souboru bez jeho smazání, musíme při otevírání specifikovat mód `std::ios::app` (append).

```cpp
// Otevře soubor pro zápis v "append" módu  
std::ofstream vystupniProud("vystup.txt", std::ios::app);

if (vystupniProud.is_open()) {  
    vystupniProud << "Tento radek byl pridan na konec.n";  
    vystupniProud.close();  
}
```

## **Kontrola chyb**

Nejdůležitějším krokem při práci se soubory je kontrola, zda se operace podařila.

```cpp
std::ifstream soubor("neexistujici_soubor.txt");

if (!soubor.is_open()) {  
    // Případně std::cerr pro chybový výstup  
    std::cout << "Chyba: Soubor se nepodarilo otevrit!" << std::endl;  
    // Zde je vhodné program ukončit, protože nemůže pokračovat  
}
```
---
## **Cvičení**

### **1. Deníček**
Vytvořte program, který umožní uživateli zadávat textové poznámky.
- Ukládejte každý řádek do souboru `denicek.txt`.
- Zadávání skončí, když uživatel napíše slovo "KONEC".

### **2. Čtečka souboru**
Napište program, který otevře soubor `denicek.txt` (vytvořený v předchozím úkolu) a vypíše jeho obsah na obrazovku.
- Před každý řádek přidejte číslo řádku (např. "1: Můj první zápis").
- Ošetřete situaci, kdy soubor neexistuje.
