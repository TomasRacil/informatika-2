# **05 - Abstraktní třídy a Polymorfismus**

V této lekci se naučíme, jak definovat pevná pravidla pro naše třídy a jak využít jejich společných vlastností.

## **1. Abstraktní třídy (Abstract Base Classes)**

Představte si, že programujete grafický editor. Máte třídy `Kruh`, `Ctverec`, `Trojuhelnik`. Všechno jsou to "Tvary".  
Dává smysl vytvořit rodičovskou třídu `Tvar`, aby měly společné vlastnosti.  
Ale má smysl vytvořit instanci třídy `Tvar`? Jak by vypadala? Jaký by měla obsah?  
Nedává to smysl. `Tvar` je jen abstraktní pojem.  
V Pythonu k tomu používáme modul `abc` (Abstract Base Classes).

### **Jak to funguje?**

1. Třída musí dědit z `ABC` (Abstract Base Class).  
2. Metody, které **musí** potomci mít, označíme jako `@abstractmethod`.

```python
from abc import ABC, abstractmethod

class Tvar(ABC):  
    @abstractmethod  
    def spocti_obsah(self):  
        pass
```

Pokud se pokusíte vytvořit instanci `Tvar()`, Python vyhodí chybu. Pokud vytvoříte potomka (např. `Kruh`), který metodu `spocti_obsah` nenaprogramuje, Python vám také nedovolí vytvořit instanci. Tím si vynucujeme tzv. **interface (rozhraní)**.

## **2. Polymorfismus (Mnohotvarost)**

Polymorfismus je vlastnost, která nám umožňuje přistupovat k objektům různých tříd stejným způsobem, pokud sdílejí společného předka (nebo rozhraní).

Díky tomu, že `Kruh` i `Ctverec` dědí z `Tvar` a oba **museli** implementovat metodu spocti_obsah, můžeme napsat univerzální funkci:

```
def vytiskni_info(jakykoliv_tvar):  
    print(f"Obsah je: {jakykoliv_tvar.spocti_obsah()}")
```

Této funkci je jedno, jestli jí předáte kruh nebo čtverec. Ví, že je to `Tvar`, a proto to má metodu `spocti_obsah()`. To je polymorfismus v praxi.
---
## **Cvičení**

### **1. Zvířecí farma**
1. Vytvořte abstraktní třídu `Zvire` s abstraktní metodou `vydej_zvuk`.
2. Vytvořte třídy `Pes` a `Kocka`. Implementujte `vydej_zvuk` ("Haf", "Mnau").
3. Vytvořte funkci `prehraj_zvuk(zvire)`, která přijme jakékoliv zvíře a zavolá jeho metodu.
4. Ověřte, že nelze vytvořit instanci třídy `Zvire`.
