### Úkol 6: Třídy, typování a zapouzdření (Bankovní systém)

Cílem tohoto cvičení je procvičit první tři témata pokročilého Pythonu:
1. **Type Hinting (typové anotace)** – typování parametrů, návratových hodnot a atributů.
2. **Úvod do tříd a objektů** – tvorba tříd, konstruktor `__init__`, parametr `self`, instance a metody.
3. **Modifikátory přístupu a vlastnosti (`@property`)** – chráněné atributy (`_atribut`), gettery, settery s validací a vypočítané vlastnosti.

---

### Specifikace tříd

Implementujte dvě třídy: `BankovniUcet` a `Banka`.

#### 1. Třída `BankovniUcet`
Reprezentuje bankovní účet konkrétního klienta.

* **Konstruktor `__init__(self, cislo_uctu: str, majitel: str, pocatecni_zustatek: float = 0.0)`:**
  * Uloží číslo účtu (`_cislo_uctu: str`).
  * Uloží jméno majitele (`_majitel: str`).
  * Nastaví počáteční zůstatek (`_zustatek: float`) přes setter vlastnosti `zustatek`.
  * Inicializuje historii transakcí (`_historie: list[tuple[str, float]]`). Pokud byl počáteční vklad kladný, zaznamená transakci `("Vklad", pocatecni_zustatek)`.

* **Vlastnost `majitel` (`@property`):**
  * **Getter:** Vrátí jméno majitele.
  * **Setter (`@majitel.setter`):** Nastaví nové jméno majitele. Pokud je zadaný řetězec po oříznutí prázdný, vyvolá `ValueError("Jméno majitele nesmí být prázdné.")`.

* **Vlastnost `zustatek` (`@property`):**
  * **Getter:** Vrátí aktuální zůstatek.
  * **Setter (`@zustatek.setter`):** Umožní nastavit zůstatek. Pokud je hodnota záporná ($< 0$), vyvolá `ValueError("Zůstatek nemůže být záporný.")`.

* **Vlastnost `cislo_uctu` (`@property` - pouze getter):**
  * Vrátí číslo účtu (číslo účtu nelze po vytvoření měnit).

* **Metoda `vloz(self, castka: float) -> bool`:**
  * Pokud je `castka > 0`, přičte částku k zůstatku, zaznamená transakci `("Vklad", castka)` a vrátí `True`.
  * V opačném případě vrátí `False`.

* **Metoda `vyber(self, castka: float) -> bool`:**
  * Pokud je `castka > 0` a zároveň je na účtu dostatek prostředků (`castka <= self._zustatek`), odečte částku, zaznamená transakci `("Výběr", castka)` a vrátí `True`.
  * V opačném případě vrátí `False`.

* **Metoda `vypis_transakce(self) -> list[str]`:**
  * Vrátí seznam řetězců ve formátu: `["Vklad: +1000.00 Kč", "Výběr: -200.00 Kč", ...]`.

* **Speciální metody:**
  * `__str__(self) -> str`: Vrátí např. `Účet 123456/0100 (Jan Novák) - Zůstatek: 1500.00 Kč`.
  * `__repr__(self) -> str`: Vrátí `BankovniUcet(cislo_uctu='123456/0100', majitel='Jan Novák', zustatek=1500.0)`.

---

#### 2. Třída `Banka`
Spravuje více bankovních účtů a převody mezi nimi.

* **Konstruktor `__init__(self, nazev: str)`:**
  * Uloží název banky (`nazev: str`).
  * Inicializuje prázdný slovník účtů `_ucty: dict[str, BankovniUcet]`, kde klíčem je číslo účtu a hodnotou instance `BankovniUcet`.

* **Metoda `zaloz_ucet(self, cislo_uctu: str, majitel: str, pocatecni_vklad: float = 0.0) -> BankovniUcet`:**
  * Pokud číslo účtu v bance již existuje, vyvolá `ValueError(f"Účet {cislo_uctu} již existuje.")`.
  * Vytvoří novou instanci `BankovniUcet`, uloží ji do slovníku `_ucty` a vrátí ji.

* **Metoda `ziskej_ucet(self, cislo_uctu: str) -> BankovniUcet | None`:**
  * Vrátí účet podle čísla, nebo `None` pokud účet neexistuje.

* **Metoda `preved_penize(self, z_uctu: str, na_ucet: str, castka: float) -> bool`:**
  * Ověří existenci obou účtů a provede výběr z prvního a vklad na druhý.
  * Pokud se výběr podaří, provede vklad na cílový účet a vrátí `True`.
  * Pokud některý účet neexistuje nebo na zdrojovém účtu není dostatek peněz, vrátí `False`.

* **Vlastnost `celkovy_kapital` (`@property`):**
  * Vrátí součet zůstatků všech účtů vedených v bance.

---

### Testovací kód

```python
banka = Banka("Python Banka")
ucet1 = banka.zaloz_ucet("111/0800", "Jan Novák", 1000.0)
ucet2 = banka.zaloz_ucet("222/0800", "Eva Černá", 500.0)

ucet1.vloz(500.0)
ucet1.vyber(200.0)

uspech = banka.preved_penize("111/0800", "222/0800", 300.0)
print(f"Převod proběhl: {uspech}")

print(ucet1)
print(ucet2)
print("Celkový kapitál banky:", banka.celkovy_kapital)
print("Historie účtu 1:", ucet1.vypis_transakce())
```
