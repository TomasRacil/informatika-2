# **Práce se soubory v Pythonu**

Schopnost číst ze souborů a zapisovat do nich je nezbytná pro ukládání výsledků programu, načítání konfigurací nebo zpracování velkých datových sad. Python k tomu používá vestavěnou funkci open().

## **Základní syntaxe**

```python
file = open("soubor.txt", mode="r", encoding="utf-8")  
# ... práce se souborem ...  
file.close() # DŮLEŽITÉ: Soubor se musí zavřít!
```

### **Módy otevření (Modes)**

Tento argument určuje, co se souborem budeme dělat:

| Mód | Popis | Chování když soubor neexistuje | Chování když existuje |
| :---- | :---- | :---- | :---- |
| `'r'` | **Read** (čtení) - výchozí | Vyhodí chybu `FileNotFoundError` | Čte od začátku |
| `'w'` | **Write** (zápis) | Vytvoří nový soubor | **Smaže obsah a přepíše ho!** |
| `'a'` | **Append** (přidání) | Vytvoří nový soubor | Píše na konec souboru |
| `'x'` | **Exclusive creation** | Vytvoří nový soubor | Vyhodí chybu `FileExistsError` |

## **Kontextový manažer (`with`) - Best Practice**

V praxi se málokdy používá `file.close()`. Místo toho používáme blok `with`. Ten zajistí, že se soubor **vždy bezpečně zavře**, i když v programu nastane chyba.

```python
# Správný a bezpečný způsob:  
with open("data.txt", "w", encoding="utf-8") as f:  
    f.write("Ahoj světe")  
# Zde už je soubor zavřený
```

**Důležité:** Vždy specifikujte `encoding="utf-8"`, pokud pracujete s češtinou, jinak se vám mohou špatně zobrazovat znaky jako ě, š, č, ř.

## **Čtení ze souboru**

Máme několik možností, jak získat data ze souboru:

1. **`read()`** – Přečte celý soubor jako jeden velký string.
   ```python
   content = f.read()
   ```

2. **`readline()`** – Přečte vždy jen jeden řádek (a posune kurzor na další).  
3. **`readlines()`** – Přečte všechny řádky a vrátí je jako **seznam** stringů.  
4. **Iterace v cyklu** – Nejefektivnější pro velké soubory.
   ```python  
   for radek in f:  
       print(radek.strip()) # .strip() odstraní neviditelné znaky konců řádků
   ```

## **Zápis do souboru**

* **`write(string)`** – Zapíše řetězec. Pozor: nepřidává automaticky nový řádek `\n`, musíte ho tam dopsat ručně.  
* **`writelines(list)`** – Zapíše seznam stringů.
---
## **Cvičení**

### **1. Zápis**
Vytvořte program, který vytvoří soubor `basnicka.txt` a zapíše do něj 4 verše nějaké básně (každý na nový řádek).

### **2. Čtení**
Otevřete soubor `basnicka.txt` (z předchozího úkolu) a vypište jeho obsah do konzole tak, že před každý řádek přidáte **odrážku** (`-> `).

### **3. Přidávání**
Otevřete soubor `basnicka.txt` v režimu `append` a přidejte na konec ještě jeden řádek (podpis autora).
