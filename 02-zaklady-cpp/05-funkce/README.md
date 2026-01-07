# **Funkce**

Funkce jsou pojmenované bloky kódu, které provádějí specifický úkol. Umožňují nám rozdělit velký a složitý program na menší, lépe spravovatelné a znovupoužitelné části. Místo opakovaného psaní stejného kódu ho napíšeme jednou do funkce a pak ji jen voláme podle potřeby.

Každý C++ program má alespoň jednu funkci: `main()`, která je vstupním bodem programu.

## **Anatomie funkce**

Funkce se skládá z hlavičky a těla:
```cpp
návratový_typ název_funkce(typ_parametru1 název_parametru1, ...) {  
    // Tělo funkce - příkazy, které se mají vykonat  
    return hodnota; // Nepovinné, záleží na návratovém typu  
}
```

* **Návratový typ:** Datový typ hodnoty, kterou funkce vrací pomocí příkazu `return`. Pokud funkce nic nevrací, používá se klíčové slovo `void`.  
* **Název funkce:** Unikátní jméno, pod kterým funkci voláme.  
* **Parametry (argumenty):** Seznam proměnných, které funkce přijímá jako vstup. Jsou nepovinné.  
* **Tělo funkce:** Blok kódu uzavřený ve složených závorkách `{}`, který se vykoná při zavolání funkce.

## **Deklarace vs. Definice**

* **Definice funkce:** Kompletní kód funkce (hlavička i tělo).  
* **Deklarace funkce (prototyp):** Pouze hlavička funkce ukončená středníkem. Říká kompilátoru, že funkce existuje, i když její tělo je definováno až později v kódu (typicky za funkcí `main`). To nám umožňuje volat funkce před jejich plnou definicí.

```cpp
// Deklarace (prototyp) funkce  
int secti(int a, int b);

int main() {  
    int vysledek = secti(5, 3); // Funkci můžeme volat, protože byla deklarována  
    return 0;  
}

// Definice funkce  
int secti(int a, int b) {  
    return a + b;  
}
```

## **Typy funkcí**

### **1. Funkce bez návratové hodnoty a bez parametrů**

Nejjednodušší typ funkce. Nic nepřijímá a nic nevrací, pouze vykoná nějakou činnost.

```cpp
void pozdrav() {  
    std::cout << "Ahoj!" << std::endl;  
}
```

### **2. Funkce s parametry, ale bez návratové hodnoty**

Přijímá vstupní data, se kterými pracuje, ale nevrací žádný výsledek.

```cpp
void vypisSoucet(int x, int y) {  
    std::cout << "Soucet je: " << (x + y) << std::endl;  
}
```

### **3. Funkce s návratovou hodnotou**

Přijímá parametry, provede výpočet a výsledek vrátí pomocí klíčového slova `return`.

```cpp
int secti(int a, int b) {  
    int soucet = a + b;  
    return soucet; // Vrátí hodnotu proměnné 'soucet'  
}
```

Návratovou hodnotu pak můžeme přiřadit do proměnné: `int vysledek = secti(10, 5);`

## **Přetěžování funkcí (Function Overloading)**

V C++ můžeme mít více funkcí se stejným názvem, pokud se liší v počtu nebo typech svých parametrů. Tomu se říká přetěžování. Kompilátor automaticky vybere správnou verzi funkce podle argumentů, se kterými je volána.

```cpp
int secti(int a, int b);       // Sčítá dvě celá čísla  
double secti(double a, double b); // Sčítá dvě desetinná čísla  
```
---
## **Cvičení**

### **1. Najdi maximum**
Napište funkci `int maximum(int a, int b)`, která vrátí větší z obou čísel. V `main` funkci ji vyzkoušejte na datech od uživatele.

### **2. Opakovaný pozdrav**
Napište funkci `void pozdrav(int n)`, která `n`-krát vypíše "Ahoj!".

### **3. Přetěžování**
Vytvořte dvě funkce se jménem `vypis`:
1. Jedna přijímá `int` parametry a vypíše: "Cislo: [hodnota]".
2. Druhá přijímá `std::string` a vypíše: "Text: [hodnota]".
Ověřte, že kompilátor vybere správnou funkci podle typu argumentu.
