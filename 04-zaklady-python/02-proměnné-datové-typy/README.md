# **02 - Proměnné a Datové typy**

V tomto bloku se naučíte, jak v programu uchovávat informace, jak s nimi pracovat a jak získat data od uživatele.

## **1. Proměnné (Variables)**

Proměnná je pojmenované místo v paměti počítače, kam si můžeme uložit hodnotu.

* **Přiřazení:** Hodnotu do proměnné vložíme pomocí rovnítka `=`.  
* **Dynamické typování:** V Pythonu nemusíte deklarovat typ (např. `int x`). Python typ pozná automaticky podle toho, co do proměnné vložíte.

### **Pravidla pro názvy (Naming Conventions)**

V Pythonu dodržujeme konvenci **snake_case**:

* Správně: `pocet_zivotu`, `jmeno_uzivatele`, `max_rychlost`  
* Špatně: `PocetZivotu` (CamelCase se používá pro třídy), `maxRychlost`  
* Názvy nesmí začínat číslem a nesmí obsahovat mezery.

## **2. Základní datové typy**

Python má bohatou sadu vestavěných datových typů. Zde je přehled všech základních (skalárních) typů:

### **Číselné typy**

| Typ | Název v Pythonu | Popis | Příklad |
| :---- | :---- | :---- | :---- |
| **Integer** | `int` | Celá čísla (kladná i záporná, neomezená velikost) | `5`, `-10`, `42`, `1000000` |
| **Float** | `float` | Desetinná čísla (vždy s tečkou, standard IEEE 754) | `3.14`, `-0.01`, `2.0`, `1.5e2` |
| **Complex** | `complex` | Komplexní čísla (reálná + imaginární část) | `2+3j`, `5j` |

### **Textové a bytové typy**

| Typ | Název v Pythonu | Popis | Příklad |
| :---- | :---- | :---- | :---- |
| **String** | `str` | Řetězce znaků (Unicode text) | `"Ahoj"`, `'Python'` |
| **Bytes** | `bytes` | Neměnná posloupnost bytů (hodnoty 0-255) | `b"Data"`, `b'x00xFF'` |
| **Bytearray** | `bytearray` | Měnitelná posloupnost bytů | `bytearray(5)` |

### **Ostatní typy**

| Typ | Název v Pythonu | Popis | Příklad |
| :---- | :---- | :---- | :---- |
| **Boolean** | `bool` | Pravdivostní hodnota | `True`, `False` |
| **NoneType** | `NoneType` | Reprezentace prázdné hodnoty nebo absence hodnoty | `None` |

**Tip:** Typ jakékoliv proměnné zjistíte funkcí `type(promenna)`.

## **3. Přetypování (Type Casting)**

Často potřebujeme změnit typ dat. Například číslo `5` se chová jinak než text `"5"`.

* `int("123")` -> převede text na celé číslo.  
* `float("3.14")` -> převede text na desetinné číslo.  
* `str(100)` -> převede číslo na text (užitečné pro výpis).  
* `bool(0)` -> převede na False (cokoliv jiného než `0` nebo prázdný řetězec je `True).

```python
a = "10"  
b = "20"  
print(a + b)      # Vypíše "1020" (spojení textů)  
print(int(a) + int(b)) # Vypíše 30 (matematický součet)
```

## **4. Vstup od uživatele (`input`)**

Pro interakci s uživatelem slouží funkce `input()`.

* Program se zastaví a čeká, až uživatel něco napíše a stiskne Enter.  
* **Důležité:** `input()` **VŽDY vrací text (string)**. I když uživatel napíše číslo.

Pokud chcete s načtenou hodnotou počítat, musíte ji ihned převést:

```python
vek = int(input("Kolik ti je let? "))
```
---
## **Cvičení**

### **1. Cestování v čase**
Zeptejte se uživatele ("Kolik ti je let?").
Načtenou hodnotu převeďte na číslo, přičtěte k ní 10 a vypište: "Za 10 let ti bude [vysledek]."

### **2. BMI Kalkulačka**
Načtěte od uživatele:
- Váhu v kg (jako float).
- Výšku v metrech (jako float).
Vypočítejte BMI podle vzorce: `BMI = vaha / (vyska * vyska)`.
Vypište výsledek.

### **3. Typová kontrola**
Vytvořte proměnné `x = 100` a `y = "100"`. Vypište jejich datové typy pomocí funkce `type()`.
