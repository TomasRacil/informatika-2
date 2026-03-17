## 7. Dědičnost (Inheritance)

Dědičnost je klíčový mechanismus objektově orientovaného programování, který umožňuje jedné třídě (dceřiné) přebírat vlastnosti (atributy) a chování (metody) z jiné třídy (rodičovské).

Hlavní výhodou je **znovupoužitelnost kódu** (princip DRY - Don't Repeat Yourself). Můžeme definovat obecnou ("rodičovskou") třídu a poté vytvářet specializované ("dceřiné") třídy, které tuto obecnou funkčnost rozšiřují.

* **Základní (Base) třída:** Třída, ze které se dědí. Někdy se jí říká "rodičovská" (parent) nebo "nadřazená" (superclass).
* **Odvozená (Derived) třída:** Třída, která dědí. Někdy se jí říká "dceřiná" (child) nebo "podřazená" (subclass).

Odvozená třída má **"is a"** (je) vztah k základní třídě. Například `Student` **je** `Osoba`. `Auto` **je** `Vozidlo`.

### Syntaxe dědičnosti

V C++ se dědičnost definuje připsáním dvojtečky, typu dědičnosti (nejčastěji `public`) a názvu základní třídy do definice odvozené třídy.

```c++
// Základní třída
class Person {
    // ...
};

// Odvozená třída 'Student' dědí z 'Person'
class Student : public Person {
    // ...
};
```

### Modifikátory přístupu a dědičnost

Modifikátory přístupu (`public`, `private`, `protected`) hrají v dědičnosti klíčovou roli.

  * **`public`:** Členy jsou přístupné odkudkoliv, včetně odvozených tříd.
  * **`private`:** Členy jsou přístupné **pouze** v rámci třídy, která je definovala. Odvozené třídy k nim **nemají** přímý přístup.
  * **`protected`:** Toto je kompromis. Členy jsou "privátní" pro vnější svět (např. pro `main`), ale jsou **plně přístupné** pro odvozené třídy.

| Přístup v `Person` | Přístup z `main()` | Přístup ze `Student` |
| :--- | :--- | :--- |
| `public` jmeno; | `person.jmeno` (OK) | `this->jmeno` (OK) |
| `protected` vek; | `person.vek` (CHYBA) | `this->vek` (OK) |
| `private` rodneCislo; | `person.rodneCislo` (CHYBA)| `this->rodneCislo` (CHYBA) |

### Konstruktory a Destruktory v Dědičnosti

Toto je velmi důležitá součást dědičnosti.

#### Pořadí volání konstruktorů

Při vytváření objektu odvozené třídy (`Student`) se **vždy nejprve volá konstruktor základní třídy (`Person`)** a teprve poté konstruktor odvozené třídy (`Student`).

Pokud má základní třída konstruktor s parametry, musíme ho z odvozené třídy explicitně zavolat pomocí **inicializačního seznamu**.

```c++
class Person {
protected:
    string jmeno;
public:
    Person(string jmeno) { // Konstruktor základní třídy
        this->jmeno = jmeno;
    }
};

class Student : public Person {
private:
    string skola;
public:
    // 'Person(jmeno)' je volání konstruktoru základní třídy
    Student(string jmeno, string skola) : Person(jmeno) {
        this->skola = skola;
    }
};
```

#### Pořadí volání destruktorů

Destruktory se volají v **přesně opačném pořadí** než konstruktory.

1.  Nejprve se zavolá destruktor odvozené třídy (`~Student()`).
2.  Poté se automaticky zavolá destruktor základní třídy (`~Person()`).

To zajišťuje, že objekt je "uklízen" postupně od nejspecifičtější části po nejobecnější.

### Volání metod rodiče

Odvozená třída může "přepsat" (override - *přesněji řečeno redefinovat, pokud metoda není virtuální*) metodu rodiče tím, že definuje vlastní metodu se stejným názvem a signaturou. Pokud z této nové metody potřebujeme zavolat původní implementaci z rodičovské třídy, použijeme operátor rozsahu (`::`). To nám umožňuje rozšířit původní chování, nikoli ho zcela nahradit.

```c++
void Student::pozdrav() {
    // Zavolá metodu pozdrav() definovanou v Person
    Person::pozdrav(); 
    
    // Přidá vlastní chování
    cout << " a studuji na " << this->skola << "." << endl;
}
```

Praktickou ukázku všech těchto konceptů najdeš v souboru `main.cpp`.


---
## **Cvičení**

### **1. Zvířata**
1. Vytvořte základní třídu `Zivocich` s `protected` atributem `jmeno`.
2. Vytvořte konstruktor `Zivocich(string j)`.
3. Vytvořte odvozenou třídu `Pes`, která přidá atribut `rasa`.
4. Vytvořte konstruktor `Pes(string j, string r)`, který správně zavolá konstruktor předka.
5. Vytvořte metodu `stekej()`, která vypíše: "[jmeno] ([rasa]): Haf!".

### **2. Ověření přístupu**
Zkuste ve třídě `Zivocich` změnit `protected` na `private`. Půjde kód zkompilovat? Proč?
