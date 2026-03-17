# **15 - Vložený kód (Extending Python with C)**

Python je skvělý pro rychlý vývoj, ale může být pomalý při náročných výpočtech (např. zpracování obrazu, kryptografie, maticové operace). V takových případech se používá tzv. **rozšíření (extension)** v jazyce C nebo C++.

Většina slavných knihoven (NumPy, TensorFlow, Pandas) je napsaná tímto způsobem. Python slouží jen jako "ovladač" pro rychlé jádro v C/C++.

## **Jak to funguje?**

1. Napíšeme kód v **C/C++**.  
2. Přidáme speciální **"wrapper" funkce** pomocí hlavičkového souboru `Python.h`. Tyto funkce slouží jako most – překládají Python objekty (`PyObject`) na C typy (`int`, `char*`) a naopak.  
3. Kód **zkompilujeme** do sdílené knihovny (`.so` na Linuxu, `.pyd` na Windows).  
4. V Pythonu knihovnu jednoduše naimportujeme (`import muj_modul`).

## **Python C API**

Základem je knihovna `Python.h`, která zpřístupňuje interní struktury interpretu Pythonu.

### **Klíčové funkce**

* `PyArg_ParseTuple(args, "i", &x)`: Převezme argumenty z Pythonu a uloží je do C proměnných. Formát `"i"` znamená integer, `"s"` string atd.  
* `Py_BuildValue("i", vysledek)`: Zabalí C výsledek zpět do Python objektu.

## **Kompilace (`setup.py`)**

Python má standardní nástroj `setuptools` pro kompilaci rozšíření.

```python
from setuptools import setup, Extension

modul = Extension('nazev_modulu', sources=['soubor.c'])

setup(ext_modules=[modul])
```

Příkaz pro kompilaci (vytvoří soubor přímo ve složce):

```shell
python3 setup.py build_ext --inplace
```

## **Alternativy**

Psaní čistého C API je pracné. Existují modernější nástroje:

* **Cython:** Píšete kód podobný Pythonu, který se přeloží do C.  
* **pybind11:** Moderní C++ knihovna pro velmi snadné propojení C++ a Pythonu.  
* **ctypes / cffi:** Umožňuje volat existující C knihovny bez nutnosti kompilace wrapperu.
---
## **Cvičení**

### **1. Cílová rovinka (C kód)**
Vytvořte soubor `mymath.c`. Napište v něm funkci v jazyce C, která přijme dvě celá čísla a vrátí jejich součin.
Přidejte nezbytný "boilerplate" kód (pomocí `Python.h`), abyste tuto funkci vystavili jako modul `mymath`.

### **2. Kompilace a Test**
Vytvořte soubor `setup.py` pro kompilaci vašeho modulu `mymath`.
1. Spusťte build (`python setup.py build_ext --inplace`).
2. Vytvořte skript `test.py`, který importuje `mymath`, zavolá vaši funkci a vypíše výsledek.
