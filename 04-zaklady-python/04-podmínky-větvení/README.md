# **04 - Podmínky a Větvení**

Doposud naše programy běžely lineárně – řádek po řádku, od shora dolů. Větvení nám umožňuje tento tok změnit: spustit určitou část kódu pouze tehdy, pokud je splněna nějaká podmínka.

## **1. Konstrukce `if`**

Základní stavební kámen rozhodování. Pokud je výraz za slovem `if` pravdivý (`True`), provede se odsazený blok kódu.

```python
cislo = 10

if cislo > 5:  
    print("Cislo je vetsi nez 5")  
    # Tento radek je soucasti podminky  
      
print("Tohle se vypise vzdy")
```

## **2. Konstrukce `else`**

Volitelná část, která se provede, pokud podmínka v `if` **není** splněna.

```python
vek = 15

if vek >= 18:  
    print("Vstup povolen.")  
else:  
    print("Vstup zakazan.")
```

## **3. Konstrukce `elif`**

Pokud máme více než dvě možnosti, použijeme `elif` (zkratka z "else if"). Python testuje podmínky postupně. Jakmile narazí na první pravdivou, provede její blok a zbytek přeskočí.

```python
body = 85

if body >= 90:  
    znamka = "A"  
elif body >= 75:  
    znamka = "B"  
elif body >= 50:  
    znamka = "C"  
else:  
    znamka = "F"
```

## **4. Vnořené podmínky (Nested Ifs)**

Podmínky můžeme vkládat do sebe. Je ale dobré to nepřehánět, aby byl kód čitelný.

```python
if uzivatel_prihlasen:  
    if ma_admin_prava:  
        print("Vitej v administraci")  
    else:  
        print("Vitej uzivateli")  
else:  
    print("Prosim, prihlaste se")
```

## **5. Ternární operátor (Jednořádkový if)**

Pro jednoduchá přiřazení hodnoty na základě podmínky existuje zkrácený zápis.

**Syntaxe:** `hodnota_pokud_pravda if podminka else hodnota_pokud_nepravda`

```python
stav = "dospely" if vek >= 18 else "nezletily"
```

## **6. Konstrukce `match-case` (Python 3.10+)**

Moderní alternativa k dlouhým řetězcům `if-elif-else`, pokud porovnáváme jednu proměnnou s více konkrétními hodnotami (podobné `switch` v C++ nebo Javě).

```python
status_kod = 404

match status_kod:  
    case 200:  
        print("OK")  
    case 404:  
        print("Nenalezeno")  
    case 500:  
        print("Chyba serveru")  
    case _:  
        print("Neznamy stav") # _ funguje jako default (else)  
```
---
## **Cvičení**

### **1. Heslo**
Načtěte od uživatele heslo.
- Pokud je heslo "tajne123", vypište "Přístup povolen".
- Jinak vypište "Chybné heslo".

### **2. Porovnání čísel**
Načtěte číslo.
- Pokud je větší než 0: vypište "Kladné".
- Pokud je menší než 0: vypište "Záporné".
- Jinak vypište "Nula".

### **3. Dny v týdnu (Match-case)**
Načtěte číslo dne (1-7). Pomocí `match-case` vypište název dne (Pondělí, Úterý...). Pro jiná čísla vypište "Neplatný den".
