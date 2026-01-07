# **12 - Argumenty příkazové řádky (CLI)**

Profesionální skripty a nástroje se málokdy ovládají úpravou zdrojového kódu nepo přes `input()`. Místo toho je ovládáme pomocí **argumentů** při spouštění z terminálu.

Příklad:

```python
python script.py input.txt --verbose --output vysledek.txt
```

## **1. Modul `sys` (`sys.argv`)**

Nejzákladnější způsob přístupu k argumentům. `sys.argv` je obyčejný seznam (list), který obsahuje všechna slova z příkazové řádky.

* `sys.argv[0]` je vždy **název skriptu** (např. `main.py`).  
* `sys.argv[1]` je první argument.

**Nevýhody:**

* Všechno jsou to řetězce (musíte ručně převádět na `int`).
* Musíte ručně řešit chyby (co když uživatel argument nezadá?).
* Musíte ručně psát nápovědu.

## **2. Modul `argparse` (Doporučeno)**

Toto je standardní knihovna pro tvorbu CLI aplikací. Řeší za vás většinu problémů.

### **Hlavní výhody:**

1. **Automatická nápověda:** Stačí spustit program s `-h` nebo `--help`.  
2. **Kontrola typů:** Můžete říct `type=int` a argparse sám vyhodí chybu, pokud uživatel zadá text.  
3. **Výchozí hodnoty:** `default=10`.  
4. **Povinné vs. Volitelné:** Poziční argumenty (bez pomlček) jsou povinné, volitelné začínají `--`.

### **Syntaxe**

```python
import argparse

# 1. Parser  
parser = argparse.ArgumentParser(description="Popis programu")

# 2. Argumenty  
parser.add_argument("jmeno", help="Vaše jméno") # Povinný  
parser.add_argument("--vek", type=int, default=18) # Volitelný

# 3. Zpracování  
args = parser.parse_args()

print(f"Ahoj {args.jmeno}, je ti {args.vek}.")
```

## **Spouštění z terminálu**

Argumenty se zadávají za název souboru oddělené mezerou.

```python
python main.py Petr --vek 25  
```
---
## **Cvičení**

### **1. Pozdrav (sys.argv)**
Napište skript, který přijme jméno z terminálu a pozdraví.
1. Pokud uživatel nezadá argument, vypište: "Chyba: Zadej jméno."
2. Pokud zadá "Petr", vypište: "Ahoj Petr".

### **2. Mocnina (argparse)**
Napište skript pomocí `argparse`.
- Přijme povinný argument `cislo` (int).
- Přijme volitelný argument `--mocnina` (int, default=2).
- Vypíše výsledek umocnění.
