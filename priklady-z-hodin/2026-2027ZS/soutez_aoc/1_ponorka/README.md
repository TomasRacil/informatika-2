# Úkol 1: Navigace ponorky (Dive!)

*Inspirace: Advent of Code 2021 – Den 2*

## Příběh
Jste v experimentální ponorce a potřebujete ji navigovat podle plánu trasy. Ponorka přijímá jednoduché příkazy zapsané v textovém souboru, kde každý řádek obsahuje jeden příkaz a číselnou hodnotu oddělené mezerou.

Příklad vstupních dat:
```text
forward 5
down 5
forward 8
up 3
down 8
forward 2
```

---

## Část 1: Základní pohyb

Ponorka začíná na souřadnicích `horizontal = 0` a `depth = 0` (hloubka).

Příkazy ovlivňují polohu následovně:
- `forward X` posune ponorku dopředu o `X` jednotek (zvýší `horizontal` o `X`).
- `down X` ponoří ponorku o `X` jednotek níže (zvýší `depth` o `X`).
- `up X` vynoří ponorku o `X` jednotek výše (sníží `depth` o `X`).

### Váš úkol:
1. Projděte všechny příkazy ze souboru.
2. Spočítejte konečnou hodnotu `horizontal` a `depth`.
3. Jako výsledek odevzdejte **součin těchto dvou hodnot** (`horizontal * depth`).

### Příklad (test.txt):
Po provedení všech 6 kroků:
- `horizontal` = 15
- `depth` = 10
- **Výsledek:** `15 * 10 = 150`

---

## Část 2: Reálné ovládání s mířením (Aim)

Přečetli jste si manuál k ponorce podrobněji a zjistili jste, že `down` a `up` nemění přímo hloubku, ale **úhel náklonu / míření (aim)**!

Ponorka začíná s `horizontal = 0`, `depth = 0` a `aim = 0`.

Příkazy ve skutečnosti fungují takto:
- `down X` zvýší vaši hodnotu `aim` o `X`.
- `up X` sníží vaši hodnotu `aim` o `X`.
- `forward X` provede **dvě** akce:
  1. Zvýší vaši vodorovnou pozici (`horizontal`) o `X`.
  2. Zvýší vaši hloubku (`depth`) o hodnotu `aim * X`.

### Váš úkol:
1. Znovu projděte příkazy ze souboru podle nových pravidel.
2. Spočítejte konečnou hodnotu `horizontal` a `depth`.
3. Jako výsledek odevzdejte opět **součin** (`horizontal * depth`).

### Příklad (test.txt):
- `forward 5` -> horizontal = 5, depth = 0, aim = 0
- `down 5` -> aim = 5
- `forward 8` -> horizontal = 13, depth = 5 * 8 = 40, aim = 5
- `up 3` -> aim = 2
- `down 8` -> aim = 10
- `forward 2` -> horizontal = 15, depth = 40 + (10 * 2) = 60, aim = 10
- **Konečný stav:** horizontal = 15, depth = 60
- **Výsledek:** `15 * 60 = 900`
