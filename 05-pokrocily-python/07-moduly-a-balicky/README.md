# **07 - Moduly a separace kódu**

Jakmile váš program přesáhne několik desítek řádků, je nutné ho rozdělit do více souborů. V Pythonu k tomu používáme **moduly** a **balíčky**.

Separace kódu má několik výhod:

1. **Přehlednost:** V `main.py` zůstane jen hlavní logika, pomocné funkce a třídy jsou bokem.  
2. **Znovupoužitelnost:** Modul s matematickými funkcemi můžete použít ve více projektech.  
3. **Namespace (Jmenný prostor):** Funkce `save()` v modulu pro databázi se nepohádá s funkcí `save()` v modulu pro soubory.

## **1. Modul (Module)**

Modul je jakýkoliv soubor s příponou `.py`.  
Pokud máme soubor `matematika.py`, vytvořili jsme modul `matematika`.

## **2. Importování**

Abychom mohli kód z jiného souboru použít, musíme ho **importovat**.

```python
# A) Import celého modulu  
import matematika  
print(matematika.PI)  # Musíme používat tečkovou notaci

# B) Import konkrétní funkce/třídy  
from matematika import PI, vypocitej  
print(PI)  # Používáme přímo

# C) Import s přejmenováním (Alias)  
import matematika as m  
print(m.PI)  # Užitečné u dlouhých názvů knihoven (např. import pandas as pd)
```

## **3. Konstrukce `if __name__ == "__main__":`**

Toto je jedna z nejdůležitějších konstrukcí v Pythonu.  
Každý modul má vestavěnou proměnnou `__name__`.

* Pokud soubor spouštíme přímo (např. tlačítkem Play), `__name__` se nastaví na "__main__".  
* Pokud soubor importujeme do jiného, `__name__` se nastaví na název souboru (např. `"matematika"`).

Díky této podmínce můžeme do modulu napsat testovací kód, který se provede **jen když modul spustíme přímo**, ale **neprovede se**, když ho importujeme jinde.

```python
# Soubor: pozdrav.py

def ahoj():  
    print("Ahoj!")

if __name__ == "__main__":  
    # Toto se provede jen při přímém spuštění pozdrav.py  
    ahoj()
```

## **4. Balíček (Package)**

Balíček je **složka**, která obsahuje moduly. Aby Python věděl, že složka je balíček, měla by obsahovat soubor `__init__.py` (v novějších verzích Pythonu to není striktně nutné, ale je to dobrá praxe).

**Struktura projektu:**

```python
muj_projekt/  
│  
├── main.py             <-- Vstupní bod aplikace  
└── utils/              <-- Balíček (složka)  
    ├── __init__.py     <-- Inicializační soubor  
    ├── database.py     <-- Modul A  
    └── email.py        <-- Modul B
```

### **Absolutní vs. Relativní importy**

Při importování v rámci balíčků rozlišujeme dva přístupy.

#### **A) Absolutní cesta (Doporučeno pro začátečníky)**

Vždy specifikujeme celou cestu od kořenového adresáře projektu (tam, kde spouštíme python). Je to čitelnější a méně náchylné k chybám.

*Příklad:* Chceme v utils/email.py použít funkci z utils/database.py.

```python
# Soubor: utils/email.py  
from utils.database import uloz_log  # Plná cesta od kořene
```

#### **B) Relativní cesta**

Používá tečky k navigaci ve struktuře složek (podobně jako v příkazové řádce `cd ..`).

* `.` = aktuální balíček  
* `..` = nadřazený balíček

*Příklad:*

```python
# Soubor: utils/email.py  
from .database import uloz_log  # Tečka říká: hledej ve stejné složce jako jsem já
```

**Častá chyba:** Relativní importy fungují **POUZE** tehdy, pokud kód spouštíte jako balíček (např. z main.py). Pokud spustíte přímo soubor `utils/email.py` tlačítkem Play, Python neví, co je "nadřazená složka", a vyhodí chybu `ImportError: attempted relative import with no known parent package`.

## **5. Cyklické závislosti (Circular Imports)**

Tohle je častý problém při návrhu aplikace. Nastane, když dva moduly importují jeden druhého.

**Scénář:**

1. Modul **A** potřebuje modul **B**.  
2. Modul **B** potřebuje modul **A**.

```python
# soubor: hrac.py  
from hra import game_over  # Hráč potřebuje funkci z hry

def zautoc():  
    if zdravi <= 0:  
        game_over()
```

```python
# soubor: hra.py  
from hrac import zautoc    # Hra potřebuje funkci z hráče

def spust_hru():  
    zautoc()
```

Když Python načítá `hrac.py`, narazí na import `hra`. Jde načíst `hra.py`, ale tam narazí na import `hrac`. Zacyklí se a vyhodí `ImportError` (často matoucí hláškou o tom, že něco není definováno).

### **Jak se tomu vyhnout?**

1. Restrukturalizace (Nejlepší řešení):  
   Vytvořte třetí, společný modul (např. `spolecne.py` nebo `config.py`), kam přesunete sdílené konstanty nebo logiku. Oba původní moduly pak importují z tohoto třetího.  
   * `hrac` importuje `spolecne`  
   * `hra` importuje `spolecne`  
   * Nikdo neimportuje nikoho navzájem.  
2. Import uvnitř funkce/metody:  
   Pokud import přesunete dovnitř funkce, provede se až ve chvíli zavolání, nikoliv při startu programu. Tím se kruh rozpojí.  
   ```python
   # soubor: hrac.py  
   def zautoc():  
       # Import se provede až tady, kdy už je modul 'hra' pravděpodobně načtený  
       from hra import game_over   
       game_over()  
    ```
---
## **Cvičení**

### **1. Vlastní modul**
1. Vytvořte soubor `geometrie.py`, do kterého umístíte funkci `obvod_kruhu(r)`. Přidejte do něj blok `if __name__ == "__main__":`, který funkci otestuje výpisem.
2. Vytvořte soubor `hlavni.py`, který importuje `geometrie` a zavolá `obvod_kruhu`.
3. Spusťte `hlavni.py` a ověřte, že se nevypisuje testovací kód z `geometrie.py`.

### **2. Import specific**
V souboru `hlavni.py` upravte import tak, abyste mohli volat funkci přímo jako `obvod_kruhu(5)` (bez tečkové notace).
