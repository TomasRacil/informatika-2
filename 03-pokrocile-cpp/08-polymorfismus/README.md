## 8. Polymorfismus

Polymorfismus (z řečtiny "mnoho tvarů") je jeden z klíčových pilířů OOP. Je to schopnost zacházet s objekty různých dceřiných tříd jednotným způsobem, a to prostřednictvím ukazatele (nebo reference) na jejich společnou základní třídu.

Polymorfismus nám umožňuje psát flexibilnější a obecnější kód. Můžeme například vytvořit pole ukazatelů na třídu `Zvire` a do něj uložit instance tříd `Pes`, `Kocka` a `Ptak`.

### Virtuální Metody (Virtual Functions)

Klíčem k polymorfismu v C++ je klíčové slovo `virtual`.

Když v základní třídě označíme metodu jako `virtual`, říkáme tím kompilátoru: "Při volání této metody přes ukazatel se nerozhoduj podle typu ukazatele (v době kompilace), ale podívej se, na jaký typ objektu ukazatel *skutečně* ukazuje (v době běhu), a zavolej jeho verzi metody."

Tento proces se nazývá **dynamická vazba (dynamic dispatch)** nebo **pozdní vazba (late binding)**, protože rozhodnutí, která konkrétní metoda se zavolá, se děje až za běhu programu na základě skutečného typu objektu. Opakem je **statická vazba (static binding)**, která se používá u ne-virtuálních metod, kde kompilátor rozhodne o volané metodě již při překladu na základě typu ukazatele nebo reference.

```c++
class Zvire {
public:
    // Tato metoda je označena jako virtuální
    virtual void udelejZvuk() {
        cout << "Neznamy zvuk zvirete" << endl;
    }
};

class Pes : public Zvire {
public:
    // Tato metoda "přepisuje" (overrides) virtuální metodu rodiče
    void udelejZvuk() override { // 'override' je dobrá praxe, kontroluje překlepy
        cout << "Haf!" << endl;
    }
};

class Kocka : public Zvire {
public:
    // Tato metoda také přepisuje metodu rodiče
    void udelejZvuk() override {
        cout << "Mnau!" << endl;
    }
};

int main() {
    Zvire* z1 = new Pes();
    Zvire* z2 = new Kocka();

    z1->udelejZvuk(); // Vypíše "Haf!"
    z2->udelejZvuk(); // Vypíše "Mnau!"
}
```

Kdyby metoda `udelejZvuk()` nebyla `virtual`, obě volání by vypsala "Neznamy zvuk zvirete", protože kompilátor by se řídil pouze typem ukazatele (`Zvire*`).

> Klíčové slovo override není povinné, ale je velmi doporučené. Pomáhá předejít chybám – kompilátor zkontroluje, zda v rodičovské třídě skutečně existuje virtuální metoda se stejnou signaturou (názvem a parametry), kterou chceme přepsat. Pokud ne (např. kvůli překlepu v názvu), kompilátor zahlásí chybu.

### Abstraktní Třídy a Čistě Virtuální Metody

Někdy chceme vytvořit základní třídu, která je tak obecná, že nedává smysl z ní vytvářet instance (objekty). Například, co je to "obecné zvíře"?

Takovou třídu můžeme označit jako **abstraktní**. Abstraktní třída je třída, která má alespoň jednu **čistě virtuální metodu (pure virtual function)**.

Čistě virtuální metoda je metoda, která nemá žádnou implementaci a je označena pomocí `= 0;`.

```c++
class Tvar { // Toto je nyní abstraktní třída
public:
    // Čistě virtuální metoda
    virtual double obsah() = 0; 
};
```

**Důsledky:**

1.  **Nelze vytvořit instanci** abstraktní třídy (`Tvar t;` by způsobilo chybu kompilace).
2.  Slouží jako **"kontrakt"** nebo **"rozhraní" (interface)**. Každá dceřiná třída, která z ní dědí, *musí* implementovat (přepsat) všechny její čistě virtuální metody, jinak se sama stane abstraktní.

### Virtuální Destruktor

Toto je velmi důležitý a častý zdroj chyb.

**Problém:** Pokud máte ukazatel na základní třídu (`Zvire* z = new Pes();`) a později zavoláte `delete z;`, C++ standardně zavolá *pouze* destruktor základní třídy (`~Zvire()`). Destruktor odvozené třídy (`~Pes()`) se nezavolá. Pokud si třída `Pes` alokovala nějakou paměť, dojde k úniku paměti (memory leak).

**Řešení:** Vždy, když máte v plánu používat třídu polymorfně (tj. mít virtuální metody), **deklarujte její destruktor jako virtuální**.

```c++
class Zvire {
public:
    // ...
    virtual ~Zvire() {
        cout << "Destruktor Zvirete" << endl;
    }
};

class Pes : public Zvire {
public:
    // ...
    ~Pes() {
        cout << "Destruktor Psa" << endl;
    }
};

int main() {
    Zvire* z = new Pes();
    delete z; 
    // Díky 'virtual ~Zvire()' se vypíše:
    // 1. "Destruktor Psa"
    // 2. "Destruktor Zvirete"
}
```

Ukázku všech těchto konceptů v praxi najdete v souboru `main.cpp`.

>Poznámka ke správě paměti: V příkladu používáme new pro vytvoření objektů na haldě a následně delete pro jejich uvolnění. Při práci s polymorfismem a ukazateli na základní třídu je nutné mít virtuální destruktor, aby se zajistilo správné uvolnění zdrojů dceřiné třídy. V moderním C++ se pro zjednodušení správy paměti často používají chytré ukazatele (např. std::unique_ptr, std::shared_ptr), které uvolnění paměti řeší automaticky. Těmi se budeme zabývat později.
---
## **Cvičení**

### **1. Geometrické útvary**
1. Vytvořte abstraktní třídu `Utvar` s čistě virtuální metodou `double obsah()`.
2. Vytvořte třídy `Ctverec` (strana a) a `Kruh` (poloměr r), které dědí z `Utvar`. Implememtujte výpočet obsahu.
3. V `main` vytvořte pole ukazatelů na `Utvar` a vložte do něj instance čtverce i kruhu.
4. Cyklem projděte pole a u každého prvku vypište jeho obsah.

### **2. Virtuální destruktor**
Do třídy `Utvar` přidejte virtuální destruktor, který vypíše hlášku. Ověřte, že při smazání objektů přes ukazatel na předka se zavolá i správný destruktor potomka.
