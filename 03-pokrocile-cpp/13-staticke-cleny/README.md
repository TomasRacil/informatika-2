# **12 - Statické členy (Static Members)**

Standardně je každý atribut (členská proměnná) unikátní pro každou instanci (objekt) třídy. Pokud vytvoříte 10 objektů třídy `Student`, každý z nich bude mít vlastní `jmeno` a `vek`.

Někdy ale potřebujeme mít proměnnou, která je **společná pro všechny instance dané třídy**. K tomu slouží klíčové slovo `static`.

## **1. Statické atributy (Static Member Variables)**

Statický atribut existuje v paměti pouze **jednou**, bez ohledu na to, kolik objektů třídy vytvoříme (i kdybychom nevytvořili žádný). Je sdílený všemi instancemi.

* **Deklarace:** Uvnitř třídy s klíčovým slovem `static`.  
* **Definice/Inicializace:** Musí být definován **mimo** třídu (typicky v .cpp souboru), aby pro něj byla alokována paměť.

**Kdy se používá?**

* Počítadlo instancí (viz příklad).  
* Sdílené konstanty pro celou třídu (např. `static const double PI = 3.14159;`).  
* Sdílené zdroje (např. ukazatel na společnou databázi).

```cpp
// V souboru Auto.h  
class Auto {  
public:  
    // Statický atribut - počítadlo  
    static int pocetVyrobenychAut;

    Auto() {  
        // Zvýšíme společné počítadlo při každém vytvoření objektu  
        pocetVyrobenychAut++;  
    }  
};

// V souboru Auto.cpp (nebo main.cpp, pokud je vše v jednom souboru)  
// Inicializace statického atributu. Musí být mimo třídu!  
int Auto::pocetVyrobenychAut = 0; 
```

## **2. Statické metody (Static Member Functions)**

Statická metoda je funkce, která patří třídě, nikoli konkrétnímu objektu.

* **Volání:** Lze ji volat přímo přes název třídy pomocí operátoru `::` (např. `Auto::getVyrobeno()`), aniž bychom museli mít vytvořený objekt.  
* **Omezení:** Protože nepatří žádné konkrétní instanci, **nemá přístup k ukazateli `this`**. Z toho plyne, že statická metoda může přistupovat **pouze k jiným statickým členům** (atributům nebo metodám) dané třídy.

```cpp
// V souboru Auto.h  
class Auto {  
public:  
    static int pocetVyrobenychAut;  
    std::string model;

    Auto(std::string m) : model(m) {  
        pocetVyrobenychAut++;  
    }

    // Statická metoda  
    static int getPocetVyrobenychAut() {  
        return pocetVyrobenychAut;  
          
        // CHYBA: Statická metoda nemá 'this', neví, o jaký model jde.  
        // return this->model;   
    }  
};

// V souboru Auto.cpp  
int Auto::pocetVyrobenychAut = 0;

// V souboru main.cpp  
int main() {  
    // Statickou metodu voláme PŘED vytvořením jakéhokoliv objektu  
    std::cout << "Vyrobeno aut: " << Auto::getPocetVyrobenychAut() << std::endl; // Vypíše 0

    Auto a1("Skoda");  
    Auto a2("BMW");

    // Voláme ji znovu po vytvoření objektů  
    std::cout << "Vyrobeno aut: " << Auto::getPocetVyrobenychAut() << std::endl; // Vypíše 2  
}
```

Ukázku kompletního kódu najdete v souboru main.cpp.
---
## **Cvičení**

### **1. Počítadlo instancí**
Vytvořte třídu `Hrac`.
1. Přidejte jí private statický atribut `pocetHracu`.
2. V konstruktoru ho inkrementujte.
3. V destruktoru ho dekrementujte.
4. Přidejte public statickou metodu `getPocet()`.
5. V `main` vytvořte několik hráčů (některé i v bloku `{}` či dynamicky) a průběžně vypisujte aktuální počet.
