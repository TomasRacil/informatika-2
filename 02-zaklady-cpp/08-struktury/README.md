# 08 - Struktury (struct)

Dosud jsme pracovali se základními datovými typy (jako `int`, `double`, `char`) nebo s kolekcemi prvků stejného typu (pole, `std::vector`). Co když ale potřebujeme uchovávat pohromadě data různých typů, která logicky patří k sobě?

Například student má jméno (`string`), věk (`int`) a průměr (`double`). Místo vytváření tří samostatných proměnných (nebo tří polí, pokud máme studentů více) můžeme vytvořit vlastní datový typ: **strukturu**.

## Co je struktura?

Struktura (anglicky **struct**) je uživatelsky definovaný datový typ, který sdružuje více proměnných (nazývaných **členy** nebo **atributy**) pod jedním názvem.

### Definice struktury

Struktura se definuje pomocí klíčového slova `struct`, následovaného názvem struktury a tělem ve složených závorkách. Definice musí být ukončena středníkem.

```cpp
struct Student {
    std::string jmeno;
    std::string prijmeni;
    int vek;
    double prumer;
}; // <-- Nezapomeňte na středník!
```

Tímto jsme vytvořili **nový datový typ** s názvem `Student`. Zatím jsme nevytvořili žádnou proměnnou tohoto typu.

## Vytvoření a použití proměnné (instance)

Jakmile máme typ definovaný, můžeme vytvářet proměnné (instance) tohoto typu, stejně jako bychom vytvářeli `int` nebo `double`.

```cpp
// Vytvoření instance studenta
Student s1;
```

### Přístup ke členům

K jednotlivým členům struktury přistupujeme pomocí **tečkové notace** (`.`).

```cpp
// Přiřazení hodnot členům
s1.jmeno = "Jan";
s1.prijmeni = "Novak";
s1.vek = 20;
s1.prumer = 1.5;

// Čtení hodnot
std::cout << "Jméno studenta: " << s1.jmeno << " " << s1.prijmeni << std::endl;
std::cout << "Věk: " << s1.vek << std::endl;
```

### Inicializace při vytvoření

Strukturu můžeme inicializovat rovnou při jejím vytvoření pomocí složených závorek (podobně jako pole).

```cpp
// Pořadí musí odpovídat definici (jmeno, prijmeni, vek, prumer)
Student s2 = {"Petr", "Svoboda", 22, 1.2};

// Nebo pomocí C++20 "designated initializers" (přehlednější)
Student s3 = {
    .jmeno = "Eva",
    .prijmeni = "Dvorakova",
    .vek = 21,
    .prumer = 1.8
};
```

## Struktury a funkce

Struktury můžeme předávat funkcím jako jakýkoli jiný datový typ.

### Předání hodnotou (Pass-by-Value)

Funkce obdrží **kopii** celé struktury. Jakékoli změny provedené uvnitř funkce se **nepromítnou** do původní proměnné.

```cpp
void vypisStudenta(Student s) {
    std::cout << s.jmeno << " " << s.prijmeni << " (Věk: " << s.vek << ")" << std::endl;
    s.vek = 99; // Tato změna ovlivní pouze lokální kopii 's'
}

Student s1 = {"Jan", "Novak", 20, 1.5};
vypisStudenta(s1); // Vypíše "Jan Novak (Věk: 20)"
std::cout << s1.vek; // Stále vypíše 20
```

### Předání referencí (Pass-by-Reference)

Pokud chceme, aby funkce mohla **modifikovat** původní strukturu, nebo pokud se chceme **vyhnout zbytečnému kopírování** (což je u velkých struktur důležité z hlediska výkonu), předáme ji referencí (`&`).

```cpp
// Přidáním const zajistíme efektivitu (bez kopírování)
// a zároveň bezpečnost (funkce nemůže data měnit)
void vypisStudentaEfektivne(const Student& s) {
    std::cout << s.jmeno << " " << s.prijmeni << " (Věk: " << s.vek << ")" << std::endl;
    // s.vek = 99; // TOTO BY NYNÍ ZPŮSOBILO CHYBU PŘI PŘEKLADU DÍKY 'const'
}

// Bez const můžeme strukturu uvnitř funkce měnit
void oslavNarozeniny(Student& s) {
    s.vek++; // Tato změna se promítne do originálu
}

Student s1 = {"Jan", "Novak", 20, 1.5};
oslavNarozeniny(s1);
vypisStudentaEfektivne(s1); // Vypíše "Jan Novak (Věk: 21)"
```

## Proč jsou struktury důležité?

Struktury jsou základem pro organizaci dat. Jsou klíčové pro:

1.  **Seskupování souvisejících dat** do jednoho logického celku.
2.  **Vytváření složitějších datových struktur.** Jak uvidíme v další kapitole, spojové seznamy, stromy a další struktury jsou postaveny právě na strukturách (nebo třídách), které obsahují data a **ukazatele** na další prvky stejného typu.


```cpp
// Náhled do další kapitoly (spojové seznamy):
struct Uzel {
    int data;       // Data, která uzel drží
    Uzel* dalsi;    // Ukazatel na další uzel ve struktuře
};
```

---
## **Cvičení**

### **1. Knihovna**
Definujte strukturu `Kniha`, která bude mít:
- Název (string)
- Autora (string)
- Rok vydání (int)
- Cenu (double)

### **2. Evidence knih**
Vytvořte pole typu `Kniha` pro 3 knihy. Naplňte ho daty (natvrdo v kódu nebo od uživatele).

### **3. Výpis a hledání**
1. Napište funkci `vypisKnihu(const Kniha& k)`, která vypíše informace o jedné knize.
2. Pomocí cyklu vypište všechny knihy v poli.
3. Najděte a vypište nejdražší knihu v poli.
