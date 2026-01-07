## 6. Konstruktory a Destruktory

Když vytvoříme objekt (instanci třídy), často potřebujeme, aby měl nějaké výchozí hodnoty nebo aby provedl nějakou počáteční akci (např. alokoval paměť). Stejně tak, když objekt zaniká, možná potřebujeme "uklidit" (např. uvolnit alokovanou paměť). K tomu slouží speciální metody: **konstruktor** a **destruktor**.

### Konstruktor (Constructor)

Konstruktor je speciální metoda, která se **automaticky volá v momentě vytvoření objektu**. Jejím hlavním úkolem je inicializovat atributy (členské proměnné) objektu a zajistit, aby byl objekt ihned po svém vzniku v platném a použitelném stavu.

**Pravidla pro konstruktor:**
1.  Musí mít **stejné jméno jako třída**.
2.  Nemá **žádnou návratovou hodnotu** (ani `void`).
3.  Může mít parametry (stejně jako běžná funkce).

```c++
class Person {
public:
    string jmeno;
    int vek;

    // Toto je konstruktor
    Person(string jmenoParam, int vekParam) {
        jmeno = jmenoParam;
        vek = vekParam;
    }
};

int main() {
    // Zde se automaticky volá konstruktor třídy Person
    Person osoba1("Jan", 30); 
    
    // Nyní má objekt 'osoba1' rovnou nastavené hodnoty
    cout << osoba1.jmeno << endl; // Vypíše "Jan"
    
    return 0;
}
```

#### Výchozí konstruktor (Default Constructor)

Je to konstruktor, který nepřijímá žádné argumenty.

```c++
class Auto {
public:
    int pocetDveri;

    // Výchozí konstruktor
    Auto() {
        pocetDveri = 5; // Vždy se vytvoří s 5 dveřmi
    }
};

int main() {
    Auto mojeAuto; // Automaticky se volá Auto()
    cout << mojeAuto.pocetDveri; // Vypíše 5
}
```

> **Důležité:** Pokud ve třídě nedefinujete *žádný* konstruktor, kompilátor za vás vytvoří prázdný výchozí konstruktor sám (nic neinicializuje). Pokud ale definujete *jakýkoliv* vlastní konstruktor (např. ten s parametry), kompilátor už výchozí konstruktor **nevytvoří**. Pokud byste ho přesto potřebovali (například pro vytvoření pole objektů bez explicitních parametrů), musíte si ho definovat sami (může být i prázdný: `NazevTridy() {}` nebo explicitně výchozí: `NazevTridy() = default;`).

### Destruktor (Destructor)

Destruktor je opakem konstruktoru. Je to speciální metoda, která se **automaticky volá v momentě zániku (zničení) objektu**.

Objekt zaniká, když:

1.  Opouští svůj *scope* (rozsah platnosti) – např. lokální proměnná na konci funkce.
2.  Je na ukazatel na objekt zavoláno klíčové slovo `delete`.

> Hlavním úkolem destruktoru je **uvolnit zdroje**, které objekt během svého života alokoval. Nejčastěji se jedná o uvolnění dynamicky alokované paměti (pomocí `delete` nebo `delete[]`), zavření souborů nebo uvolnění jiných systémových prostředků. Tím se zajišťuje správná správa zdrojů a předchází se například únikům paměti (memory leaks), jak je ukázáno v přiloženém `main.cpp`.

**Pravidla pro destruktor:**

1.  Musí mít **stejné jméno jako třída**, ale s vlnovkou (`~`) na začátku.
2.  Nemá **žádnou návratovou hodnotu** (ani `void`).
3.  Nikdy **nemá žádné parametry**. Každá třída má právě jeden destruktor.

```c++
class MojeTrida {
public:
    int* data;

    // Konstruktor: Alokuje paměť
    MojeTrida(int hodnota) {
        data = new int; // Alokace paměti na haldě
        *data = hodnota;
        cout << "Objekt vytvořen." << endl;
    }

    // Destruktor: Uvolňuje paměť
    ~MojeTrida() {
        delete data; // Uvolnění alokované paměti
        cout << "Objekt zničen." << endl;
    }
};
```

Praktickou ukázku celého životního cyklu objektu (volání konstruktoru a destruktoru) nejdete v souboru `main.cpp`.

---
## **Cvičení**

### **1. Produkt v e-shopu**
Vytvořte třídu `Produkt`.
1. **Konstruktor**: Přijme název a cenu, uloží je do atributů a vypíše "Vytvořen produkt: [nazev]".
2. **Destruktor**: Vypíše "Zničen produkt: [nazev]".
3. V `main` vytvořte produkt uvnitř bloku `{ ... }`. Sledujte, kdy se vypíše zpráva z destruktoru (mělo by to být při ukončení bloku).

### **2. Dynamický objekt**
Zkuste vytvořit produkt dynamicky pomocí `new`.
- Kdy se zavolá konstruktor?
- Kdy se zavolá destruktor? (Nápověda: Musíte zavolat `delete`).
