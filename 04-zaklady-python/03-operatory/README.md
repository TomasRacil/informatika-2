# **03 - Operátory**

Operátory jsou symboly, které provádějí operace s jednou nebo více hodnotami (operand). V Pythonu je dělíme do několika skupin.

## **1. Aritmetické operátory**

Slouží k běžným matematickým výpočtům.

| Operátor | Název | Popis | Příklad | Výsledek |
| :---- | :---- | :---- | :---- | :---- |
| `+` | Sčítání | Sečte dvě čísla | `10 + 5` | `15` |
| `-` | Odčítání | Odečte druhé číslo od prvního | `10 - 5` | `5` |
| `*` | Násobení | Vynásobí čísla | `10 * 5` | `50` |
| `/` | Dělení | Vždy vrací desetinné číslo (float) | `10 / 2` | `5.0` |
| `//` | Celochíselné dělení | Vrací pouze celou část výsledku (ořízne desetiny) | `10 // 3` | `3` |
| `%` | Modulo | Vrací zbytek po dělení | `10 % 3` | `1` |
| `**` | Mocnění | Umocní číslo na daný exponent | `2 ** 3` | `8` |

**Poznámka k Modulu (`%`):** Tento operátor je extrémně užitečný v programování. Používá se například pro zjištění, zda je číslo sudé (`x % 2 == 0`), nebo pro opakování cyklů (např. dny v týdnu).

## **2. Operátory pro práci s řetězci**

Některé aritmetické operátory fungují i na text, ale chovají se jinak.

| Operátor | Popis | Příklad | Výsledek |
| :---- | :---- | :---- | :---- |
| `+` | Konkatenace (spojení) | `"Ahoj " + "světe"` | `"Ahoj světe"` |
| `*` | Opakování | `"Na" * 3` | `"NaNaNa"` |

## **3. Přiřazovací operátory**

Slouží ke zkrácení zápisu, kdy měníme hodnotu proměnné na základě její původní hodnoty.

| Zápis | Ekvivalent |
| :---- | :---- |
| `x = 5` | Klasické přiřazení |
| `x += 2` | `x = x + 2` |
| `x -= 2` | `x = x - 2` |
| `x *= 2` | `x = x * 2` |
| `x /= 2` | `x = x / 2` |

## **4. Porovnávací operátory**

Vždy vrací hodnotu True nebo False.

| Operátor | Význam | Příklad (`x=5`) |
| :---- | :---- | :---- |
| `==` | Rovná se (pozor na dvě rovnítka!) | `x == 5` (`True`) |
| `!=` | Nerovná se | `x != 5` (`False`) |
| `>` | Větší než | `x > 2` (`True`) |
| `<` | Menší než | `x < 2` (`False`) |
| `>=` | Větší nebo rovno | `x >= 5` (`True`) |
| `<=` | Menší nebo rovno | `x <= 10` (`True`) |

**Python Specialita:** V Pythonu můžete řetězit porovnání, což je v jiných jazycích vzácné.

* `0 < x < 10` (Znamená: x je větší než 0 A ZÁROVEŇ menší než 10)

## **5. Logické operátory**

Slouží ke kombinování podmínek.

| Operátor | Popis | Příklad |
| :---- | :---- | :---- |
| `and` | Platí oba výroky současně | `True and False` -> `False` |
| `or` | Platí alespoň jeden výrok | `True or False` -> `True` |
| `not` | Obrací hodnotu (negace) | `not True` -> `False` |

### **Tabulka pravdivosti pro AND a OR**

| A | B | A and B | A or B |
| :---- | :---- | :---- | :---- |
| False | False | **False** | **False** |
| False | True | **False** | **True** |
| True | False | **False** | **True** |
| True | True | **True** | **True** |

## **6. Členské operátory (Membership)**

Používají se ke kontrole, zda se hodnota nachází v sekvenci (např. v řetězci nebo seznamu).

* `in` - vrací True, pokud je hodnota nalezena.  
* `not in` - vrací True, pokud hodnota NENÍ nalezena.

```python
"a" in "auto"  # True  
"z" in "auto"  # False  
```
---
## **Cvičení**

### **1. Matematické operace**
Zeptejte se uživatele na dvě celá čísla. Vypište výsledky:
- Sčítání
- Násobení
- Umocňování (první číslo na druhou)
- Zbytek po dělení (modulo)

### **2. Detektiv**
Zeptejte se uživatele na jeho oblíbenou větu.
Pomocí operátoru `in` zjistěte, zda věta obsahuje slovo "Python". Vypište True nebo False.

### **3. Dělitelnost**
Načtěte číslo. Zjistěte (True/False), zda je dělitelné 5 A ZÁROVEŇ 10.
