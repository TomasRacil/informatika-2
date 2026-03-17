# **09 - Výjimky a Error Handling**

Chyby v programech dělíme na dva základní typy:

1. **Syntaktické chyby (Syntax Errors):** Program vůbec nejde spustit (chybí dvojtečka, špatné odsazení). Ty musí opravit programátor.  
2. **Výjimky (Exceptions):** Chyby, které nastanou až za běhu programu (Runtime Errors). Například soubor neexistuje, uživatel zadal text místo čísla, došlo místo na disku.

Pokud výjimku neošetříme, program **spadne** (ukončí se s chybovým výpisem). Cílem Error Handlingu je výjimku zachytit a zareagovat na ni (vypsat hlášku, zkusit akci znovu), aby program mohl pokračovat.

## **Základní syntaxe**

```python
try:  
    # Kód, který může vyvolat chybu  
    vysledek = 10 / 0  
except ZeroDivisionError:  
    # Kód, který se provede, pokud nastane dělení nulou  
    print("Nelze dělit nulou!")  
except Exception as e:  
    # Zachytí jakoukoliv jinou chybu  
    print(f"Jiná chyba: {e}")
```

## **Bloky `else` a `finally`**

Python má bohatší syntaxi než jen `try-catch` známé z jiných jazyků.

* **`try`**: Testovaný kód.  
* **`except`**: Ošetření konkrétní chyby.  
* **`else`**: Provede se, pokud v bloku `try` **nenastala žádná chyba**.  
* **`finally`**: Provede se **VŽDY** (ať už chyba byla nebo ne). Slouží k úklidu (zavírání souborů, spojení).


## **Vyvolání výjimky (raise)**

Někdy chceme chybu vyvolat my sami (např. při validaci dat).

```python
def nastav_vek(vek):  
    if vek < 0:  
        raise ValueError("Věk nesmí být záporný!")
```

## **Vlastní výjimky**

Pro složitější projekty je dobré definovat si vlastní typy chyb. Stačí vytvořit třídu, která dědí z Exception.

```python
class HraSkoncilaError(Exception):  
    pass

# Použití  
raise HraSkoncilaError("Došly životy")
```

## **Časté chyby (Anti-patterns)**

### **1. Bare Except (Holý except)**

```python
# ŠPATNĚ  
try:  
    neco_udelej()  
except:  # Chytne úplně všechno, včetně přerušení klávesnicí (Ctrl+C)  
    pass
```

Vždy specifikujte, jakou chybu čekáte (např. `except ValueError`). Pokud chcete chytit vše, použijte `except Exception`.

### **2. Pass v except bloku**

Pokud chybu chytíte a nic neuděláte (`pass`), chyba "zmizí". Program pokračuje v nekonzistentním stavu a vy nevíte proč. Vždy chybu alespoň zalogujte.

---
## **Cvičení**

### **1. Kalkulačka s ochranou**
Napište program, který:
1. Načte dvě čísla od uživatele.
2. Vydělí je.
3. Ošetří `ValueError` (pokud zadá text) a `ZeroDivisionError` (pokud dělí nulou).
4. Vypíše výsledek nebo chybovou hlášku.

### **2. Validátor**
Napište funkci `registrace(jmeno)`, která vyvolá `ValueError`, pokud je jméno prázdné nebo kratší než 3 znaky. Funkci zavolejte v bloku `try-catch` a odchyťte chybu.
