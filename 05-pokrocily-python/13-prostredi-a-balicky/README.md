# **13 - Virtuální prostředí a správa balíčků**

Při práci na více projektech narazíte na problém zvaný **"Dependency Hell"** (Peklo závislostí).

* Projekt A potřebuje knihovnu `requests` ve verzi 1.0.  
* Projekt B potřebuje knihovnu `requests` ve verzi 2.0.

Pokud instalujete knihovny globálně do systému, nemůžete mít obě verze najednou. Řešením jsou **virtuální prostředí**.

## **1. Virtuální prostředí (`venv`)**

Virtuální prostředí je izolovaná složka, která obsahuje vlastní kopii Python interpretu a vlastní složku pro knihovny (`site-packages`).

### **Jak vytvořit venv (Terminál)**

```python
# Windows  
python -m venv .venv

# Linux / Mac  
python3 -m venv .venv
```

Příkaz vytvoří složku `.venv` (název je volitelný, ale `.venv` je standard).

### **Jak aktivovat venv**

Po vytvoření musíme terminálu říct, aby používal tento Python místo systémového.

* **Windows (PowerShell):** `.venvScriptsActivate.ps1`  
* **Windows (CMD):** `.venvScriptsactivate.bat`  
* **Linux / Mac:** `source .venv/bin/activate`

Po aktivaci uvidíte v příkazové řádce `(.venv)`.

## **2. Správce balíčků (pip)**

`pip` (Pip Installs Packages) je nástroj pro stahování knihoven z [PyPI (Python Package Index)](https://pypi.org).

**Důležité upozornění:** V posledních verzích Pythonu (a mnoha Linuxových distribucích) je z bezpečnostních důvodů často **zakázáno instalovat balíčky globálně** (chyba `error: externally-managed-environment`). Systém vás tím nutí používat virtuální prostředí, aby nedošlo k poškození systémových nástrojů, které na Pythonu závisí.

### **Základní příkazy**

* `pip install nazev_balicku` - Nainstaluje nejnovější verzi.  
* `pip list` - Zobrazí nainstalované balíčky.  
* `pip uninstall nazev_balicku` - Odinstaluje balíček.

## **3. Soubor `requirements.txt`**

Abychom mohli projekt sdílet s ostatními (kteří nemají naši složku `.venv`), musíme vytvořit seznam závislostí.

### **Vytvoření seznamu (Freeze)**

Uloží aktuální stav prostředí do souboru:

```shell
pip freeze > requirements.txt
```

### **Instalace ze seznamu**

Když si někdo stáhne váš projekt, vytvoří si prázdný venv a spustí:

```shell
pip install -r requirements.txt
```

Tím se nainstalují přesně ty verze knihoven, které projekt potřebuje.
---
## **Cvičení**

### **1. Manifest (Teorie)**
Vytvořte textový soubor `requirements.txt`, který byste použili pro projekt, jenž vyžaduje:
- Knihovnu `requests` přesně ve verzi `2.28.1`.
- Knihovnu `flask` v jakékoliv verzi.

### **2. Příkazy (Teorie)**
Napište sérii příkazů pro Linux, které:
1. Vytvoří virtuální prostředí.
2. Aktivují ho.
3. Nainstalují balíček `numpy`.
