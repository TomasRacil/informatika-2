## 9. Přetěžování operátorů (Operator Overloading)

Přetěžování operátorů je mechanismus v C++, který umožňuje programátorovi definovat vlastní chování pro standardní operátory (jako `+`, `-`, `*`, `==`, `<<` atd.) pro uživatelsky definované typy (tedy pro naše **třídy** a **struktury**).

Cílem je, aby byl kód čitelnější a intuitivnější. Místo psaní `vysledek = v1.secti(v2);` můžeme psát přirozeně `vysledek = v1 + v2;`.

### Jak to funguje?

Operátor je v C++ ve skutečnosti jen "syntaktický cukr" (syntactic sugar) pro volání funkce se speciálním názvem. Například `a + b` je interně chápáno jako `a.operator+(b)` (pokud je operátor implementován jako členská funkce) nebo `operator+(a, b)` (pokud je implementován jako volná funkce).

#### Syntaxe

Funkce operátoru se definuje pomocí klíčového slova `operator` následovaného symbolem operátoru, který přetěžujeme.

```c++
class Vektor2D {
public:
    double x, y;

    // Přetížení operátoru '+' jako ČLENSKÉ funkce
    // 'this' je levý operand (a), 'other' je pravý operand (b)
    Vektor2D operator+(const Vektor2D& other) {
        return Vektor2D(this->x + other.x, this->y + other.y);
    }
};
````

### Členská vs. Volná funkce

Operátory můžeme implementovat dvěma způsoby:

1.  **Jako členskou funkci třídy:**

      * Levý operand je vždy objekt `*this`.
      * Funkce má o jednoho parametru méně (např. `+` má jen jeden parametr, ten pravý).
      * Nemůže fungovat, pokud je levý operand jiného typu (např. `5 * mujVektor` by selhalo, pokud je `*` jen členská funkce `Vektor2D`).

2.  **Jako volnou (nečlenskou) funkci:**

      * Bere oba operandy jako parametry (např. `operator+(v1, v2)`).
      * Je flexibilnější pro pořadí operandů (můžeme definovat `operator*(int, Vektor2D)` i `operator*(Vektor2D, int)`).
      * Pokud potřebuje přístup k privátním členům třídy, musí být tato funkce označena jako **`friend`** (přítel) v definici třídy.

### Přetěžování `<<` pro `std::cout`

Typickým příkladem volné funkce je přetěžování operátoru `<<` pro výpis do `std::ostream` (jako je `std::cout`).

Musí to být volná funkce, protože levý operand je `std::cout` (typu `std::ostream`), a my nemůžeme měnit definici třídy `std::ostream` a přidat jí tam naši členskou funkci.

```c++
#include <iostream>

class Vektor2D {
public:
    double x, y;
    // ... konstruktor ...

    // Deklarujeme, že tato volná funkce je "přítel"
    // a smí přistupovat k našim 'private' a 'protected' členům
    friend std::ostream& operator<<(std::ostream& os, const Vektor2D& v);
};

// Implementace volné funkce
std::ostream& operator<<(std::ostream& os, const Vektor2D& v) {
    os << "Vektor(" << v.x << ", " << v.y << ")";
    return os; // Musíme vrátit stream, aby fungovalo řetězení
}

int main() {
    Vektor2D v(1, 2);
    std::cout << "Můj vektor: " << v << std::endl; // Funguje!
}
```

> **Byl zde `friend` nutný?** Nebyl, protože `Vektor2D` je třída s `public` členy `x` a `y`, tedy technicky `friend` není potřeba. **Pokud by však `Vektor2D` členy `x` a `y` byly `private`**, pak by `operator<<` (jakožto volná funkce) k těmto členům neměl přístup. V takovém případě by bylo **nutné** deklarovat `operator<<` uvnitř třídy `Vektor2D` jako `friend`, aby získal oprávnění přistupovat k privátním členům.

### Třídy vs. Struktury

Funguje to i pro struktury? **Ano, funguje to úplně stejně.**

Připomeňme, že v C++ je jediný strukturální rozdíl mezi `class` a `struct` ve výchozím přístupu:

* `class` má vše ve výchozím stavu `private`.
* `struct` má vše ve výchozím stavu `public`.

Jinak jsou si funkčně rovny: obě mohou mít konstruktory, destruktory, metody (včetně virtuálních), mohou dědit a mohou mít přetížené operátory. Zvykově se `struct` často používá pro jednodušší datové struktury s převážně veřejnými členy, zatímco `class` pro složitější objekty se zapouzdřením.

### Další běžně přetěžované operátory:

Kromě `+`, `==` a `<<` se často přetěžují i další operátory pro intuitivnější práci s objekty:

* **Aritmetické:** `-`, `*`, `/`, `%`, `++`, `--`, `+=`, `-=` atd.
* **Relační:** `!=`, `<`, `>`, `<=`, `>=` (pro porovnávání objektů).
* **Přiřazovací:** `=` (operátor přiřazení má specifická pravidla, zejména tzv. "Rule of Three/Five/Zero").
* **Indexovací:** `[]` (pro přístup k prvkům jako u pole).
* **Vstupní:** `>>` (pro načítání objektu z `std::cin` nebo souboru).
* **Funkční volání:** `()` (umožňuje "volat" objekt jako funkci).


Praktickou ukázku přetěžování operátorů `+`, `==` a `<<` najdete v souboru `main.cpp`.
---
## **Cvičení**

### **1. Komplexní čísla**
Vytvořte třídu `KomplexniCislo` (reálná a imaginární část).
1. Přetěžte operátor `+` tak, abyste mohli sečíst dvě komplexní čísla (sečtou se reálné části a imaginární části zvlášť).
2. Přetěžte operátor `<<` pro hezký výpis ve formátu "a + bi".

### **2. Porovnání**
Přetěžte operátor `==`, který vrátí `true`, pokud jsou dvě komplexní čísla shodná (mají stejnou reálnou i imaginární část).
