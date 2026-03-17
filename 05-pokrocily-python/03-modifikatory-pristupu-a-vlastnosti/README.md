# **03 - Modifikátory přístupu a Vlastnosti**

V objektově orientovaném programování je jedním z hlavních principů **zapouzdření (encapsulation)**. To znamená, že data (atributy) a metody, které s nimi pracují, jsou uzavřeny v jedné třídě a přímý přístup k datům zvenčí je omezen.

Cílem je zabránit nechtěné změně vnitřního stavu objektu, která by mohla vést k chybám (např. nastavení záporného věku nebo zůstatku na účtu).

## **Modifikátory přístupu v Pythonu**

Na rozdíl od jazyků jako C++ nebo Java, Python nepoužívá klíčová slova `public`, `private` nebo `protected`. Místo toho spoléhá na jmenné konvence (použití podtržítek).

### **1. Public (Veřejné)**

* **Zápis:** `self.jmeno`  
* **Chování:** Atribut je přístupný odkudkoliv (z vnitřku třídy i zvenčí).  
* **Použití:** Pro data, která mohou být volně čtena a měněna.

### **2. Protected (Chráněné)**

* **Zápis:** `self._jmeno` (jedno podtržítko na začátku)  
* **Chování:** Funguje jako public (Python přístup nezakáže), ale podtržítko je vzkaz pro programátora: *"Tento atribut je určen pouze pro vnitřní použití ve třídě a jejích potomcích. Nesahej na něj zvenčí."*  
* **Použití:** Pro vnitřní logiku, která by neměla být součástí veřejného rozhraní (API).

### **3. Private (Soukromé)**

* **Zápis:** `self.__jmeno` (dvě podtržítka na začátku)  
* **Chování:** Python provede tzv. **Name Mangling** (zkomolení jména). Atribut `__jmeno` ve třídě `Trida` interně přejmenuje na `_Trida__jmeno`.  
* **Důsledek:** Atribut není jednoduše přístupný pomocí `objekt.__jmeno`.  
* **Použití:** Pro data, která musí být striktně skryta před vnějším světem a potomky, aby nedošlo ke kolizi názvů.

## **Vlastnosti (Properties)**

Častou chybou začátečníků přicházejících z jiných jazyků je psaní metod `get_hodnota()` a `set_hodnota()` pro každý atribut. V Pythonu je tento přístup považován za neefektivní.

Pokud potřebujeme kontrolovat přístup k atributu (např. ověřit, že nová hodnota není záporná), použijeme dekorátor `@property`.

### **Syntax `@property`**

Umožňuje definovat metody, ke kterým se přistupuje jako k atributům (bez závorek).

1. **Getter** (`@property`): Metoda, která se zavolá, když hodnotu čteme.  
2. **Setter** (`@nazev.sette`r): Metoda, která se zavolá, když do hodnoty zapisujeme.

```python
class Clovek:  
    def __init__(self, vek):  
        self._vek = vek  # Uložíme do protected proměnné

    @property  
    def vek(self):  
        # Getter: vrátí hodnotu  
        return self._vek

    @vek.setter  
    def vek(self, hodnota):  
        # Setter: provede validaci  
        if hodnota < 0:  
            print("Chyba: Věk nemůže být záporný.")  
        else:  
            self._vek = hodnota
```

Použití je pak přirozené:

```python
jan = Clovek(20)  
jan.vek = 25    # Volá setter  
print(jan.vek)  # Volá getter  
jan.vek = -5    # Setter zachytí chybu
```

Toto je **Pythonic way** – kód je čistý, čitelný a data jsou chráněna.
---
## **Cvičení**

### **1. Bankovní účet**
Vytvořte třídu `Ucet`.
1. V `__init__` nastavte privátní atribut `__zustatek` na 0.
2. Vytvořte property `zustatek` (getter), která vrátí aktuální stav.
3. Vytvořte metodu `vloz(castka)`, která zvýší zůstatek (pouze pokud je částka kladná).
4. Vytvořte setter pro `zustatek`, který nedovolí nastavit zápornou hodnotu (vypíše chybu).

### **2. Test bezpečnosti**
Zkuste vytvořit instanci účtu a přistoupit přímo k `__zustatek`. Co se stane?
