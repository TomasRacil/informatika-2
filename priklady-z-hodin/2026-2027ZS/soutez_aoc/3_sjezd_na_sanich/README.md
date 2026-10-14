# Úkol 3: Sjezd na saních (Toboggan Trajectory)

*Inspirace: Advent of Code 2020 – Den 3*

## Příběh
Cestujete zasněženou krajinou na saních a potřebujete bezpečně sjet zalesněný svah. Vaše mapa znázorňuje stromy a volná místa:
- `.` označuje volné zasněžené místo
- `#` označuje strom, kterému se musíte vyhnout

Příklad vstupních dat:
```text
..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#
```

### Klíčová vlastnost mapy:
Svah je velmi široký – vzor stromů na mapě se směrem doprava **neustále periodicky opakuje**!
Pokud tedy vyjedete vpravo mimo šířku řádku, ocitnete se znovu na levém okraji téhož vzoru.
*(Tip: Využijte operátor modulo `%` pro indexování na řádku: `index_sloupce % sirka_radku`).*

---

## Část 1: Standardní trajektorie (Doprava 3, Dolů 1)

Začínáte v levém horním rohu na souřadnicích `[0, 0]` (což je volné místo `.`).

Vaše saně mají pevnou trajektorii:
V každém kroku se posunete **o 3 políčka doprava** a **o 1 políčko dolů**.

Postupujete tak dlouho, dokud nesjedete pod spodní okraj mapy (projdete všechny řádky).

### Váš úkol:
1. Načtěte mapu ze souboru.
2. Simulujte pohyb saní s posunem `(dx = 3, dy = 1)`.
3. Spočítejte, kolik stromů (`#`) na své trase trefíte.

### Příklad (test.txt):
Při trajektorii doprava 3, dolů 1 trefíte přesně **7** stromů.

---

## Část 2: Otestování více trajektorií

Abyste našli optimální trasu, chcete vyzkoušet několik různých úhlů sjezdu (různých sklonů).

Spočítejte počet trefených stromů pro těchto **5 různých trajektorií**:
1. **Doprava 1, dolů 1** (`dx = 1, dy = 1`)
2. **Doprava 3, dolů 1** (`dx = 3, dy = 1`) – to je trajektorie z Části 1
3. **Doprava 5, dolů 1** (`dx = 5, dy = 1`)
4. **Doprava 7, dolů 1** (`dx = 7, dy = 1`)
5. **Doprava 1, dolů 2** (`dx = 1, dy = 2`) – *pozor: procházíte pouze každý druhý řádek!*

### Váš úkol:
1. Pro každou z 5 trajektorií spočítejte počet trefených stromů.
2. Všechny tyto dílčí počty **vzájemně vynásobte**.
3. Jako výsledek odevzdejte tento celkový součin.

### Příklad (test.txt):
- Trajektorie (1, 1): 2 stromy
- Trajektorie (3, 1): 7 stromů
- Trajektorie (5, 1): 3 stromy
- Trajektorie (7, 1): 4 stromy
- Trajektorie (1, 2): 2 stromy
- **Součin:** `2 * 7 * 3 * 4 * 2 = 336`
