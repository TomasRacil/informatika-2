# **14 - Generátory a Iterátory**

V Pythonu je cyklus `for` velmi mocný. Můžeme iterovat přes seznamy, n-tice, slovníky, řetězce nebo soubory. Všechny tyto objekty jsou tzv. **Iterable**.

Ale co když chceme projít sekvenci o miliardě čísel? Kdybychom vytvořili seznam (`list`), zaplníme celou paměť RAM. Zde přicházejí na řadu **Generátory**.

## **1. Iterátorový protokol**

Aby šel objekt použít ve `for` cyklu, musí splňovat dvě podmínky (magické metody):

1. **`__iter__`**: Vrátí iterátor (objekt, který umí dávat další prvky).  
2. **`__next__`**: Vrátí další prvek v řadě. Pokud už žádný není, vyvolá výjimku `StopIteration`.

For cyklus v Pythonu ve skutečnosti dělá toto:

```python
iterator = iter(objekt)  
while True:  
    try:  
        hodnota = next(iterator)  
        # ... tělo cyklu ...  
    except StopIteration:  
        break
```

## **2. Generátory (`yield`)**

Psát třídu s `__iter__` a `__next__` je zdlouhavé. Python má elegantní řešení: Generátor.  
Je to funkce, která místo return používá klíčové slovo yield.

### **Jak funguje yield?**

* Když Python narazí na `yield`, **pozastaví** vykonávání funkce a vrátí hodnotu.  
* Stav funkce (proměnné) se uloží do paměti.  
* Při dalším zavolání `next()` funkce pokračuje **přesně tam, kde přestala** (hned za `yield`).

```python
def pocitadlo():  
    yield 1  
    yield 2  
    yield 3

g = pocitadlo()  
print(next(g)) # 1  
print(next(g)) # 2
```

## **3. Generátorová notace (Expressions)**

Podobně jako máme *List Comprehension* (`[x for x in data]`), máme i *Generator Expression*. Stačí vyměnit hranaté závorky za kulaté.

* **Seznam:** `[x*2 for x in range(10)]` -> Vytvoří celý seznam v paměti.  
* **Generátor:** `(x*2 for x in range(10))` -> Vytvoří objekt generátoru, který nic nepočítá, dokud si o to neřeknete.

## **Kdy použít generátory?**

* **Velká data:** Čtení obřích souborů řádek po řádku (CSV, logy).  
* **Nekonečné sekvence:** Generování čísel, signálů, dat z senzorů.  
* **Pipelining:** Řetězení operací zpracování dat bez nutnosti mezivýsledků v RAM.
---
## **Cvičení**

### **1. Odpočítávání**
Napište generátorovou funkci `countdown(n)`, která vrací čísla od `n` do 0 (pomocí `yield`).
Použijte ji v cyklu `for`.

### **2. Nekonečná řada**
Napište generátor `sud_prijmy()`, který vrací posloupnost 0, 2, 4, 6... do nekonečna.
V hlavním programu si vyžádejte prvních 5 čísel (pomocí `next()`) a pak skončete. (Pozor na nekonečný cyklus!)
