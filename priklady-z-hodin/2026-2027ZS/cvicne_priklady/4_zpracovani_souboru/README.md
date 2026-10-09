### Úkol 4: Zpracování a agregace souborů (40 min)

Napište skript pro zpracování souboru se záznamy přístupů `pristupy.csv`.

**Formát vstupního souboru (`pristupy.csv`):**

```text
cas;cesta;kod;velikost
10:14:02;/api/data;200;1420
10:14:05;/login;401;320
10:15:11;/api/data;200;8900
10:16:40;/admin;403;150
10:17:00;/api/users;500;0

```

**Požadavky:**

* Otevřete soubor pomocí kontextového manažeru `with open(...) as f:`.
* Procházejte soubor po řádcích (bez načtení celého obsahu do paměti).
* Spočítejte:
    1. Celkový objem přenesených dat (součet sloupce `velikost` pouze pro záznamy s kódem `200`).
    2. Počet chybových kódů (kódy začínající na `4` nebo `5`).
    3. Počet volání jednotlivých endpointů (sloupec `cesta`).


* Výsledky zapište do nového souboru `vystup.txt`.
