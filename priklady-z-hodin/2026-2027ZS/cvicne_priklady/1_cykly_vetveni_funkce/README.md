
### Úkol 1: Cykly, n-tice a větvení

Napište funkci `analyzuj_mereni(casy, teploty, limit=85.0)`.

**Požadavky:**

* Současně procházejte seznamy `casy` a `teploty` pomocí funkce `zip()`.
* Pomocí `enumerate()` sledujte index aktuálního měření.
* Zaznamenejte indexy měření, kde teplota překročila zadaný `limit`.
* Funkce vrátí n-tici: `(celkovy_pocet, pocet_prekroceni, seznam_indexu)`.

**Testovací kód:**

```python
casy = [0, 10, 20, 30, 40, 50]
teploty = [72.5, 84.0, 86.2, 85.1, 80.0, 91.4]

vysledek = analyzuj_mereni(casy, teploty, limit=85.0)
print(vysledek)
# Očekávaný výstup: (6, 3, [2, 3, 5])

```




