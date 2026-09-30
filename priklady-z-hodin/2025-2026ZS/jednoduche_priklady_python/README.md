## **Úloha 1: Interaktivní analyzátor čísel**
**Cíl:** Vstup uživatele, `while`, seznamy.

1. Napište program, který opakovaně čte čísla od uživatele.
2. Pokud uživatel zadá **"stop"**, program skončí.
3. Všechna zadaná čísla uložte do seznamu.
4. Vytvořte funkci `vypis_statistiku(seznam)`, která vypíše:
   - Součet, největší a nejmenší číslo.
   - Počet sudých a lichých čísel.
   - Průměrnou hodnotu.

---

## **Úloha 2: Frekvenční analýza textu**
**Cíl:** Řetězce, slovníky (`dict`), cyklus `for`.

1. Napište funkci `spocitej_znaky(text)`, která přijme libovolný řetězec.
2. Funkce vrátí **slovník**, kde klíčem je znak a hodnotou počet jeho výskytů (např. `{'a': 5, 'b': 2}`).
3. **Podmínky:**
   - Nerozlišujte velká a malá písmena (převeďte vše na malé).
   - Ignorujte mezery.

---

## **Úloha 3: Evidence studentů**
**Cíl:** Vnořené struktury (slovník v seznamu), funkce.

1. Vytvořte prázdný seznam `studenti`.
2. Napište funkci `pridej_studenta(jmeno, znamky)`, která přidá studenta do seznamu ve formátu:
   `{"jmeno": "Jan", "znamky": [1, 2, 3]}`.
3. Přidejte alespoň 3 studenty.
4. Napište funkci `nejlepsi_student(seznam_studentu)`, která najde a vypíše jméno studenta s nejlepším (nejnižším) průměrem známek.

---

## **Úloha 4: Filtrování logů**
**Cíl:** Práce se soubory (`open`, `with`), zápis dat.

1. Vytvořte soubor `system.log` s několika řádky textu (obsahující slova `INFO`, `WARNING`, `ERROR`).
2. Napište skript, který:
   - Načte soubor `system.log`.
   - Vyfiltruje pouze řádky obsahující slovo **ERROR**.
   - Zapíše tyto řádky do nového souboru `errors_only.txt`.

---

## **Úloha 5: Caesarova šifra**
**Cíl:** Práce s ASCII kódy (`ord`, `chr`) nebo abecedou, modulo aritmetika.

1. Napište funkci `sifruj(text, posun)`, která zašifruje vstupní text posunem písmen v abecedě.
   - Příklad: `sifruj("abc", 1)` -> `"bcd"`
2. **Požadavky:**
   - Pokud posun přesáhne konec abecedy, musí začít znovu od 'a' (např. 'z' + 1 -> 'a').
   - Zachovejte velikost písmen (velká zůstanou velká).
   - Znaky, které nejsou písmena (mezery, tečky), nechejte beze změny.