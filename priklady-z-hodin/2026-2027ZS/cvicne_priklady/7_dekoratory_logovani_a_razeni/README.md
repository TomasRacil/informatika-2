# Cvičení 7: Dekorátory, Logování chyb a Benchmark řazení

Cílem cvičení je vytvořit dva samostatné dekorátory (pro měření času a pro logování chyb), vyzkoušet jejich skládání a porovnat rychlost tří vlastních řadicích algoritmů s vestavěnou metodou `.sort()`.

---

## 1. Dva dekorátory

Vytvořte dva samostatné dekorátory s využitím `functools.wraps`:

1. **`@mereni_casu`**:
   - Změří dobu běhu funkce pomocí `time.perf_counter()`.
   - Zaloguje (nebo vypíše) název funkce a naměřený čas v sekundách (např. pomocí `logging.info`).
   - Vrátí výsledek původní funkce.

2. **`@zachyt_chyby`**:
   - Obalí volání funkce blokem `try ... except Exception as e`.
   - Pokud nastane výjimka, zaloguje chybu (např. přes `logging.error(f"Chyba ve funkci {func.__name__}: {e}")`).
   - Výjimku po zalogování pošle dál pomocí `raise` (případně ji ošetří).

---

## 2. Implementace 3 řadicích algoritmů

Vyberte si **libovolné tři** řadicí algoritmy a implementujte je (např. Bubble sort, Selection sort, Insertion sort, Merge sort, Quick sort apod.).

- Na všechny tři algoritmy aplikujte **oba dekorátory současně**:
  ```python
  @mereni_casu
  @zachyt_chyby
  def muj_algoritmus(data: list[int]) -> list[int]:
      ...
  ```
- Vytvořte také obalovací funkci pro vestavěný `.sort()` (nebo `sorted()`) a aplikujte na ni stejné dekorátory.

---

## 3. Porovnání rychlosti (Benchmark)

Vygenerujte náhodná celá čísla a porovnejte rychlost algoritmů na různě velkých množinách:
- Otestujte algoritmy na menších i větších datech (např. 1 000, 5 000, 10 000 prvků).
- Sledujte rozdíly v rychlosti mezi jednotlivými algoritmy a vestavěným `.sort()`.
- Pro velkou množinu (např. 100 000 nebo 1 000 000 prvků) vyzkoušejte rychlost vestavěného `.sort()`.
