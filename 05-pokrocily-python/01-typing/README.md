# **06 - Type Hinting (Typové anotace)**

Python je dynamicky typovaný jazyk. To znamená, že proměnná může v průběhu času měnit svůj typ a interpreter nekontroluje typy před spuštěním programu.

U větších projektů to ale může vést k chybám, které se těžko hledají. Proto byl do Pythonu přidán **Type Hinting**.

## **Co to je?**

Type Hinting umožňuje programátorovi "napovědět", jaký datový typ očekává.  
Důležité: Python tyto anotace za běhu ignoruje! Program poběží, i když typy nesedí. Slouží primárně pro:

1. **IDE (nápověda, autocomplete).**  
2. **Statickou analýzu (nástroje jako `mypy`).**  
3. **Dokumentaci kódu.**

## **Základní syntaxe**

```python
# Proměnné  
vek: int = 25  
jmeno: str = "Petr"  
aktivni: bool = True

# Funkce (parametry -> návratová hodnota)  
def pozdrav(jmeno: str) -> str:  
    return "Ahoj " + jmeno
```

## **Složené typy (Collections)**

Od Pythonu 3.9 můžeme používat vestavěné typy s hranatými závorkami.

* `list[int]` - Seznam celých čísel  
* `dict[str, int]` - Slovník, kde klíč je string a hodnota int  
* `tuple[int, int]` - N-tice dvou čísel  
* `set[str]` - Množina řetězců

## **Speciální typy**

### **1. Union (Sjednocení) - `|`**

Používá se, když proměnná může být více typů.

* Starší zápis: `Union[int, str]` (vyžaduje from typing import Union)  
* Nový zápis (Python 3.10+): `int | str`

### **2. Optional - `| None`**

Používá se, když hodnota může být nějakého typu, nebo `None`.

* Např.: `uzivatel: str | None = None`

### **3. Any**

Typ `Any` říká "zde může být cokoliv". Tím v podstatě vypínáte kontrolu typů pro danou proměnnou. Používejte opatrně.

### **4. Vlastní třídy**

Jako typ lze použít i název vlastní třídy.

```python
def zpracuj_studenta(student: Student) -> None:  
    ...  
```
---
## **Cvičení**

### **1. Typovaná funkce**
Napište funkci `vypocet_obvodu`, která:
- Přijímá jeden parametr `strana` (typu `int` nebo `float`).
- Vrací `float`.
- Vypočítá obvod čtverce (strana * 4).

### **2. Kolekce**
Vytvořte proměnnou `studenti`, která bude slovníkem, kde klíčem je jméno (`str`) a hodnotou věk (`int`). Použijte správnou typovou anotaci.

### **3. Optional**
Napište funkci `najdi_uzivatele(id: int)`, která vrátí jméno uživatele (`str`) nebo `None`, pokud uživatel neexistuje (vracejte `None` pro jakékoliv ID > 10). Nezapomeňte na návratový typ `str | None` (nebo `Optional[str]`).
