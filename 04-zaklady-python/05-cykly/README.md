# **05 - Cykly (Loops)**

Cykly umožňují opakovat blok kódu vícekrát. V programování se používají ke dvěma hlavním účelům:

1. Opakování kódu stanovený počet krát (např. "udělej to 10x").  
2. Opakování kódu, dokud platí podmínka (např. "čti data, dokud není konec souboru").

## **1. Cyklus `for`**

V Pythonu je cyklus `for` navržen primárně pro procházení sekvencí (čísel, znaků v textu, položek v seznamu).

### **Funkce `range()`**

Pro generování posloupnosti čísel používáme funkci `range()`. Má tři parametry: `range(start, stop, krok)`.

| Zápis | Význam | Vygenerovaná čísla |
| :---- | :---- | :---- |
| `range(5)` | Čísla od 0 do `stop-1`. | 0, 1, 2, 3, 4 |
| `range(1, 5)` | Čísla od `start` do `stop-1`. | 1, 2, 3, 4 |
| `range(0, 10, 2)` | Čísla od `start` s krokem `step`. | 0, 2, 4, 6, 8 |
| `range(5, 0, -1)` | Odpočítávání (záporný krok). | 5, 4, 3, 2, 1 |

```python
# Vypíše čísla 0 až 4  
for i in range(5):  
    print(i)
```

### **Iterace přes řetězec**

Řetězec je v Pythonu sekvence znaků, takže ho můžeme procházet znak po znaku.

```python
for znak in "Python":  
    print(znak)
```

## **2. Cyklus `while`**

Tento cyklus opakuje kód tak dlouho, dokud je podmínka pravdivá (True). Používá se v situacích, kdy předem nevíme, kolikrát se cyklus provede (např. čekání na vstup uživatele).

```python
heslo = ""  
while heslo != "tajne123":  
    heslo = input("Zadej heslo: ")
```

**Pozor na nekonečné cykly:** Pokud podmínka nikdy nepřestane platit (např. `while True:`), program se zasekne a musíte ho násilně ukončit (v terminálu zkratkou `Ctrl+C`).

## **3. Řízení průběhu cyklu**

Chování cyklu můžeme ovlivnit speciálními příkazy:

* **`break`**: Okamžitě ukončí celý cyklus. Program pokračuje prvním příkazem za cyklem.  
* **`continue`**: Okamžitě ukončí aktuální iteraci (kolo) a skočí zpět na začátek cyklu k dalšímu kroku.  
* **`pass`**: Nedělá nic. Používá se jako "prázdná instrukce" tam, kde syntaxe vyžaduje kód (např. v prázdném cyklu při návrhu programu).

## **4. Větev `else` u cyklů**

Python má unikátní vlastnost – k cyklům `for` i `while` lze přidat větev `else`.

* Kód v bloku `else` se provede **pouze tehdy**, pokud cyklus doběhl přirozeně až do konce.  
* Pokud byl cyklus ukončen příkazem `break`, blok `else` se **neprovede**.

To se hodí například při vyhledávání:

```python
for cislo in range(5):  
    if cislo == 10:  
        print("Nalezeno")  
        break  
else:  
    print("Nenalezeno (cyklus prosel cely)")
```

## **5. Vnořené cykly (Nested Loops)**

Cykly můžeme vkládat do sebe. Vnitřní cyklus proběhne celý pro každou jednu iteraci vnějšího cyklu. Používá se například pro práci s tabulkami (řádky a sloupce).

```python
for radek in range(3):  
    for sloupec in range(3):  
        print(f"[{radek},{sloupec}]", end=" ")  
    print() # Odradkovani 
```
---
## **Cvičení**

### **1. Počitadlo**
Pomocí cyklu `for` vypište čísla od 1 do 10 (včetně).

### **2. Hláskování**
Načtěte od uživatele slovo. Pomocí cyklu `for` vypište každé písmeno na samostatný řádek.

### **3. Neodbytný program**
Pomocí cyklu `while` se ptejte uživatele "Chceš pokračovat?". Cyklus ukončete, až když uživatel napíše "ne".

### **4. Sudá čísla**
Vypište všechna sudá čísla mezi 0 a 20. Zkuste to vyřešit pomocí parametru `step` ve funkci `range`.
