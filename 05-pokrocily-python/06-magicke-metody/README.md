# **06 - Magické metody (Dunder methods)**

Magické metody (zkratka z *Double Underscore methods*) jsou speciální metody v Pythonu, které začínají a končí dvěma podtržítky. Umožňují nám definovat, jak se objekty chovají při použití standardních operací a funkcí.

Díky nim můžeme dosáhnout toho, že se naše vlastní objekty chovají stejně přirozeně jako vestavěné typy (`int`, `str`, `list`).

## **1. Reprezentace objektu (`__str__` a `__repr__`)**

Když vytiskneme objekt pomocí `print(objekt)`, Python standardně vypíše něco jako `<__main__.Trida object at 0x00...>`, což není příliš užitečné.

* **`__str__(self)`**: Volá se funkcí `print()` nebo `str()`. Měla by vrátit čitelný popis pro **uživatele**.  
* **`__repr__(self)`**: Volá se v interaktivní konzoli nebo funkcí `repr()`. Měla by vrátit detailní popis pro **vývojáře** (ideálně takový, aby šel zkopírovat a znovu spustit).

```python
class Kniha:  
    def __init__(self, nazev):  
        self.nazev = nazev

    def __str__(self):  
        return f"Kniha: {self.nazev}"

k = Kniha("Hobit")  
print(k)  # Vypíše: Kniha: Hobit
```

## **2. Přetěžování operátorů (Operator Overloading)**

Chceme-li, aby šly objekty sčítat, odčítat nebo porovnávat, musíme implementovat příslušné magické metody.

* **`__add__(self, other)`**: Implementuje sčítání `+`.  
* **`__sub__(self, other)`**: Implementuje odčítání `-`.  
* **`__mul__(self, other)`**: Implementuje násobení `*`.  
* **`__eq__(self, other)`**: Implementuje porovnání na rovnost `==`.  
* **`__lt__(self, other)`**: Implementuje menší než `<`.

### **Příklad sčítání vektorů:**

Pokud definujeme `__add__`, můžeme napsat `v3 = v1 + v2`. Python interně zavolá `v1.__add__(v2)`.

## **3. Další užitečné metody**

* **`__len__(self)`**: Volá se funkcí `len(objekt)`.  
* **`__getitem__(self, index)`**: Umožňuje přistupovat k objektu jako k seznamu pomocí indexu `objekt[index]`.  
* **`__call__(self)`**: Umožňuje zavolat objekt jako funkci `objekt()`.

Používání magických metod činí kód tzv. **Pythonic** – čistý, čitelný a intuitivní.
---
## **Cvičení**

### **1. Vektory**
Vytvořte třídu `Vektor`, která má atributy `x` a `y`.
1. Implementujte `__str__`, aby se vektor vypisoval jako `(x, y)`.
2. Implementujte `__add__`, aby bylo možné sečíst dva vektory (`v3 = v1 + v2`).
3. Vytvořte dva vektory, sečtěte je a výsledek vypište.

### **2. Porovnání**
Přidejte metodu `__eq__`, která vrátí `True`, pokud mají dva vektory stejné `x` i `y`. Otestujte to.
