### Úkol 5: Systém evidence skladu

Vytvořte modul se čtyřmi funkcemi pro správu skladu:

1. `nacti_sklad(cesta_k_souboru)`:
    ačte CSV soubor do slovníku s touto strukturou:
```python
{
    "KOD_POLOZKY": {"nazev": str, "pocet": int, "cena_za_kus": float}
}

```

2. `aktualizuj_zasoby(sklad, kod, zmena)`:
    * Upraví počet kusů o hodnotu `zmena` (může být kladná i záporná).
    * Pokud by výsledný počet klesl pod 0, změnu neprovede a vrátí `False`, jinak `True`.

3. `spocti_hodnotu_skladu(sklad)`:
    * Vrátí celkovou finanční hodnotu zboží na skladě (součet `pocet * cena_za_kus`).

4. `uloz_sklad(cesta_k_souboru, sklad)`:
    * Uloží aktuální stav slovníku zpět do souboru ve stejném formátu, v jakém byl načten.

**Vstupní data (`sklad.csv`):**

```text
kod;nazev;pocet;cena
A101;Rezistor 10k;150;2.5
B202;Kondenzator 100uF;45;8.0
C303;LED cervena;200;1.2

```