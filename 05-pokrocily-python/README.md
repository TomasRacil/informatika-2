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

1. [Type Hinting (Typové anotace)](./01-typing/) 
2. [Úvod do tříd a objektů](./02-uvod-do-trid/)  
3. [Modifikátory přístupu a Vlastnosti](./03-modifikatory-pristupu-a-vlastnosti/)  
4. [Dědičnost](./04-dedicnost/)  
4b. [Vícenásobná dědičnost](./04b-vicenasobna-dedicnost/)
5. [Abstraktní třídy a Polymorfismus](./05-abstraktni-tridy/)
6. [Magické metody](./06-magicke-metody/)
7. [Moduly a balíčky](./07-moduly-a-balicky/)
8. [Dekorátory](./08-dekoratory/)
9. [Výjimky a Error Handling](./09-vyjimky/)
10. [Logování](./10-logovani/)
11. [Regulární výrazy](./11-regularni-vyrazy/)
12. [Argumenty příkazové řádky (CLI)](./12-argumenty-prikazove-radky/)
13. [Virtuální prostředí a správa balíčků](./13-prostredi-a-balicky/)
14. [Generatory a Iteratory](./14-generatory-a-iteratory/)
15. [Vložený kód (Rozšíření v C++)](./15-vlozeny-kod/)
16. [Vlákna (Threading)](./16-vlakna/)
17. [Multiprocessing (Více procesů)](./17-multiprocessing/)
18. [Sdílení paměti](./18-sdilena-pamet/)
19. [Klasické sockety (Blocking I/O)](./19-klasicke-sockety/)
20. [Úvod do AsyncIO](./20-uvod-asyncio/)
21. [Síťová komunikace v AsyncIO](./21-sitova-komunikace-asyncio/)
