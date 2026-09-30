# **04 - Základy jazyka Python**

Tato sekce se zaměřuje na úvod do programovacího jazyka **Python**. Python je vysokoúrovňový interpretovaný jazyk, který klade důraz na čitelnost kódu.

## **Vývojové prostředí (DevContainer)**

Tento repozitář je nakonfigurován jako **DevContainer**. To znamená, že máte připravené kompletní prostředí pro vývoj bez nutnosti cokoliv instalovat do svého počítače.

**Co máte k dispozici:**

* **Python 3.x** - Interpret jazyka je již nainstalován.  
* **VS Code Extensions** - Doplňky pro Python, Jupyter Notebooky a lintery jsou aktivní.  
* **Terminál** - Příkazová řádka je integrovaná přímo v editoru.

## **Jak pracovat s materiály**

V každé složce naleznete tři typy souborů:

1. README.md - Teorie k danému tématu.  
2. main.py - Ukázkový skript.  
3. teorie.ipynb - Interaktivní sešit (Jupyter Notebook).

### **Možnost A: Spouštění Python skriptů (.py)**

Jelikož jste ve VS Code, máte dvě snadné možnosti:

1. **Tlačítko Play:** Otevřete soubor main.py a klikněte na ikonu "Play" v pravém horním rohu editoru. Kód se spustí v terminálu.  
2. **Terminál:** Otevřete terminál (zkratka Ctrl + ; nebo menu Terminal -> New Terminal) a napište:

   ```bash
   python cesta/k/souboru/main.py
   ```

### **Možnost B: Interaktivní sešity (.ipynb)**

Jupyter Notebooky umožňují spouštět kód po částech (buňkách) a vidět výsledek okamžitě pod nimi.

1. Otevřete soubor s koncovkou .ipynb.  
2. VS Code automaticky načte rozhraní pro notebooky (pokud se zeptá na "Kernel", zvolte **Python 3** nebo **Recommended**).  
3. Kliknutím na tlačitko spustit vlevo u každé buňky spustíte daný kus kódu.

## **Obsah sekce**

| Kapitola | Téma | Popis | Stav |
| :--- | :--- | :--- | :---: |
| 1. [Syntaxe, výstup a komentáře](./01-syntaxe-komentare/) | Základní syntaxe | Výpis do konzole (`print`), komentáře, struktura skriptu | Hotovo |
| 2. [Proměnné a datové typy](./02-proměnné-datové-typy/) | Datové typy a f-stringy | Dynamické typování, skalární typy, přetypování, moderní f-stringy | Hotovo |
| 3. [Operátory](./03-operatory/) | Operátory | Aritmetické, logické, porovnávací a přiřazovací operátory | Hotovo |
| 4. [Podmínky a větvení](./04-podmínky-větvení/) | Řízení toku | Konstrukce `if-elif-else`, logické výrazy, ternární operátor | Hotovo |
| 5. [Cykly](./05-cykly/) | Iterace | Cykly `for` a `while`, funkce `range`, `break`, `continue`, `else` u cyklů | Hotovo |
| 6. [Datové struktury](./06-datove-struktury/) | Kolekce | Seznamy (`list`), n-tice (`tuple`), slovníky (`dict`), množiny (`set`), list comprehension | Hotovo |
| 7. [Práce se soubory](./07-prace-se-soubory/) | Text, CSV a JSON | Kontextový manažer `with`, práce s textovými soubory<br>*Bude doplněno:* formát **CSV** (modul `csv`, `DictReader`) a formát **JSON** (modul `json`) | Rozpracováno |
| 8. [Funkce](./08-funkce/) | Funkce a scope | Definice funkcí, parametry, návratové hodnoty, `*args`, `**kwargs`, lambda funkce, lokální a globální scope | Hotovo |