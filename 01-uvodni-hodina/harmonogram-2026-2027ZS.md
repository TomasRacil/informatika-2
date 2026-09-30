# Harmonogram výuky – Informatika 2 (Zimní semestr 2026/2027)

Tento harmonogram pokrývá všech 44 vyučovacích bloků (po 90 minutách) předmětu Informatika 2.  
Výuka je zaměřena na jazyk **Python** s důrazem na:
1. **Jazykové základy a strukturovaná data** (syntaxe, kolekce, funkce, práce se soubory CSV a JSON).
2. **Robustní kód a objektový návrh** (type hints, výjimky, logging, argparse, OOP, `@dataclass`).
3. **Práci s externími daty** (REST API, knihovna `requests`, web scraping s `BeautifulSoup4`).
4. **Rozšířenou algoritmizaci** (rekurze, backtracking, řazení, spojové seznamy, stromy, grafy BFS/DFS/Dijkstra, dynamické programování, Advent of Code).
5. **Moderní Python tooling** (`pyproject.toml`, testování v `pytest`, linter a formatter `ruff`).
6. **Ochutnávku vědeckého Pythonu** (letmý úvod do `NumPy`, `Pandas` a konceptu strojového učení na závěr).
7. **Samostatné semestrální projekty** (zadání si studenti navrhují a specifikují sami) a přípravu na zkoušku.

---

| Datum | Čas | Učebna | Téma | Domácí úkoly |
| :--- | :--- | :---: | :--- | :--- |
| **30.09.2026** | 14:30 – 16:00 | Š8/20 | **Úvod do předmětu:** Organizace, pravidla zápočtu a zkoušky, Git & GitHub, odevzdávání přes PR, prostředí (Codespaces / Dev Container / venv) | Zadání: Úkol 0 (Hello World) |
| **01.10.2026** | 14:30 – 16:00 | Š8/20 | **Základy syntaxe Pythonu:** Interpret, dynamické typování, operátory, vstup a výstup (`print`, `input`), formátování textu (f-stringy) | |
| **02.10.2026** | 08:00 – 09:30 | Š8/20 | **Řídicí struktury:** Podmínky (`if-elif-else`), logické výrazy, cykly (`for`, `while`), funkce `range`, `break`, `continue` | **Deadline: Úkol 0**<br>Zadání: Úkol 1 |
| **09.10.2026** | 08:00 – 09:30 | Š8/20 | **Datové struktury I:** Seznamy (`list`) a n-tice (`tuple`), indexování, slicing, metody seznamů, list comprehension | |
| **09.10.2026** | 09:50 – 11:20 | Š8/20 | **Datové struktury II:** Slovníky (`dict`) a množiny (`set`), hashování, množinové operace, frekvenční analýza textu | **Deadline: Úkol 1**<br>Zadání: Úkol 2 |
| **14.10.2026** | 14:30 – 16:00 | Š8/20 | **Funkce v Pythonu:** Parametry, návratové hodnoty, variabilní argumenty `*args` a `**kwargs`, scope proměnných, lambda funkce | |
| **16.10.2026** | 08:00 – 09:30 | Š8/20 | **Práce se soubory a formáty:** Kontextový manažer `with`, práce s textovými soubory, parsování a ukládání formátů CSV a JSON | |
| **16.10.2026** | 09:50 – 11:20 | Š8/20 | **Praktické cvičení:** Zpracování, validace a transformace nestrukturovaných a polo-strukturovaných dat ze souborů | **Deadline: Úkol 2**<br>Zadání: Úkol 3 |
| **20.10.2026** | 14:30 – 16:00 | Š8/20 | **Typový systém a statická analýza:** Type hints, knihovna `typing`, statická typová kontrola pomocí nástroje `mypy` | |
| **22.10.2026** | 08:00 – 09:30 | Š8/20 | **Výjimky a ošetření chyb:** Blok `try-except-else-finally`, hierarchie výjimek, vyvolávání výjimek (`raise`), tvorba vlastních výjimek | |
| **23.10.2026** | 09:50 – 11:20 | Š8/20 | **Logování a CLI nástroje:** Modul `logging` (úrovně, formátovače, handlery) a modul `argparse` pro argumenty příkazové řádky | **Deadline: Úkol 3**<br>Zadání: Úkol 4 |
| **27.10.2026** | 14:30 – 16:00 | Š8/20 | **Objektově orientované programování (OOP) I:** Třídy a instance, konstruktor `__init__`, parametr `self`, instance vs. třídní atributy | |
| **30.10.2026** | 09:50 – 11:20 | Š8/20 | **OOP II – Zapouzdření:** Privátní a chráněné atributy (name mangling), dekorátor `@property`, gettery a settery | |
| **30.10.2026** | 11:40 – 13:10 | Š8/20 | **OOP III – Dědičnost a polymorfismus:** Odvozování tříd, funkce `super()`, abstraktní bázové třídy (`abc.ABC`, `@abstractmethod`) | **Deadline: Úkol 4**<br>Zadání: Úkol 5 |
| **03.11.2026** | 14:30 – 16:00 | Š8/20 | **OOP IV – Magické (dunder) metody:** `__str__`, `__repr__`, `__eq__`, `__len__`, `__getitem__`, přetěžování operátorů | |
| **06.11.2026** | 09:50 – 11:20 | Š8/20 | **OOP V – Moderní datové třídy:** Modul `dataclasses` (`@dataclass`, field defaults, frozen třídy), kompozice vs. dědičnost | |
| **06.11.2026** | 11:40 – 13:10 | Š8/20 | **Architektura aplikací a semestrální projekty:** Zásady návrhu, vyhlášení semestrálních projektů (vlastní specifikace studenty) | **Deadline: Úkol 5**<br>Zadání: Úkol 6 |
| **10.11.2026** | 14:30 – 16:00 | Š8/20 | **Iterátory a generátory:** Protokol iterace (`__iter__`, `__next__`), klíčové slovo `yield`, generátorové výrazy a streamování dat | |
| **13.11.2026** | 08:00 – 09:30 | Š8/20 | **Funkcionální prvky a dekorátory:** Funkce vyššího řádu, uzávěry (closures), tvorba vlastních dekorátorů s parametry, `@functools.wraps` | **Deadline: Úkol 6**<br>Zadání: Úkol 7 |
| **16.11.2026** | 11:40 – 13:10 | Š8/20 | **Regulární výrazy:** Modul `re`, vyhledávací vzory, skupiny (groups), validace a parsování strukturovaných textů | |
| **20.11.2026** | 08:00 – 09:30 | Š8/20 | **Práce se sítí a REST API:** Knihovna `requests`, HTTP metody (GET, POST), autorizace, zpracování JSON odpovědí a chyb | **Deadline: Úkol 7**<br>Zadání: Úkol 8 |
| **23.11.2026** | 11:40 – 13:10 | Š8/20 | **Web Scraping:** Získávání dat z webu, knihovna `BeautifulSoup4`, CSS selektory, parsování HTML stromu, etika scrapingu | |
| **24.11.2026** | 14:30 – 16:00 | Š8/20 | **Algoritmizace I – Asymptotická složitost:** Big O notace, analýza časové a prostorové náročnosti, profilování a měření v Pythonu | |
| **27.11.2026** | 08:00 – 09:30 | Š8/20 | **Algoritmizace II – Řazení a vyhledávání:** QuickSort, MergeSort, binární vyhledávání, porovnání s vestavěným Timsortem | **Deadline: Úkol 8**<br>Zadání: Úkol 9 |
| **30.11.2026** | 11:40 – 13:10 | Š8/20 | **Algoritmizace III – Rekurze a Backtracking:** Rekurzivní myšlení, Hanojské věže, backtracking (problém N dam, generování stavů) | |
| **03.12.2026** | 11:40 – 13:10 | Š8/20 | **Algoritmizace IV – Vlastní datové struktury:** Spojový seznam (Linked List), Zásobník (Stack), Fronta (Queue), prioritní fronta (`heapq`) | |
| **04.12.2026** | 09:50 – 11:20 | Š8/20 | **Algoritmizace V – Stromy a grafy I:** Reprezentace grafu (seznam sousedů), prohledávání grafu do šířky (BFS) a hloubky (DFS) | **Deadline: Úkol 9**<br>Zadání: Úkol 10 |
| **07.12.2026** | 11:40 – 13:10 | Š8/20 | **Algoritmizace VI – Grafy II:** Hledání nejkratší cesty v ohodnoceném grafu (Dijkstrův algoritmus), hledání cest v bludišti/síti | |
| **10.12.2026** | 11:40 – 13:10 | Š8/20 | **Algoritmizace VII – Dynamické programování a výzvy:** Memoizace (`@functools.cache`), tabulková metoda, úlohy typu Advent of Code | **Deadline: Úkol 10**<br>Zadání: Úkol 11 |
| *11.12.2026 – 03.01.2027* | — | — | *Vánoční prázdniny a samostatná práce na semestrálních projektech* | |
| **04.01.2027** | 09:50 – 11:20 | Š8/20 | **Moderní Python tooling I:** Správa projektů nové generace – `pyproject.toml`, virtuální prostředí (představení `uv` / `poetry` vs. `pip`) | |
| **05.01.2027** | 14:30 – 16:00 | Š8/20 | **Moderní Python tooling II – Profesionální testování:** Knihovna `pytest` (rozdíly oproti `unittest`, psaní testů, fixtures, parametrizace) | |
| **06.01.2027** | 08:00 – 09:30 | Š8/20 | **Moderní Python tooling III – Code Quality:** Ultrarychlý linter a formatter `ruff`, statická kontrola, pre-commit hooky | |
| **07.01.2027** | 08:00 – 09:30 | Š8/20 | **Vědecký Python (Ochutnávka) I:** Základy `NumPy` a `Pandas` – vícerozměrná pole, DataFrames, načtení a agregace dat | **Deadline: Úkol 11** |
| **11.01.2027** | 09:50 – 11:20 | Š8/20 | **Vědecký Python (Ochutnávka) II:** Vizualizace v `Matplotlib` a ochutnávka Machine Learning (princip modelu v `scikit-learn`) | |
| **11.01.2027** | 11:40 – 13:10 | Š8/20 | **Konzultace k semestrálním projektům I:** Kontrola architektury, ladění kódu, konzultace studentských specifikací | |
| **12.01.2027** | 14:30 – 16:00 | Š8/20 | **Příprava na zkoušku I:** Rozbor typických zkouškových úloh, algoritmické cvičení v časovém limitu | |
| **13.01.2027** | 08:00 – 09:30 | Š8/20 | **Příprava na zkoušku II:** Vzorová praktická zkouška nanečisto s okamžitým rozborem řešení a častých chyb | |
| **14.01.2027** | 11:40 – 13:10 | Š8/20 | **Konzultace k semestrálním projektům II:** Finální ladění projektů a příprava na obhajoby | |
| **15.01.2027** | 08:00 – 09:30 | Š8/20 | **Odevzdání semestrálních projektů a Obhajoby I:** Zahájení prezentací a ústních obhajob | **Odevzdání semestrálních projektů** |
| **18.01.2027** | 08:00 – 09:30 | Š8/20 | **Obhajoby semestrálních projektů II:** Prezentace a obhajoby projektů | |
| **19.01.2027** | 11:40 – 13:10 | Š8/20 | **Obhajoby semestrálních projektů III:** Prezentace a obhajoby projektů | |
| **20.01.2027** | 08:00 – 09:30 | Š8/20 | **Obhajoby semestrálních projektů IV:** Prezentace a obhajoby projektů | |
| **20.01.2027** | 11:40 – 13:10 | Š8/20 | **Závěrečné shrnutí semestru:** Rekapitulace zkouškových požadavků, vyhodnocení, zápis zápočtů | **Zápis zápočtů** |
| **21.01.2027** | 08:00 – 09:30 | Š8/20 | **Předtermín zkoušky / Rezerva:** Řádný předtermín zkoušky a rezervní prostor | |
