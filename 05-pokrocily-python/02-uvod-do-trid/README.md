# **02 - Úvod do tříd a objektů (OOP)**

Doposud jsme programovali převážně **procedurálně** nebo **funkcionálně**. To znamená, že jsme měli data (proměnné, seznamy, slovníky) a funkce, které s těmito daty pracovaly. Data a funkce byly oddělené.

**Objektově orientované programování (OOP)** tento přístup mění. Spojuje data a funkce, které s nimi pracují, do jednoho celku – **Objektu**.

## **Proč používat třídy?**

Představte si, že programujete hru s auty. Bez tříd byste museli mít pro každé auto spoustu proměnných:

```python
# Procedurální přístup (nepřehledné pro více aut)  
auto1_barva = "červená"  
auto1_rychlost = 0  
auto1_nastartovano = False

auto2_barva = "modrá"  
auto2_rychlost = 50  
auto2_nastartovano = True

def zrychli(aktualni_rychlost):  
    return aktualni_rychlost + 10
```

Jakmile budete mít aut 50, ztratíte se v tom. OOP nám umožňuje vytvořit **Třídu (šablonu)** `Auto` a podle ní vyrábět jednotlivé **Objekty**. Každý objekt si svá data drží u sebe.

## **Klíčové pojmy**

### **1. Třída (Class) = Šablona**

Třída je předpis, jak má objekt vypadat a co má umět. Je to jako "razítko" nebo "výkres v továrně". Sama o sobě nic nedělá, jen definuje strukturu.

* Píšeme je s velkým písmenem (PascalCase), např. `MojeTrida`.

### **2. Objekt (Instance) = Konkrétní výrobek**

Objekt je to, co vznikne, když třídu "zavoláme". Podle jedné třídy můžeme vytvořit tisíce objektů. Každý je unikátní.

### **3. Atributy (Attributes) = Vlastnosti**

Jsou to proměnné uvnitř objektu. Popisují jeho **stav**.

* Např.: `barva`, `rychlost`, `počet_kol`.

### **4. Metody (Methods) = Schopnosti**

Jsou to funkce uvnitř třídy. Popisují **chování** objektu.

* Např.: `zatrub()`, `nastartuj()`, `zastav()`.

## **Syntaxe v Pythonu**

```python
class Pes:  
    # Speciální metoda (konstruktor)  
    def __init__(self, jmeno, rasa):  
        self.jmeno = jmeno  # Atribut instance  
        self.rasa = rasa    # Atribut instance

    # Běžná metoda  
    def stekej(self):  
        print(f"{self.jmeno} dělá HAF!")
```

### **Kouzelné slovíčko `self`**

Všimněte si, že každá metoda ve třídě má jako první parametr `self`.

* `self` odkazuje na **právě ten konkrétní objekt**, se kterým pracujeme.  
* Když voláme `alik.stekej()`, Python to na pozadí převede na `Pes.stekej(alik)`. Objekt `alik` se vloží do parametru `self`.  
* Díky `self.jmeno` program ví, že má vypsat jméno *tohoto* psa, a ne nějakého jiného.

### **Konstruktor `__init__`**

Metoda `__init__` je tzv. magická metoda (dunder method).

* Spustí se **automaticky** v okamžiku, kdy vytváříte nový objekt: `pes = Pes("Alík", "Oříšek")`.  
* Slouží k nastavení startovních hodnot atributů.

## **Shrnutí**

* **Třída** definuje strukturu.  
* **Objekt** je konkrétní instance třídy.  
* **`__init__`** nastavuje startovní data.  
* **`self`** umožňuje objektu přistupovat ke svým vlastním datům.
---
## **Cvičení**

### **1. Kniha**
Vytvořte třídu `Kniha`.
1. V konstruktoru (`__init__`) nastavte atributy `nazev`, `autor` a `pocet_stran`.
2. Přidejte metodu `info(self)`, která vypíše: "Kniha [nazev] od [autor] má [pocet] stran."

### **2. Knihovna**
Vytvořte dvě instance třídy `Kniha` (např. Harry Potter a Pán Prstenů). Zavolejte na obou metodu `info()`.
