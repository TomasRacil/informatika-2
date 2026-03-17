# **Operátory**

Operátory jsou speciální symboly, které provádějí operace s jednou, dvěma nebo třemi hodnotami (operandy) a vracejí výsledek. V C++ je používáme pro matematické výpočty, přiřazování hodnot, porovnávání a logické operace.

## **Aritmetické operátory**

Používají se pro základní matematické operace.

| Operátor | Popis | Příklad (a = 10, b = 3) | Výsledek |
| :---- | :---- | :---- | :---- |
| + | Sčítání | a + b | 13 |
| - | Odčítání | a - b | 7 |
| * | Násobení | a * b | 30 |
| / | Dělení | a / b | 3 (celočíselné dělení) |
| % | Modulo (zbytek po dělení) | a % b | 1 |
| ++ | Inkrementace (zvýšení o 1) | a++ nebo ++a | a se změní na 11 |
| -- | Dekrementace (snížení o 1) | a-- nebo --a | a se změní na 9 |

*Poznámka: U dělení záleží na datových typech. Pokud jsou oba operandy celá čísla, provede se celočíselné dělení (výsledek je bez desetinné části). Pokud je alespoň jeden operand desetinné číslo, výsledek bude také desetinné číslo.*

## **Přiřazovací operátory**

Používají se pro přiřazení hodnoty do proměnné.

| Operátor | Ekvivalent | Popis |
| :---- | :---- | :---- |
| = |  | Základní přiřazení (a = 10) |
| += | a = a + b | Sečti a přiřaď |
| -= | a = a - b | Odečti a přiřaď |
| *= | a = a * b | Vynásob a přiřaď |
| /= | a = a / b | Vyděl a přiřaď |
| %= | a = a % b | Vypočti modulo a přiřaď |

## **Relační (porovnávací) operátory**

Porovnávají dvě hodnoty a jako výsledek vracejí logickou hodnotu `true` (pravda) nebo `false` (nepravda).

| Operátor | Popis | Příklad (a = 5, b = 10) | Výsledek |
| :---- | :---- | :---- | :---- |
| == | Je rovno | a == b | false |
| != | Není rovno | a != b | true |
| > | Větší než | a > b | false |
| < | Menší než | a < b | true |
| >= | Větší nebo rovno | a >= b | false |
| <= | Menší nebo rovno | a <= b | true |

## **Logické operátory**

Spojují nebo modifikují logické výrazy. Výsledkem je opět `true` nebo `false`.

| Operátor | Popis | Příklad |
| :---- | :---- | :---- |
| && | Logický AND (a zároveň) | (a < b) && (b > 0) - true pokud platí oba výrazy |
| \|\| | Logický OR ( nebo) | (a < b) \|\| (b > 0) - true pokud platí alespoň jeden výraz |
| ! | Logická negace (NOT) | !(a == b) - Obrátí logickou hodnotu výrazu |

## **Priorita operátorů**

Operátory mají pevně danou prioritu, která určuje pořadí jejich vyhodnocování (podobně jako v matematice, kde má násobení přednost před sčítáním). Například `5 + 10 * 2` se vyhodnotí jako `5 + (10 * 2) = 25`.

Pokud si nejsme jisti prioritou nebo chceme pořadí změnit, **používáme kulaté závorky `()`**.

```cpp
int vysledek1 = 5 + 10 * 2; // vysledek1 bude 25  
int vysledek2 = (5 + 10) * 2; // vysledek2 bude 30  
```
---
## **Cvičení**

### **1. Jednoduchá kalkulačka**
Napište program, který:
1. Načte od uživatele dvě celá čísla.
2. Vypíše výsledky součtu, rozdílu, součinu, podílu (celočíselného) a zbytku po dělení.

### **2. Logické operátory**
Vytvořte program, který ověří, zda zadané číslo patří do intervalu `<10, 20>`.
- Použijte operátor `&&` pro spojení podmínek (větší nebo rovno 10 A ZÁROVEŇ menší nebo rovno 20).
