# Cvičení: Objektový Inventory System v Pythonu
**Cíl:** Procvičit OOP, magické metody (`__dunder__`), tvorbu vlastních dekorátorů a trvalé ukládání dat do souboru.

---

### Část 1: Třída `Polozka` a magické metody
Vytvořte třídu `Polozka`, která bude reprezentovat zboží ve skladu.

1. **Konstruktor `__init__`**: Třída bude mít atributy `nazev` (str), `cena` (float) a `mnozstvi` (int).
2. **Reprezentace `__str__` a `__repr__`**:
* `__str__`: Vrací čitelný popis, např. *"Jablko: 25.50 Kč (100 ks)"*.
* `__repr__`: Vrací formát vhodný pro debugging, např. `Polozka('Jablko', 25.5, 100)`.

3. **Porovnávání `__eq__`**: Dvě položky jsou stejné, pokud mají stejný `nazev` a `cena`.
4. **Aritmetika `__add__`**:
    * Umožněte sečíst dvě instance `Polozka` (např. `item1 + item2`).
    * Pokud mají stejný název a cenu, vraťte novou instanci se sečteným množstvím.
    * Pokud nejsou stejné, vyvolejte výjimku `ValueError` s textem, že nelze sčítat různé zboží.

---

### Část 2: Dekorátor pro logování

Vytvořte samostatnou funkci (dekorátor) nazvanou `log_operace`.

1. Dekorátor by měl vypisovat informace do konzole (nebo do souboru `log.txt`) o tom, jaká metoda byla zavolána a s jakými argumenty.
2. Formát výstupu např.: `[LOG] Volána metoda 'odeber_zbozi' s argumenty: ('Hruška', 5)`.
3. Tento dekorátor později použijete ve třídě `Sklad` pro metody, které mění stav skladu (přidání/odebrání zboží).

*(Tip: Nezapomeňte na `functools.wraps`, aby se zachovala metadata dekorovaných funkcí.)*

---

### Část 3: Třída `Sklad` a práce se soubory
Vytvořte třídu `Sklad`, která bude spravovat kolekci položek (např. ve slovníku nebo seznamu).

1. **Magická metoda `__len__`**: Vrátí celkový počet kusů všeho zboží na skladu.
2. **Magická metoda `__getitem__`**: Umožní získat položku podle názvu pomocí indexace (např. `muj_sklad["Jablko"]`).
3. **Metody pro správu**:
    * `pridej_polozku(polozka)`: Přidá objekt `Polozka`. Pokud už existuje, zvýší množství (využijte vaši implementaci `__add__`). **Odekorujte tuto metodu pomocí `@log_operace`.**
    * `odeber_polozku(nazev, pocet)`: Sníží množství. Pokud klesne na 0, položku odstraní. **Odekorujte tuto metodu pomocí `@log_operace`.**


4. **Práce se soubory (Persistence)**:
    * Implementujte metodu `uloz_do_csv(soubor)`. Metoda projde všechny položky a uloží je do textového souboru ve formátu `nazev,cena,mnozstvi`.
    * Implementujte statickou metodu (nebo class method) `nacti_z_csv(soubor)`, která načte soubor, vytvoří instance `Polozka` a vrátí naplněnou instanci `Sklad`.



---

### Část 4: Context Manager

Upravte třídu `Sklad` tak, aby fungovala jako **Context Manager** (použití s `with`).

1. Implementujte `__enter__` a `__exit__`.
2. Při vstupu (`__enter__`) se může například vypsat "Otevírám sklad...".
3. Při výstupu (`__exit__`) se stav skladu **automaticky uloží** do souboru `autosave_sklad.csv`.

---

### Ukázka očekávaného použití (Testovací skript)

```python
def main():
    # 1. Vytvoření položek
    jablka = Polozka("Jablko", 10, 50)
    dalsi_jablka = Polozka("Jablko", 10, 20)
    hrušky = Polozka("Hruška", 15, 30)

    print(f"Test sčítání: {jablka + dalsi_jablka}")  # Mělo by vypsat Jablko s množstvím 70

    # 2. Práce se skladem
    sklad = Sklad()
    sklad.pridej_polozku(jablka)
    sklad.pridej_polozku(dalsi_jablka) # Log: Volána metoda pridej...
    sklad.pridej_polozku(hrušky)       # Log: Volána metoda pridej...
    
    print(f"Položka ve skladu: {sklad['Hruška']}")
    print(f"Celkem kusů na skladu: {len(sklad)}")

    # 3. Uložení a načtení
    sklad.uloz_do_csv("sklad_data.csv")
    print("Uloženo.")

    novy_sklad = Sklad.nacti_z_csv("sklad_data.csv")
    print(f"Načteno {len(novy_sklad)} kusů zboží z nového skladu.")

if __name__ == "__main__":
    main()

```