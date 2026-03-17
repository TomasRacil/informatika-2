# **Funkce v Pythonu**

Funkce jsou základním stavebním kamenem každého většího programu. Umožňují nám rozdělit kód na menší, logické celky (bloky), které můžeme opakovaně volat. To zvyšuje čitelnost kódu a usnadňuje jeho údržbu (DRY - Don't Repeat Yourself).

## **Definice funkce**

K definici funkce používáme klíčové slovo `def`, následované názvem funkce, závorkami `()` a dvojtečkou `:`. Tělo funkce musí být odsazené.

```python
def nazev_funkce():  
    print("Tělo funkce")
```

### **Volání funkce**

Funkci spustíme (zavoláme) jejím názvem a závorkami.

```python
nazev_funkce()
```

## **Parametry a argumenty**

Funkce mohou přijímat data pomocí **parametrů** (proměnné v definici funkce). Při volání funkce pak předáváme konkrétní hodnoty, kterým říkáme **argumenty**.

```python
def pozdrav(jmeno):  # 'jmeno' je parametr  
    print(f"Ahoj, {jmeno}!")

pozdrav("Petře")     # "Petře" je argument
```

### **Výchozí hodnoty parametrů (Default arguments)**

Můžeme nastavit výchozí hodnotu parametru. Pokud uživatel při volání tento argument nezadá, použije se výchozí.

```python
def pozdrav(jmeno="Neznámý"):  
    print(f"Ahoj, {jmeno}!")

pozdrav() # Vypíše: Ahoj, Neznámý!
```

## **Návratová hodnota (`return`)**

Funkce často něco vypočítají a výsledek chtějí vrátit zpět do místa, odkud byly zavolány. K tomu slouží klíčové slovo `return`. Jakmile Python narazí na `return`, funkce okamžitě končí.

```python
def soucet(a, b):  
    vysledek = a + b  
    return vysledek  # Vrátí hodnotu zpět

x = soucet(5, 3)     # x bude 8  
print(x)
```
## **Anonymní funkce (`lambda`)**

Lambda funkce jsou malé, jednorázové funkce, které nemají jméno. Jsou definovány na jednom řádku pomocí klíčového slova `lambda`. Často se používají tam, kde potřebujeme funkci jako argument pro jinou funkci (např. při řazení).

**Syntaxe:** `lambda argumenty: výraz`

```python
# Klasická funkce
def na_druhou(x):
    return x * x

# Ekvivalentní lambda funkce
na_druhou_lambda = lambda x: x * x

print(na_druhou_lambda(5)) # Vypíše 25
```

## **Rozsah platnosti proměnných (Scope)**

* **Lokální proměnné:** Proměnné definované uvnitř funkce. Jsou viditelné pouze uvnitř této funkce.  
* **Globální proměnné:** Proměnné definované v hlavním těle programu. Jsou viditelné všude (ale pro jejich úpravu uvnitř funkce je potřeba klíčové slovo `global`, což se obecně nedoporučuje).
---
## **Cvičení**

### **1. Obsah obdélníku**
Napište funkci `obsah(a, b)`, která vrátí obsah obdélníku.
Vyzkoušejte ji s hodnotami od uživatele.

### **2. Pozdrav s časem**
Napište funkci `pozdrav(jmeno, cas="ráno")`.
- Pokud zavolám `pozdrav("Jana")`, vypíše "Dobré ráno, Jana".
- Pokud zavolám `pozdrav("Petr", "večer")`, vypíše "Dobrý večer, Petr".

### **3. Lambda násobička**
Vytvořte lambda funkci, která přijme číslo a vrátí jeho trojnásobek. Uložte ji do proměnné `nasob` a otestujte.
