# Projekt Gutenberg: Analýza R.U.R. pomocí Regexu

V tomto projektu budeme analyzovat text klasického díla Karla Čapka - **R.U.R.**. Cílem je procvičit si práci se soubory a především **regulární výrazy** v praxi.

## Krok 1: Získání dat

Jelikož C++ standardně neumí stahovat soubory z internetu, musíme si text knihy připravit ručně.

Použijeme text z projektu Gutenberg (Plain Text UTF-8).

### Ruční stažení

1.  Otevřete v prohlížeči: [https://www.gutenberg.org/cache/epub/13083/pg13083.txt](https://www.google.com/url?sa=E&source=gmail&q=https://www.gutenberg.org/cache/epub/13083/pg13083.txt)
2.  Zkopírujte celý text (Ctrl+A, Ctrl+C).
3.  Vytvořte ve složce projektu nový soubor `kniha.txt`.
4.  Vložte text a uložte.

## Krok 2: Úkoly pro analýzu (C++)

V souboru `main.cpp` implementujte následující funkce pomocí knihovny `<regex>`:

1.  **`analyzujRoboty`**: Zjistěte, kolikrát se v textu vyskytuje slovo, které má kořen "Robot" (např. Robot, Roboti, Robota, Robotům...).
      * *Hledejte slovo začínající na "Robot" následované libovolnými písmeny.*
2.  **`najdiPrimouRec`**: Vypište prvních 5 vět, které jsou v uvozovkách.
      * *Tip: Pozor na různé typy uvozovek v textu. V Gutenberg textech bývají často standardní anglické `"`.*
3.  **`najdiLetopocty`**: Najděte a vypište všechny letopočty (čtyřciferná čísla) v textu.
4.  **`najdiPostavy`**: Pokuste se najít všechny postavy (jména), která v textu mluví. Ve scénářích divadelních her je to obvykle formát `JMENO:` nebo `JMENO.` na začátku řádku (velkými písmeny).


