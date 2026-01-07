# **08 - Dekorátory**

Dekorátory jsou jedním z nejsilnějších a zároveň často nepochopených nástrojů v Pythonu. Umožňují nám **upravit chování funkce nebo třídy**, aniž bychom museli měnit její vnitřní kód.

Abychom pochopili, jak fungují, musíme jít krok za krokem.

## **1. Funkce je objekt (First-Class Citizen)**

V Pythonu je funkce jen další typ objektu (jako `int` nebo `str`). To znamená dvě zásadní věci:

1. **Můžeme ji uložit do proměnné.**  
2. **Můžeme ji předat jako parametr jiné funkci.**  
3. **Můžeme ji vrátit jako výsledek z jiné funkce.**

```python
def zvys_o_jedna(cislo):  
    return cislo + 1

# Uložení funkce do proměnné (bez závorek - nevoláme ji, jen odkazujeme)  
moje_funkce = zvys_o_jedna   
print(moje_funkce(5)) # Vypíše 6
```

## **2. Vnořené funkce (Nested Functions)**

Uvnitř funkce můžeme definovat další funkci. Tato vnitřní funkce existuje jen uvnitř té vnější (je tam "schovaná").

```python
def rodic():  
    print("Jsem rodič")  
      
    def potomek():  
        print("Jsem potomek")  
      
    potomek() # Musíme ji zavolat uvnitř, aby se provedla
```

## **3. Princip Wrapperu (Obálky)**

Tady se dostáváme k jádru dekorátorů. Můžeme vytvořit funkci, která přijme jinou funkci, "obalí" ji nějakým kódem a tu novou, obalenou funkci vrátí.

```python
def dekorator(puvodni_funkce):  
    # Wrapper je ta "obálka"  
    def wrapper():  
        print("--- Kód PŘED spuštěním funkce ---")  
        puvodni_funkce() # Spustíme tu, kterou jsme dostali  
        print("--- Kód PO spuštění funkce ---")  
      
    return wrapper # Vracíme novou funkci (wrapper)
```

## **4. Syntaxe se zavináčem `@`**

Výše uvedený princip je přesně to, co dělá `@`. Je to jen "syntaktické zjednodušení" (zkratka), který nám ušetří psaní.

```shell
# Místo složitého:  
# pozdrav = dekorator(pozdrav)

# Píšeme jednoduše:  
@dekorator  
def pozdrav():  
    print("Ahoj!")
```

## **5. Pokročilý dekorátor (Šablona)**

V praxi funkce přijímají argumenty (`*args`, `**kwargs`) a vrací hodnoty (`return`). Také chceme, aby si funkce zachovala své jméno (pomocí `functools.wraps`).

Toto je univerzální šablona, kterou budete používat v 99 % případů:

```python
import functools

def muj_dekorator(funkce):  
    @functools.wraps(funkce) # 1. Zachová metadata (jméno, dokumentaci)  
    def wrapper(*args, **kwargs): # 2. Přijme jakékoliv argumenty  
        # --- Kód PŘED ---  
        print(f"Log: Volám {funkce.__name__}")  
          
        # 3. Spustí původní funkci s jejími argumenty  
        vysledek = funkce(*args, **kwargs)  
          
        # --- Kód PO ---  
        print("Log: Dokončeno")  
          
        # 4. Vrátí výsledek původní funkce  
        return vysledek  
          
    return wrapper
```

## **Kdy dekorátory použít?**

* **Logování:** Zaznamenat, kdo a kdy funkci zavolal.  
* **Měření času:** Zjistit, jak dlouho funkce běží.  
* **Autentizace:** Ověřit, zda má uživatel právo (např. `@login_required` ve webových aplikacích).  
* **Opakování:** Zkusit funkci zavolat znovu, pokud selže (např. při výpadku sítě).
---
## **Cvičení**

### **1. Měřič času**
Napište dekorátor `zmer_cas`, který změří, jak dlouho funkce běžela (použijte `time.time()`).
- Před spuštěním funkce si uložte startovní čas.
- Po spuštění funkce si uložte koncový čas.
- Vypište rozdíl.

### **2. Aplikace**
Vytvořte funkci `dlouha_operace`, která jen uspí program na 1 sekundu (`time.sleep(1)`). Obalte ji dekorátorem a ověřte, že vypíše dobu trvání cca 1.0s.
