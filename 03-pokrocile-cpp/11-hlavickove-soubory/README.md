# **10 - Hlavičkové soubory (`.h`) a Implementační soubory (`.cpp`)**

Jakmile programy začnou být větší, je neudržitelné mít veškerý kód v jednom `main.cpp` souboru. Kód potřebujeme rozdělit do logických celků, což v C++ děláme pomocí dvou typů souborů:

1. **Hlavičkové soubory (`.h` nebo `.hpp`)**  
2. **Implementační (zdrojové) soubory (`.cpp`)**

Toto rozdělení je základním principem pro organizaci, znovupoužitelnost a efektivitu kompilace v C++.

## **Proč kód rozdělovat?**

Hlavním důvodem je oddělení **deklarace** (co něco dělá - jeho rozhraní) od **definice** (jak to dělá - jeho implementace).

* **Deklarace (co):** Říká kompilátoru: "Neboj, někde v programu existuje funkce s tímto jménem, která přijímá tyto parametry a vrací tento typ." (Např. `int secti(int a, int b);`)  
* **Definice (jak):** Obsahuje samotný kód (tělo) funkce. (Např. `int secti(int a, int b) { return a + b; }`)

### **Výhody tohoto přístupu:**

1. **Organizace:** Kód je přehlednější. Hlavičkový soubor slouží jako dokumentace rozhraní – rychle vidíte, jaké funkce a třídy daný modul nabízí.  
2. **Znovupoužitelnost:** Chcete-li použít svou knihovnu `Matematika` v jiném projektu, stačí přiložit `Matematika.h` a linknout zkompilovaný `Matematika.cpp` (nebo knihovnu `.lib`/`.a`).  
3. **Efektivita kompilace:** Kdybyste veškerý kód napsali do `.h` souborů a ty vložili (`#include`) do více `.cpp` souborů, každý `.cpp` soubor by kompiloval tu samou věc znovu a znovu. Ještě hůře, linker by narazil na chybu "vícenásobné definice" (One Definition Rule - ODR violation). Oddělením implementace do `.cpp` souborů zajistíme, že každá funkce je definována (a kompilována) pouze jednou.

## **Hlavičkový soubor (`.h` nebo `.hpp`)**

Hlavičkový soubor (header) definuje **rozhraní** (co modul umí).

**Co sem patří:**

* Deklarace funkcí (prototypy).  
* Definice tříd (`class`) a struktur (`struct`).  
* Deklarace `extern` globálních proměnných (i když globálním proměnným je lepší se vyhnout).  
* Definice konstant (`const`, `constexpr`).  
* Definice inline funkcí.

### **Zábrany proti vícenásobnému vložení (Include Guards)**

Pokud soubor `A.h` includuje `B.h` a zároveň soubor `C.h` includuje `B.h`, a váš `main.cpp` pak includuje `A.h` i `C.h`, soubor `B.h` by byl do main.cpp vložen dvakrát. To by vedlo k chybě "vícenásobné definice".

Aby se tomu zabránilo, používají se "include guards".

**Moderní způsob (preferovaný):** Na první řádek hlavičkového souboru napište:  

```cpp
#pragma once
```

**Tradiční způsob (funguje všude):**

```cpp
#ifndef NAZEV_SOUBORU_H  
#define NAZEV_SOUBORU_H

// ... celý obsah .h souboru ...

#endif // NAZEV_SOUBORU_H
```

Oba přístupy zajistí, že obsah souboru bude do jedné kompilační jednotky (jednoho `.cpp` souboru) vložen pouze jednou.

## **Implementační soubor (`.cpp`)**

Implementační soubor (source) obsahuje **definice** (těla) funkcí a metod, které byly deklarovány v odpovídajícím hlavičkovém souboru.

**Co sem patří:**

* `#include` odpovídajícího `.h` souboru (jako první, pro kontrolu).  
* `#include` dalších knihoven, které jsou potřeba *pouze* pro implementaci (např. `<iostream>` pro výpis).  
* Definice (těla) funkcí a metod.  
* Definice privátních statických proměnných.

### **Rozdíl mezi `#include <...>` a `#include "..."`**

* `#include <knihovna>`: Říká kompilátoru, aby hledal soubor ve **standardních systémových složkách** (kde jsou nainstalovány knihovny jako `iostream`, `string`, `vector` atd.).  
* `#include "soubor.h"`: Říká kompilátoru, aby hledal soubor **nejprve v aktuálním adresáři** (nebo v adresářích specifikovaných v projektu) a až poté v systémových složkách. Používá se pro lokální hlavičkové soubory projektu.

## **Příklad**

Podívejte se na soubory `Matematika.h`, `Matematika.cpp` a `main.cpp` v tomto adresáři, které demonstrují toto rozdělení v praxi.

### **Jak to funguje při kompilaci?**

Proces kompilace se skládá ze dvou hlavních fází:

1. **Kompilace (Compilation):**  
   * Kompilátor vezme `main.cpp` a vloží do něj obsah `Matematika.h`. Vytvoří "translation unit". Zkontroluje, že voláte funkci `secti` správně (podle deklarace v `.h`). Vytvoří soubor `main.o` (objektový soubor), který obsahuje kód z `main.cpp` a poznámku, že mu chybí definice funkce secti.  
   * Kompilátor vezme `Matematika.cpp` a vloží do něj obsah `Matematika.h`. Vytvoří "translation unit". Zkompiluje tělo funkce `secti`. Vytvoří soubor `Matematika.o`, který obsahuje zkompilovaný kód funkce secti.  
2. **Linkování (Linking):**  
   * Linker vezme `main.o` a `Matematika.o`.  
   * Vidí, že `main.o` potřebuje funkci secti.  
   * Najde funkci secti v `Matematika.o`.  
   * Propojí je dohromady a vytvoří finální spustitelný soubor (např. `program.exe`).
---
## **Cvičení**

### **1. Rozdělení programu**
Máte jednoduchý program v jednom souboru:
```cpp
int secti(int a, int b) { return a + b; }
int main() { cout << secti(1, 2); }
```
Rozdělte ho na tři soubory:
- `matematika.h` (hlavička funkce)
- `matematika.cpp` (tělo funkce)
- `main.cpp` (volání funkce)

### **2. Kompilace**
Zkuste program zkompilovat. Pokud používáte příkazovou řádku, nezapomeňte uvést oba .cpp soubory:
`g++ main.cpp matematika.cpp -o program`
