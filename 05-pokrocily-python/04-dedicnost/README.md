# **04 - Dědičnost (Inheritance)**

Dědičnost je klíčový mechanismus OOP, který nám umožňuje vytvářet nové třídy na základě těch existujících. Místo toho, abychom psali kód znovu, "zdedíme" vlastnosti a metody z jiné třídy a pouze je upravíme nebo rozšíříme.

Tím dodržujeme princip **DRY (Don't Repeat Yourself)**.

## **Terminologie**

* **Rodičovská třída (Parent Class / Superclass):** Třída, ze které se dědí (např. `Zvire`).  
* **Potomek (Child Class / Subclass):** Třída, která dědí (např. `Pes`).

## **Základní syntaxe**

```python
class Rodic:  
    pass

class Potomek(Rodic):  # Název rodiče v závorce  
    pass
```

## **Klíčové koncepty**

### **1. Přepisování metod (Method Overriding)**

Potomek dědí všechny metody rodiče. Pokud ale chceme, aby se potomek choval jinak, můžeme metodu **přepsat**. Stačí v potomkovi definovat metodu se **stejným názvem**.

* *Příklad:* Rodič `Zvire` má metodu `zvuk()`, která vypíše "...", ale `Pes` ji přepíše na "Haf".

### **2. Funkce `super()`**

Když metodu přepíšeme (např. `__init__`), původní kód rodiče se nespustí. Často ale nechceme funkčnost rodiče zahodit, ale jen ji **rozšířit**.

K tomu slouží funkce `super()`, která zavolá metodu rodiče.

* Typicky se používá v konstruktoru, abychom nemuseli znovu nastavovat atributy, které už řeší rodič.

```python
class Clovek:  
    def __init__(self, jmeno):  
        self.jmeno = jmeno

class Student(Clovek):  
    def __init__(self, jmeno, obor):  
        super().__init__(jmeno)  # Necháme rodiče nastavit jméno  
        self.obor = obor         # Sami si nastavíme obor
```

### **3. Hierarchie a `isinstance`**

V OOP vzniká stromová struktura (hierarchie). Je užitečné vědět, kam objekt patří.

* `isinstance(objekt, Trida)` vrátí `True`, pokud je objekt instancí dané třídy nebo jejího potomka.  
* Každý `Pes` je zároveň `Zvire`, ale ne každé `Zvire` je `Pes`.
---
## **Cvičení**

### **1. E-shop**
1. Vytvořte třídu `Produkt` (nazev, cena).
2. Vytvořte třídu `Elektronika`, která dědí z `Produkt` a přidává `zaruka` (v měsících).
3. Přepište konstruktor v `Elektronika` a použijte `super()`.
4. Vytvořte třídu `Obleceni`, která dědí z `Produkt` a přidává `velikost`.

### **2. Výpis**
Přidejte do `Produkt` metodu `info()`. Přepište ji v potomcích tak, aby vypisovala i specifické vlastnosti (záruku resp. velikost). Využijte `super().info()` pokud to dává smysl.
