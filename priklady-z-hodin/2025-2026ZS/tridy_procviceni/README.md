# Zadání cvičení: Objektově orientované programování

**Téma:** Interakce objektů, zapouzdření a ošetření výjimek
**Název projektu:** Univerzitní informační systém (Mini-UIS)

## Cíl úlohy

Cílem je vytvořit jednoduchý systém pro správu studentů a kurzů. Úloha slouží k procvičení vazby mezi objekty (agregace 1:N a M:N), práce s vlastními výjimkami a použití dekorátoru `@property` pro vypočítané atributy.

-----

## Specifikace tříd

Implementujte následující tři třídy podle uvedené specifikace:

### 1. Třída `KapacitaNaplnenaError`

  * Dědí ze standardní třídy `Exception`.
  * Tato výjimka bude vyvolána v případě, že se student pokouší zapsat do kurzu, který již dosáhl své maximální kapacity.

### 2. Třída `Kurz`

Reprezentuje jeden vyučovaný předmět.

  * **Atributy (metoda `__init__`):**
      * `kod` (str): Kód předmětu (např. "IT101").
      * `nazev` (str): Celý název předmětu.
      * `kapacita` (int): Maximální počet studentů, kteří mohou být zapsáni.
      * `_studenti` (list): Privátní seznam instancí zapsaných studentů.
  * **Metody:**
      * `pridej_studenta(student)`: Přidá instanci studenta do seznamu `_studenti`.
          * *Validace:* Pokud je počet studentů roven kapacitě, metoda vyvolá výjimku `KapacitaNaplnenaError`.
          * *Validace:* Pokud již student v seznamu existuje, metoda jej znovu nepřidá (volitelně vypíše informaci).
      * `__len__`: Vrátí aktuální počet zapsaných studentů.
      * `__str__`: Vrací textovou reprezentaci stavu kurzu (např. *"IT101: Python [5/20]"*).

### 3. Třída `Student`

Reprezentuje studenta univerzity.

  * **Atributy (metoda `__init__`):**
      * `jmeno` (str): Jméno a příjmení.
      * `osobni_cislo` (int): Identifikační číslo studenta.
      * `_znamky` (dict): Slovník, kde klíčem je kód kurzu a hodnotou známka (int).
      * `_zapsane_kurzy` (list): Seznam instancí kurzů, které student navštěvuje.
  * **Metody:**
      * `zapis_kurz(kurz)`: Klíčová metoda pro interakci.
          * Zavolá metodu `kurz.pridej_studenta(self)`.
          * Musí obsahovat blok `try-except`, který zachytí `KapacitaNaplnenaError`. V případě chyby vypíše do konzole chybovou hlášku a program pokračuje dál.
          * Pokud zápis proběhne bez chyby, uloží si instanci kurzu do svého seznamu `_zapsane_kurzy`.
      * `udel_znamku(kurz, znamka)`: Zapíše známku do slovníku `_znamky`.
          * Před zápisem ověří, zda student daný kurz skutečně navštěvuje.
          * Ověří, zda je známka v intervalu 1–5.
      * `studijni_prumer`:
          * Definováno jako **property** (`@property`).
          * Vrací aritmetický průměr všech známek ve slovníku.
          * Pokud student nemá žádné známky, vrací hodnotu `0.0`.

-----

## Požadovaný výstup (Scénář pro testování)

Do bloku `if __name__ == "__main__":` vložte kód, který demonstruje funkčnost systému v následujících krocích:

1.  Vytvořte instanci kurzu (např. "Programování") s kapacitou nastavenou na **2 studenty**.
2.  Vytvořte **3 různé instance studentů**.
3.  Pokuste se všechny 3 studenty zapsat do vytvořeného kurzu.
      * Očekávané chování: První dva se zapíší, u třetího program vypíše chybovou hlášku zachycenou z výjimky (program nespadne).
4.  Zkuste zapsat studenta do kurzu podruhé (ověření duplicity).
5.  Udělte zapsaným studentům známky. Zkuste udělit známku i z předmětu, kam student nechodí.
6.  Vypište finální informace o studentech pomocí `print()`, včetně jejich studijního průměru.

### Příklad očekávaného výstupu v konzoli:

```text
Zapisuji studenta Novák... OK
Zapisuji studenta Svoboda... OK
Zapisuji studenta Dvořák... CHYBA: Kapacita kurzu IT101 je naplněna!

--- Výpis studentů ---
Student: Novák (12345), Průměr: 1.0, Zapsáno kurzů: 1
Student: Svoboda (67890), Průměr: 2.5, Zapsáno kurzů: 1
Student: Dvořák (11111), Průměr: 0.0, Zapsáno kurzů: 0
```