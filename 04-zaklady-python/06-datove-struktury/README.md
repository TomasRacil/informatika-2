# **Datové struktury v Pythonu**

Datové struktury jsou kontejnery, které organizují a ukládají data. V Pythonu existují čtyři základní vestavěné typy kolekcí, z nichž každá má specifické vlastnosti a účel použití. Výběr správné struktury je klíčový pro efektivitu programu.

## **Přehled vlastností**

| Název | Typ v Pythonu | Závorky | Seřazené? | Měnitelné (Mutable)? | Unikátní prvky? |
| :---- | :---- | :---- | :---- | :---- | :---- |
| **Seznam** | `list` | `[]` | Ano | **Ano** | Ne |
| **N-tice** | `tuple` | `()` | Ano | **Ne** (Immutable) | Ne |
| **Množina** | `set` | `{}` | Ne* | Ano | **Ano** |
| **Slovník** | `dict` | `{k:v}` | Ano** | Ano | Ano (klíče) |

*\* Množiny nejsou indexované.  
*\*\* Od Pythonu 3.7 jsou slovníky seřazené podle pořadí vložení.*

## **1. Seznam (List)**

Seznam je nejpoužívanější datová struktura. Je to uspořádaná posloupnost prvků, kterou můžeme libovolně měnit.

### **Vytvoření a přístup**

```python
# Prázdný seznam  
muj_seznam = []

# Seznam s daty (mohou být různé typy)  
ovoce = ["jablko", "hruška", "banán", 10, True]

# Přístup pomocí indexu (začínáme od 0)  
print(ovoce[0])  # Vypíše: jablko  
print(ovoce[-1]) # Vypíše: True (poslední prvek)
```

### **Základní metody seznamu**

* `.append(hodnota)` – přidá prvek na konec.  
* `.insert(index, hodnota)` – vloží prvek na konkrétní pozici.  
* `.remove(hodnota)` – odstraní první výskyt hodnoty.  
* `.pop(index)` – odstraní a vrátí prvek na daném indexu (bez indexu odstraní poslední).  
* `.sort()` – seřadí prvky (musí být porovnatelné).

### **List Comprehension (Generování seznamů)**

Velmi silný nástroj Pythonu pro tvorbu seznamů na jednom řádku. Nahrazuje klasický cyklus `for` při plnění seznamu.

**Syntaxe**: `[výraz for polozka in kolekce if podminka]`

```python
# Klasicky:
cisla = []
for x in range(5):
    cisla.append(x * 2)

# List Comprehension:
cisla = [x * 2 for x in range(5)]
```

## **2. N-tice (Tuple)**

N-tice je velmi podobná seznamu, ale je **neměnná** (immutable). Jakmile ji vytvoříte, nemůžete změnit její obsah (přidávat, mazat ani měnit prvky).

### **Kdy použít Tuple?**

* Data, která se nemají měnit (např. dny v týdnu, souřadnice GPS, barvy RGB).  
* Je rychlejší a zabírá méně paměti než seznam.  
* Může sloužit jako klíč ve slovníku (seznam nemůže).

```python
souradnice = (50.0755, 14.4378)  
# souradnice[0] = 40.123  # TOTO VYVOLÁ CHYBU (TypeError)
```

**Tip:** Tuple s jedním prvkem musí mít čárku: `jednoprvkovy = (1,)`.

## **3. Množina (Set)**

Množina je kolekce unikátních prvků. Neuchovává pořadí a neumožňuje přístup přes indexy.

### **Hlavní využití**

1. **Odstranění duplicit** ze seznamu.  
2. **Matematické operace** (sjednocení, průnik, rozdíl).  
3. Rychlé zjišťování, zda prvek v kolekci existuje.

```python
cisla = {1, 2, 3, 3, 3, 4}  
print(cisla)  # Vypíše: {1, 2, 3, 4} -> duplicity zmizely
```

## **4. Slovník (Dictionary)**

Slovník slouží k ukládání dat ve formátu **klíč : hodnota**. Hodnoty vyhledáváme podle klíče, nikoliv podle číselného indexu.

### **Práce se slovníkem**

```python
student = {  
    "jmeno": "Petr",  
    "vek": 17,  
    "znamky": [1, 2, 1]  
}

# Přístup k hodnotě  
print(student["jmeno"])

# Přidání nebo změna hodnoty  
student["vek"] = 18      # Změna  
student["obor"] = "IT"   # Nový klíč

# Bezpečné získání hodnoty (pokud klíč neexistuje, vrátí None nebo default)  
print(student.get("adresa", "Neznámá adresa"))
```

### **Iterace přes slovník**

* `student.keys()` – vrátí klíče.  
* `student.values()` – vrátí hodnoty.  
* `student.items()` – vrátí páry (klíč, hodnota).
---
## **Cvičení**

### **1. Nákupní seznam (List)**
Vytvořte seznam `nakup`, který obsahuje: "chleba", "máslo", "jablka".
1. Přidejte na konec "mléko".
2. Odeberte "máslo".
3. Vypište, kolik položek je v seznamu (`len()`).

### **2. Mocniny (List Comprehension)**
Pomocí list comprehension vytvořte seznam druhých mocnin čísel od 0 do 9. Výsledek by měl být `[0, 1, 4, 9, ...]`.

### **3. Telefonní seznam (Dict)**
Vytvořte slovník, kde klíčem je jméno a hodnotou telefonní číslo.
1. Vypište číslo pro "Petra".
2. Přidejte nový kontakt "Jana".
3. Vypište všechny kontakty (klíče).

### **4. Unikátní čísla (Set)**
Máte seznam `[1, 2, 2, 3, 1, 4, 5, 5]`.
Převeďte ho na množinu a vypište výsledek, abyste se zbavili duplicit.
