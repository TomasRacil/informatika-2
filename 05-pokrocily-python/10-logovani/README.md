# **10 - Logování (Logging)**

Až dosud jsme pro zjišťování stavu programu používali funkci `print()`. U malých skriptů to stačí, ale u větších aplikací je to špatná praxe.

**Proč nepoužívat `print()` pro ladění?**

1. **Není trvalý:** Výpis zmizí, jakmile zavřete konzoli.  
2. **Nelze filtrovat:** Musíte ručně hledat chyby v záplavě textu.  
3. **Špatně se vypíná:** Když chcete jít do produkce, musíte všechny volání funkce `print()` smazat nebo zakomentovat.

Modul `logging` řeší všechny tyto problémy.

## **Úrovně logování (Logging Levels)**

Každá zpráva má svou důležitost (úroveň). Můžete nastavit, že chcete vidět jen chyby, a ignorovat detaily.

1. **DEBUG**: Detailní informace pro diagnostiku (např. "Hodnota proměnné X je 5").  
2. **INFO**: Potvrzení, že věci fungují jak mají (např. "Uživatel přihlášen").  
3. **WARNING**: Něco je špatně, ale program běží dál (např. "Disk je z 90 % plný"). **Defaultní úroveň.**  
4. **ERROR**: Vážnější problém, část programu selhala (např. "Nelze uložit soubor").  
5. **CRITICAL**: Kritická chyba, program pravděpodobně spadne (např. "Databáze neodpovídá").

## **Základní konfigurace**

Nejjednodušší způsob je použít `logging.basicConfig()`.

```python
import logging

logging.basicConfig(  
    level=logging.INFO,  # Loguj vše od INFO výše (DEBUG se ignoruje)  
    filename='app.log',  # Ulož do souboru  
    format='%(asctime)s - %(levelname)s - %(message)s' # Přidej čas  
)

logging.info("Start programu")  
logging.warning("Pozor!")
```

## **Formátování**

V parametru `format` můžeme použít různé proměnné:

* `%(asctime)s` - Čas události  
* `%(levelname)s` - Úroveň (INFO, ERROR...)  
* `%(message)s` - Samotná zpráva  
* `%(funcName)s` - Název funkce, kde se logovalo

## **Logování výjimek**

Pokud chytáte výjimku v `except` bloku, je dobré ji zalogovat i s tzv. Tracebackem (historií volání). K tomu slouží parametr `exc_info=True` nebo metoda `logging.exception()`.

```python
try:  
    1 / 0  
except ZeroDivisionError:  
    logging.error("Chyba výpočtu", exc_info=True)
```
---
## **Cvičení**

### **1. První log**
Nastavte `logging.basicConfig` tak, aby logoval do souboru `moje_aplikace.log` a úroveň byla `DEBUG`. Zalogujte jednu zprávu z každé úrovně (debug, info, warning, error).
Otevřete soubor a zkontrolujte obsah.

### **2. Logování chyby**
Vytvořte záměrnou chybu (např. dělení nulou) v bloku `try-except`. V bloku `except` chybu zalogujte pomocí `logging.error("...", exc_info=True)`, aby se uložil i popis chyby.
