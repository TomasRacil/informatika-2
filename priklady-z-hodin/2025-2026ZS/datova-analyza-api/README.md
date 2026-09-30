# Cvičení: Analýza dat z API (Binance)

V tomto cvičení si vyzkoušíme reálnou práci s daty. Stáhneme si aktuální data o kryptoměnách z veřejného API burzy Binance, zpracujeme je knihovnou **Pandas** a vizualizujeme pomocí **Matplotlib**.

## Cíl cvičení
1.  Pochopit, jak získat data z internetu pomocí knihovny `requests`.
2.  Naučit se základní manipulaci s `pandas.DataFrame` (vytvoření, převod typů, filtrování, řazení).
3.  Vykreslit základní graf pro vizualizaci dat.

## Příprava prostředí

```bash
# Vytvoření venv (pokud ještě nemáte)
python3 -m venv .venv
source .venv/bin/activate  # na Windows: .venv\Scripts\activate

# Instalace knihoven
pip install pandas requests matplotlib jupyter
```

---

## Rychlý úvod do použitých knihoven

### 1. Requests (Komunikace s webem)
Knihovna pro posílání HTTP požadavků. Pro nás je klíčová metoda `GET`, která "stáhne" stránku nebo data z API.

-   **`requests.get(url)`**: Pošle požadavek na danou URL. Vrací objekt `Response`.
-   **`response.status_code`**: Číselný kód výsledku (200 = OK, 404 = Nenalezeno).
-   **`response.json()`**: Pokud server vrací data ve formátu JSON (což API dělají), tato metoda je převede na Python slovníky a seznamy.

### 2. Pandas (Práce s daty)
Nejpoužívanější knihovna pro analýzu dat v Pythonu. Hlavním objektem je **DataFrame** (tabulka).

-   **`pd.DataFrame(data)`**: Vytvoří tabulku ze seznamu slovníků.
-   **`df.head(n)`**: Zobrazí prvních *n* řádků tabulky.
-   **`df.info()`**: Zobrazí informace o sloupcích (názvy a datové typy).
-   **`df['sloupec']`**: Vybere konkrétní sloupec (vrací tzv. Series).
-   **`df.astype(float)`**: Převede data ve sloupci na desetinná čísla (z API často chodí jako text).
-   **`df[podminka]`**: Filtrování. Např. `df[df['cena'] > 100]` vybere jen řádky, kde cena > 100.
-   **`df.sort_values('sloupec')`**: Seřadí tabulku podle sloupce.

### 3. Matplotlib (Grafy)
Knihovna pro vizualizaci.

-   **`plt.bar(x, y)`**: Vykreslí sloupcový graf.
-   **`plt.xlabel('popis')`**: Popisek osy X.
-   **`plt.title('Nadpis')`**: Nadpis grafu.
-   **`plt.show()`**: Zobrazí výsledný graf.

---

## Zadání

1.  Otevřete soubor `zadani.ipynb` ve VS Code (nebo spusťte `jupyter notebook`).
2.  Postupujte podle instrukcí v notebooku.

### Hinty k API
-   **API Endpoint**: `https://api.binance.com/api/v3/ticker/24hr`
-   **Offline verze**: Pokud nemáte přístup k internetu, použijte přiložený soubor `coins.json`. Data načtěte příkazem `data = json.load(open('coins.json'))`.
-   **Struktura dat**: Binance vrací seznam, kde každý prvek je jedna kryptoměna.
    -   `symbol`: Např. "BTCUSDT"
    -   `lastPrice`: Poslední cena (jako text!)
    -   `quoteVolume`: Objem obchodů v druhé měně páru (pro BTCUSDT je to objem v USDT).
