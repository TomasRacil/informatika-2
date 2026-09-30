# **05 - Pokročilý Python**

Tato sekce vás posune od psaní jednoduchých skriptů k tvorbě **profesionálních, robustních a udržovatelných aplikací**.

Kromě **Objektově Orientovaného Programování (OOP)**, které je nezbytné pro větší projekty, se zaměříme i na nástroje pro **efektivitu kódu** (dekorátory), **bezpečnost** (správa chyb), **monitorování** (logování) a **správu prostředí**. Cílem je naučit se psát Python kód tak, jak se píše v reálné praxi.

## **Vývojové prostředí (DevContainer)**

Tento repozitář je nakonfigurován jako **DevContainer**. To znamená, že máte připravené kompletní prostředí pro vývoj bez nutnosti cokoliv instalovat do svého počítače.

**Co máte k dispozici:**

* **Python 3.x** - Interpret jazyka je již nainstalován.  
* **VS Code Extensions** - Doplňky pro Python, Jupyter Notebooky a lintery jsou aktivní.  
* **Terminál** - Příkazová řádka je integrovaná přímo v editoru.

## **Jak pracovat s materiály**

V každé složce naleznete tři typy souborů:

1. `README.md` - Teorie k danému tématu.  
2. `main.py` - Ukázkový skript.  
3. `teorie.ipynb` - Interaktivní sešit (Jupyter Notebook).

### **Možnost A: Spouštění Python skriptů (.py)**

Jelikož jste ve VS Code, máte dvě snadné možnosti:

1. **Tlačítko Play:** Otevřete soubor `main.py` a klikněte na ikonu "Play" v pravém horním rohu editoru. Kód se spustí v terminálu.  
2. **Terminál:** Otevřete terminál (zkratka `Ctrl + ;` nebo menu *Terminal -> New Terminal*) a napište:
   ```bash
   python cesta/k/souboru/main.py
   ```

### **Možnost B: Interaktivní sešity (.ipynb)**

Jupyter Notebooky umožňují spouštět kód po částech (buňkách) a vidět výsledek okamžitě pod nimi.

1. Otevřete soubor s koncovkou `.ipynb`.  
2. VS Code automaticky načte rozhraní pro notebooky (pokud se zeptá na "Kernel", zvolte **Python 3** nebo **Recommended**).  
3. Kliknutím na tlačitko spustit vlevo u každé buňky spustíte daný kus kódu.

## **Obsah sekce**

| Kapitola | Téma | Popis | Stav |
| :--- | :--- | :--- | :---: |
| 1. [Type Hinting](./01-typing/) | Typové anotace | Typové anotace, modul `typing`, statická analýza kódu `mypy` | Hotovo |
| 2. [Úvod do tříd a objektů](./02-uvod-do-trid/) | Základy OOP | Třídy, instance, konstruktor `__init__`, parametr `self`, atributy | Hotovo |
| 3. [Modifikátory přístupu a Vlastnosti](./03-modifikatory-pristupu-a-vlastnosti/) | Zapouzdření | Privátní a chráněné atributy, dekorátor `@property`, gettery a settery | Hotovo |
| 4. [Dědičnost](./04-dedicnost/) | Dědičnost a polymorfismus | Odvozování tříd, funkce `super()`, přepisování metod | Hotovo |
| 4b. [Vícenásobná dědičnost](./04b-vicenasobna-dedicnost/) | Vícenásobná dědičnost | Dědění z více tříd, Method Resolution Order (MRO), mixiny | Hotovo |
| 5. [Abstraktní třídy](./05-abstraktni-tridy/) | Abstrakce a rozhraní | Modul `abc`, abstraktní bázové třídy `ABC`, dekorátor `@abstractmethod` | Hotovo |
| 6. [Magické metody](./06-magicke-metody/) | Dunder metody | `__str__`, `__repr__`, `__eq__`, `__len__`, `__getitem__`, přetěžování operátorů | Hotovo |
| 6b. **Moderní datové třídy** | Dataclasses | Modul `dataclasses`, dekorátor `@dataclass`, výchozí hodnoty, `frozen=True` | *Bude doplněno* |
| 7. [Moduly a balíčky](./07-moduly-a-balicky/) | Modularizace | Vlastní moduly a balíčky, `__init__.py`, importní systém | Hotovo |
| 8. [Dekorátory](./08-dekoratory/) | Funkcionální dekorátory | Funkce vyššího řádu, uzávěry (closures), dekorátory s parametry, `@functools.wraps` | Hotovo |
| 9. [Výjimky a Error Handling](./09-vyjimky/) | Ošetření chyb | Blok `try-except-else-finally`, hierarchie výjimek, tvorba vlastních výjimek | Hotovo |
| 10. [Logování](./10-logovani/) | Diagnostika a audit | Modul `logging`, úrovně (DEBUG, INFO, ERROR), formátovače, handlery | Hotovo |
| 11. [Regulární výrazy](./11-regularni-vyrazy/) | Textové vzory | Modul `re`, vyhledávací vzory, skupiny, validace a parsování textu | Hotovo |
| 11b. **Práce s REST API a sítí** | Síťová komunikace | Knihovna `requests`, HTTP metody (GET, POST), autorizace, JSON odpovědi | *Bude doplněno* |
| 11c. **Web Scraping** | Získávání dat z webu | Knihovna `BeautifulSoup4`, CSS selektory, parsování HTML stromu, etika scrapingu | *Bude doplněno* |
| 12. [Argumenty příkazové řádky](./12-argumenty-prikazove-radky/) | Tvorba CLI nástrojů | Modul `argparse`, poziční argumenty, přepínače, nápověda | Hotovo |
| 13. [Virtuální prostředí a balíčky](./13-prostredi-a-balicky/) | Správa prostředí | Izolovaná prostředí `venv`, instalátor `pip`, soubor `requirements.txt` | Hotovo |
| 13b. **Moderní Python tooling** | Tooling nové generace | Standard `pyproject.toml`, testování v `pytest` (fixtures, parametrizace), linter/formatter `ruff` | *Bude doplněno* |
| 14. [Generátory a Iterátory](./14-generatory-a-iteratory/) | Efektivní streamování | Protokol iterátoru (`__iter__`, `__next__`), klíčové slovo `yield`, paměťová úspora | Hotovo |
| 15. [Vložený kód](./15-vlozeny-kod/) | C/C++ rozšíření | Kompilace a volání nativních C/C++ modulů z Pythonu | Hotovo |
| 15b. **Ochutnávka vědeckého Pythonu** | Data Science úvod | Úvod do `NumPy` a `Pandas`, grafy v `Matplotlib`, základní myšlenka modelů v `scikit-learn` | *Bude doplněno* |

---

### **Témata přesunutá do navazujícího semestru**

Následující témata jsou připravena v repozitáři, ale v rámci tohoto semestru se neprobírají:

| Kapitola | Téma | Popis | Stav |
| :--- | :--- | :--- | :---: |
| 16. [Vlákna (Threading)](./16-vlakna/) | Vícevláknové programování | Modul `threading`, GIL, souběžný běh I/O operací | Přesunuto |
| 17. [Multiprocessing](./17-multiprocessing/) | Víceprocesorový běh | Modul `multiprocessing`, obcházení GILu, procesy, fronty | Přesunuto |
| 18. [Sdílení paměti](./18-sdilena-pamet/) | Meziprocesová komunikace | Modul `multiprocessing.shared_memory`, sdílení polí NumPy | Přesunuto |
| 19. [Klasické sockety](./19-klasicke-sockety/) | Nízkoúrovňová síť | Modul `socket`, TCP/UDP klient a server, blokující I/O | Přesunuto |
| 20. [Úvod do AsyncIO](./20-uvod-asyncio/) | Asynchronní programování | Event loop, klíčová slova `async` a `await`, asynchronní úlohy | Přesunuto |
| 21. [Síťová komunikace v AsyncIO](./21-sitova-komunikace-asyncio/) | Asynchronní síť | Asynchronní TCP/UDP servery a klienti, streamy | Přesunuto |
