# Úkol 2: Ověřování hesel (Password Philosophy)

*Inspirace: Advent of Code 2020 – Den 2*

## Příběh
Bezpečnostní systém ve firemní databázi byl napaden. Abychom zjistili rozsah poškození, musíme ověřit integritu uložených hesel. Vstupní soubor obsahuje seznam hesel a u každého z nich bezpečnostní pravidlo, které mělo heslo splňovat.

Každý řádek má formát:
`MIN-MAX ZNAK: HESLO`

Příklad vstupních dat:
```text
1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
```

---

## Část 1: Pravidlo počtu výskytů

V první části pravidlo udává minimální a maximální počet výskytů daného znaku v heslu:
- `1-3 a: abcde` znamená, že písmeno `a` se musí v heslu `abcde` vyskytovat minimálně 1× a maximálně 3×.
  - V heslu `abcde` je `a` právě 1× -> **Platné heslo** ✅.
- `1-3 b: cdefg` znamená, že `b` se musí vyskytovat 1× až 3×.
  - V heslu `cdefg` se `b` nevyskytuje ani jednou (0×) -> **Neplatné heslo** ❌.
- `2-9 c: ccccccccc` znamená, že `c` se musí vyskytovat 2× až 9×.
  - V heslu je `c` právě 9× -> **Platné heslo** ✅.

### Váš úkol:
1. Projděte soubor řádek po řádku.
2. Zjistěte, kolik hesel je **platných** podle Pravidla 1.
3. Jako výsledek odevzdejte **počet platných hesel**.

### Příklad (test.txt):
- Výsledek: **2** platná hesla ze 3.

---

## Část 2: Pravidlo pozic (Toboggan Corporate Policy)

Při dalším čtení firemní dokumentace zjistíte, že první pravidlo bylo zastaralé. Nové pravidlo říká:
Čísla `MIN` a `MAX` ve skutečnosti znamenají **pozice v heslu** (pozor: **indexováno od 1**, nikoliv od 0! První znak má index 1, druhý index 2 atd.).

Pravidlo zní:
Daný znak se musí nacházet **na právě jedné ze zadaných pozic** (buď na první pozici, nebo na druhé pozici, ale **nikdy ne na obou současně** – tzv. operace XOR).

### Příklad ověření:
- `1-3 a: abcde`:
  - Pozice 1 obsahuje `a` (shoda).
  - Pozice 3 obsahuje `c` (neshoda).
  - Právě jedna pozice se shoduje -> **Platné heslo** ✅.
- `1-3 b: cdefg`:
  - Pozice 1 obsahuje `c` (neshoda).
  - Pozice 3 obsahuje `e` (neshoda).
  - Ani jedna pozice se neshoduje -> **Neplatné heslo** ❌.
- `2-9 c: ccccccccc`:
  - Pozice 2 obsahuje `c` (shoda).
  - Pozice 9 obsahuje `c` (shoda).
  - Obě pozice obsahují hledaný znak, což pravidlo zakazuje -> **Neplatné heslo** ❌.

### Váš úkol:
1. Znovu projděte soubor řádek po řádku.
2. Zjistěte, kolik hesel je **platných** podle Pravidla 2.
3. Jako výsledek odevzdejte **počet platných hesel**.

### Příklad (test.txt):
- Výsledek: **1** platné heslo ze 3.
