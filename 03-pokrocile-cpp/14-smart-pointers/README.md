# **14 - Chytré ukazatele (Smart Pointers)**

V předchozích kapitolách jsme viděli, jak silné, ale i nebezpečné, je manuální správa paměti pomocí `new` a `delete` (`03-pokrocile-cpp/02-dynamicka-alokace-pameti/`). Nejčastější chyby, jako jsou úniky paměti (zapomenutý `delete`) nebo dvojité uvolnění (double free), vedou k nestabilitě a pádům aplikací.

Moderní C++ (od C++11) přináší řešení ve formě **chytrých ukazatelů**.

## **Co je to chytrý ukazatel?**

Chytrý ukazatel je objekt (třída), který se chová jako běžný ukazatel (lze ho dereferencovat pomocí `*` a `->`), ale navíc **automaticky spravuje životní cyklus objektu, na který ukazuje**.

Využívá principu zvaného **RAII (Resource Acquisition Is Initialization)**. To znamená, že zdroj (v tomto případě alokovaná paměť) je "vlastněn" objektem (chytrým ukazatelem). Když je tento objekt-ukazatel zničen (například když opustí svůj *scope* – rozsah platnosti), jeho destruktor se automaticky postará o uvolnění zdroje (zavolá `delete` na spravovaný ukazatel).

**Hlavní výhoda: Už nikdy nemusíte ručně psát `delete`!**

Pro použití chytrých ukazatelů je nutné zahrnout hlavičku `<memory>`:

```cpp
#include <memory>
```

## **Typy chytrých ukazatelů**

C++ nabízí tři hlavní typy chytrých ukazatelů pro různé scénáře správy vlastnictví.

### **1. `std::unique_ptr` (Unikátní vlastnictví)**

Toto je nejběžnější a nejefektivnější chytrý ukazatel. Představuje **exkluzivní vlastnictví** objektu.

* **Pouze jeden `unique_ptr`** může v daný okamžik vlastnit daný objekt.  
* **Nelze jej kopírovat.** Nemůžete vytvořit kopii `unique_ptr`.  
* **Lze jej přesunout (move).** Vlastnictví objektu lze explicitně přesunout na jiný `unique_ptr` pomocí `std::move()`. Po přesunu je původní `unique_ptr` prázdný (`nullptr`).  
* Jakmile `unique_ptr` zanikne (opustí scope), objekt, který vlastnil, je automaticky smazán.

Jak ho vytvořit:  
Preferovaný způsob je použití `std::make_unique` (dostupné od C++14):  
```cpp
// Vytvoří objekt třídy 'MojeTrida' s parametry (10, "Ahoj") na haldě  
// a vrátí unique_ptr, který ho vlastní.  
std::unique_ptr<MojeTrida> mujUkazatel = std::make_unique<MojeTrida>(10, "Ahoj");
```
*Pro C++11 (pokud nepodporuje make_unique):* `std::unique_ptr<MojeTrida> mujUkazatel(new MojeTrida(10, "Ahoj"));`

**Jak ho použít:**

```cpp
mujUkazatel->nejakaMetoda();  
std::cout << mujUkazatel->nejakyAtribut << std::endl;
```

**Přesun vlastnictví:**

```cpp
// nelze: std::unique_ptr<MojeTrida> druhyUkazatel = mujUkazatel; // Chyba kompilace!

// lze:  
std::unique_ptr<MojeTrida> druhyUkazatel = std::move(mujUkazatel);  
// Nyní 'druhyUkazatel' vlastní objekt a 'mujUkazatel' je nullptr.
```

### **2. `std::shared_ptr` (Sdílené vlastnictví)**

Používá se, když potřebujete, aby **více ukazatelů sdílelo vlastnictví** jednoho objektu.

* Funguje na principu **počítání referencí** (reference counting).  
* Každý `shared_ptr` ukazuje na řídicí blok, který obsahuje počet odkazů na daný objekt.  
* Když je `shared_ptr` zkopírován, počítadlo se zvýší.  
* Když `shared_ptr` zanikne (opustí scope), počítadlo se sníží.  
* Objekt je smazán (`delete` je zavolán) až tehdy, když **počet referencí klesne na 0**.

Jak ho vytvořit:  
Preferovaný způsob je použití `std::make_shared`: 

```cpp
// Vytvoří objekt a řídicí blok v jedné alokaci (efektivnější)  
std::shared_ptr<MojeTrida> sdilenyUkazatel1 = std::make_shared<MojeTrida>("Test");
```

**Jak ho použít:**

```cpp
{  
    // Vytvoříme druhý sdílený ukazatel  
    std::shared_ptr<MojeTrida> sdilenyUkazatel2 = sdilenyUkazatel1;  
      
    // Nyní oba ukazují na stejný objekt.  
    // Počítadlo referencí je 2.  
    std::cout << sdilenyUkazatel1.use_count(); // Vypíše 2  
      
} // Zde zaniká 'sdilenyUkazatel2'. Počítadlo klesne na 1.  
  // Objekt stále existuje.

// Zde zaniká 'sdilenyUkazatel1'. Počítadlo klesne na 0.  
// Objekt je automaticky smazán.
```

### **3. `std::weak_ptr` (Slabý ukazatel)**

`weak_ptr` se používá ve spojení se `shared_ptr` k řešení problému **cyklických závislostí**.

* `weak_ptr` **nevlastní** objekt, na který ukazuje.  
* Nezvyšuje ani nesnižuje počet referencí.  
* Slouží jako pozorovatel. Umožňuje zkontrolovat, zda objekt *ještě existuje*.  
* Nelze ho přímo dereferencovat (`->` nebo `*`). Musí se nejprve "zamknout" (pomocí metody `lock()`), čímž se vytvoří dočasný `shared_ptr`. Pokud objekt mezitím zanikl, `lock()` vrátí prázdný `shared_ptr` (`nullptr`).

**Příklad problému (cyklická závislost):***  
Třída `Osoba` má `shared_ptr` na svého partnera.  
```cpp
class Osoba {  
public:  
    std::shared_ptr<Osoba> partner;  
    ~Osoba() { std::cout << "Destruktor Osoby" << std::endl; }  
};

std::shared_ptr<Osoba> alice = std::make_shared<Osoba>();  
std::shared_ptr<Osoba> bob = std::make_shared<Osoba>();

alice->partner = bob;   // Alice ukazuje na Boba (Bob má 2 reference)  
bob->partner = alice;   // Bob ukazuje na Alici (Alice má 2 reference)
```

Když `alice` a `bob` opustí scope, počet referencí pro každého klesne na 1 (protože se navzájem drží). Nikdy neklesne na 0, takže destruktory se nikdy nezavolají. **Vznikne memory leak.**

Řešení pomocí `weak_ptr`:  
Pokud partner bude `std::weak_ptr`, reference se v cyklu nenavýší a objekty se po opuštění scope správně smažou. 
```cpp 
class Osoba {  
public:  
    std::weak_ptr<Osoba> partner; // Změna!  
    ~Osoba() { std::cout << "Destruktor Osoby" << std::endl; }  
};
```
---
## **Cvičení**

### **1. Unique Pointer**
1. Vytvořte třídu `Test` s destruktorem, který vypíše "Znicen!".
2. V `main` vytvořte `std::unique_ptr<Test>`.
3. Ověřte, že se zpráva vypíše sama na konci programu.

### **2. Shared Pointer**
1. Vytvořte `std::shared_ptr<int>` s hodnotou 100.
2. Vvořte druhý `shared_ptr`, který bude kopií prvního.
3. Vypište počet referencí (`use_count()`).
4. Resetujte první ukazatel (`reset()`) a znovu vypište počet referencí u druhého.
