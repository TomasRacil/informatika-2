# **01 - Syntaxe, Výstup a Komentáře**

Vítejte v prvním bloku Pythonu. Zde se naučíme, jak Python funguje, jak zapisovat instrukce a jak komunikovat s uživatelem pomocí výpisu textu.

## **1. Základní filosofie a Syntaxe**

Python je navržen tak, aby byl čitelný.

* **Žádné středníky:** Na konci řádku se nepíše `;`. Konec řádku znamená konec příkazu.  
* **Case Sensitive:** Záleží na velikosti písmen. `print`, `Print` a `PRINT` jsou tři různé věci (v Pythonu funguje pouze to první).  
* **Odsazování (Indentation):** Toto je pro Python klíčové. Zatímco jiné jazyky (C++, C#) používají složené závorky `{}` pro ohraničení bloků kódu (např. uvnitř podmínek), Python používá odsazení textu.

## **2. Funkce `print()`**

Tato funkce slouží k vypsání čehokoliv do konzole (terminálu).

### **Základní použití**

```python
print("Ahoj světe")  
print(123)
```

### **Pokročilé parametry**

Funkce `print` má užitečné volitelné parametry:

1. **`sep` (separator):** Určuje, co se vloží *mezi* jednotlivé vypisované hodnoty. Výchozí je mezera.  
2. **`end`:** Určuje, co se vypíše *na úplném konci*. Výchozí je nový řádek (`\n`).

```python
# Vypíše: 10:20:30 (na jednom řádku)  
print(10, 20, 30, sep=":")

# Vypíše: Ahoj... (kurzor zůstane na stejném řádku)  
print("Ahoj", end="...")
```

## **3. Formátování textu (f-strings)**

Od verze Python 3.6 používáme tzv. **f-stringy**. Jde o modernější a přehlednější způsob, jak vložit proměnné přímo do textu. Před uvozovky stačí napsat písmeno `f` a proměnné psát do složených závorek `{}`.

```python
jmeno = "Lukáš"  
vek = 25  
# Starší způsob (doporučuji nepoužívat, pokud nemusíte):  
print("Jmenuje se", jmeno, "a je mu", vek)

# Moderní způsob (f-string):  
print(f"Jmenuje se {jmeno} a je mu {vek} let.")
```

## **4. Komentáře**

Komentáře jsou vzkazy pro programátory. Python je při spuštění programu zcela ignoruje.

* **Jednořádkový:** Začíná znakem `#`.  
* **Víceřádkový (Docstring):** Ohraničený třemi uvozovkami `"""`. Používá se pro dokumentaci.

```python
# Toto je komentář  
print("Kod") # Komentář může být i za příkazem
```

## **5. Speciální znaky (Escape sequences)**

Někdy potřebujeme vypsat znaky, které mají speciální význam (např. odřádkování).

* `\n` - Nový řádek (New Line)  
* `\t` - Tabulátor  
* `\"` nebo `\'` - Vypíše uvozovku, aniž by ukončil řetězec.  
* `\\` - Vypíše zpětné lomítko.
---
## **Cvičení**

### **1. Pozdrav**
Vypište do konzole text "Ahoj světe, učím se Python!"

### **2. Vizitka (f-string)**
Vytvořte proměnné `jmeno` (text) a `vek` (číslo). Pomocí f-stringu vypište větu: "Jmenuji se [jmeno] a je mi [vek] let."

### **3. Seznam barev**
Pomocí jedné funkce `print` vypište následující barvy, každou na nový řádek (použijte parametr `sep`):
- Červená
- Zelená
- Modrá
