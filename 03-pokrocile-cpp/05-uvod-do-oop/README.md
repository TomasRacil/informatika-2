## 5. Úvod do OOP (Základy tříd)

Objektově orientované programování (OOP) je programovací paradigma, které nám umožňuje strukturovat kód do logických celků. Místo abychom přemýšleli jen v termínech funkcí a proměnných, přemýšlíme v termínech **objektů**, které mají své vlastnosti a schopnosti.

Základním stavebním kamenem OOP v C++ je **třída** (class).

### Třída (Class)

Třída slouží jako "šablona" nebo "plán" pro vytváření objektů. Definuje, jaké data (vlastnosti) a jaké funkce (schopnosti) budou objekty dané třídy mít.

Třída se definuje pomocí klíčového slova `class`.

```c++
class Person {
  // Deklarace atributů a metod
public:
  std::string jmeno;
  int vek;

  void pozdrav() {
      std::cout << "Ahoj, jsem " << jmeno << std::endl;
  }
};
```

### Atributy a Metody

Členy třídy dělíme na:

  * **Atributy (Attributes):** Jsou to proměnné, které ukládají data (stav) objektu. Například třída `Person` by mohla mít atributy `jmeno` a `vek`.
  * **Metody (Methods):** Jsou to funkce, které definují chování (schopnosti) objektu. Mohou pracovat s atributy, provádět výpočty atd. Například třída `Person` by mohla mít metodu `pozdrav()`.

### Objekt (Object)

Objekt je konkrétní **instance** třídy. Zatímco třída `Person` je jen šablona, `osoba1` je skutečný objekt vytvořený podle této šablony, s konkrétními hodnotami (např. `jmeno = "Jan"`).

```c++
// 'osoba1' je objekt (instance) třídy 'Person'
Person osoba1; 
osoba1.jmeno = "Jan";
osoba1.vek = 30;
osoba1.pozdrav(); // Volání metody na objektu
```

### Ukazatel `this`

Uvnitř **ne-statických** členských metod existuje speciální ukazatel `this`. Tento ukazatel obsahuje **adresu objektu**, pro který byla metoda zavolána. Používá se hlavně k rozlišení mezi atributem třídy a parametrem metody se stejným jménem, nebo když metoda potřebuje vrátit referenci či ukazatel na vlastní objekt.

```c++
class Obdelnik {
private:
    int delka;
    int sirka;
public:
    // Konstruktor používá 'this->' k rozlišení
    Obdelnik(int delka, int sirka) {
        this->delka = delka; // 'this->delka' je atribut třídy, 'delka' je parametr
        this->sirka = sirka;
    }
    // ... další metody ...
};
```

### Zapouzdření (Encapsulation)

Zapouzdření je jeden z klíčových principů OOP. Znamená to, že data (atributy) jsou skryta uvnitř třídy a přístup k nim je možný pouze prostřednictvím veřejných metod. To chrání data před nechtěnou modifikací.

K řízení přístupu slouží klíčová slova:

  * **`public`:** Členy (atributy i metody) jsou přístupné odkudkoliv, i vně třídy.
  * **`private`:** Členy jsou přístupné *pouze* z metod dané třídy. Z vnějšku (např. z `main`) k nim přistupovat nelze.
  * **`protected`:** Podobné jako `private`, ale členy jsou přístupné i z metod odvozených (dceřiných) tříd. (Probereme u dědičnosti).

Ve výchozím stavu jsou všichni členové třídy (`class`) **privátní**.

### Příklad

Praktickou ukázku definice třídy `Obdelnik`, vytvoření jejích instancí a volání metod najdete v souboru `main.cpp`.

---
## **Cvičení**

### **1. Třída Auto**
Vytvořte třídu `Auto`, která bude mít:
- Privátní atributy: `znacka` (string), `rokVyroby` (int).
- Public metody:
    - `nastavHodnoty(string z, int r)`
    - `vypisInfo()` - vypíše např. "Skoda, rok 2010"

### **2. Použití**
V `main` vytvořte instanci třídy `Auto`, nastavte ji hodnoty a zavolejte výpis. Zkuste přistoupit k atributu `znacka` přímo (`objekt.znacka`) a ověřte, že to díky `private` nejde.
